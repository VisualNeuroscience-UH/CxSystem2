"""
Unit tests for the RandomManager singleton in cxsystem2.core.
"""

# Built-in
import threading
from unittest import mock

# Third-party
import pytest
from numpy.random import Generator, SeedSequence, default_rng

# Local
from cxsystem2.core.workspace_manager import RandomManager


def _reset_singleton() -> None:
    """Reset the singleton through its private class attributes."""
    RandomManager._instance = None
    RandomManager._initialized = False


@pytest.fixture(autouse=True)
def _reset_random_manager():
    """Give every test a fresh, uninitialized RandomManager singleton."""
    _reset_singleton()
    yield
    _reset_singleton()


def _run_in_thread(target) -> dict:
    """Run ``target()`` in a joined thread and return its outcome.

    The returned dictionary holds ``"result"`` on success or ``"error"``
    with the raised exception.
    """
    outcome = {}

    def _wrapper() -> None:
        try:
            outcome["result"] = target()
        except BaseException as exc:  # noqa: BLE001 - forwarded to the test
            outcome["error"] = exc

    thread = threading.Thread(target=_wrapper)
    thread.start()
    thread.join()
    return outcome


class TestSingletonAndSeed:
    """Singleton semantics and the seed and spawn-key properties."""

    def test_first_construction_fixes_seed(self):
        manager = RandomManager(42)
        assert manager.seed == 42

    def test_repeated_construction_returns_same_instance(self):
        first = RandomManager(42)
        assert RandomManager() is first
        assert RandomManager(42) is first

    def test_omitted_seed_after_init_allowed(self):
        first = RandomManager(42)
        assert RandomManager(None) is first

    def test_get_instance_matches_constructor(self):
        first = RandomManager.get_instance(42)
        assert RandomManager() is first
        assert RandomManager.get_instance() is first

    def test_conflicting_seed_raises(self):
        RandomManager(42)
        with pytest.raises(RuntimeError, match="already initialized"):
            RandomManager(43)

    def test_none_seed_draws_entropy(self):
        manager = RandomManager()
        assert isinstance(manager.seed, int)
        assert manager.seed >= 0

    def test_negative_seed_rejected(self):
        # NumPy itself rejects negative integer entropy; the manager does
        # not convert that into a RuntimeError, so the native exception
        # propagates.
        with pytest.raises(ValueError):
            RandomManager(-1)

    def test_root_spawn_key_empty(self):
        assert RandomManager(42).spawn_key == ()


class TestRngAndSpawn:
    """The shared generator, spawn, and internal wiring checks."""

    def test_rng_returns_shared_generator(self):
        manager = RandomManager(42)
        assert isinstance(manager.rng, Generator)
        assert manager.rng is manager.rng

    def test_rng_deterministic_across_managers(self):
        first = RandomManager(42).rng.random(5)
        _reset_singleton()
        second = RandomManager(42).rng.random(5)
        assert (first == second).all()

    def test_rng_matches_reference_stream(self):
        manager = RandomManager(42)
        reference = default_rng(SeedSequence(42))
        assert (manager.rng.random(5) == reference.random(5)).all()

    def test_rng_advances_shared_stream(self):
        manager = RandomManager(42)
        first = manager.rng.random(3)
        second = manager.rng.random(3)
        assert not (first == second).all()

    def test_spawn_returns_requested_generators(self):
        generators = RandomManager(42).spawn(3)
        assert len(generators) == 3
        assert all(isinstance(g, Generator) for g in generators)

    def test_spawn_children_independent(self):
        draws = [g.random(5) for g in RandomManager(42).spawn(3)]
        for i in range(len(draws)):
            for j in range(i + 1, len(draws)):
                assert not (draws[i] == draws[j]).all()

    def test_spawn_deterministic(self):
        first = [g.random(5) for g in RandomManager(42).spawn(2)]
        _reset_singleton()
        second = [g.random(5) for g in RandomManager(42).spawn(2)]
        assert all((a == b).all() for a, b in zip(first, second))

    def test_spawn_differs_from_parent_stream(self):
        manager = RandomManager(42)
        parent_draw = manager.rng.random(5)
        child_draw = manager.spawn(1)[0].random(5)
        assert not (parent_draw == child_draw).all()

    def test_constructor_builds_generator_from_master_sequence(self):
        with mock.patch(
            "cxsystem2.core.workspace_manager.default_rng"
        ) as factory:
            manager = RandomManager(42)
            factory.assert_called_once()
            (master,), _ = factory.call_args
            assert isinstance(master, SeedSequence)
            assert master.entropy == 42
            assert manager._rng is factory.return_value

    def test_spawn_delegates_to_master_sequence(self):
        with mock.patch(
            "cxsystem2.core.workspace_manager.default_rng"
        ) as factory:
            manager = RandomManager(42)
            master = manager._seed_sequence
            # SeedSequence is immutable from Python, so its spawn method
            # cannot be patched; a spec-ed mock stands in for the master
            # sequence and hands out the real spawned children.
            children = master.spawn(3)
            fake_sequence = mock.Mock(spec=SeedSequence)
            fake_sequence.spawn.return_value = children
            with mock.patch.object(
                manager, "_seed_sequence", fake_sequence
            ):
                manager.spawn(3)
            fake_sequence.spawn.assert_called_once_with(3)
            # One factory call in the constructor plus one per child.
            assert factory.call_count == 4
            passed = [c.args[0] for c in factory.call_args_list[1:]]
            assert passed == children

    def test_ownership_guard_covers_streams_not_pure_reads(self):
        manager = RandomManager(42)
        with mock.patch.object(
            RandomManager, "_ensure_thread_ownership"
        ) as guard:
            manager.rng
            manager.seed_sequence
            manager.spawn(1)
            assert guard.call_count == 3
            manager.seed
            manager.spawn_key
            assert guard.call_count == 3


class TestProcessRecursion:
    """SeedSequence adoption, spawn keys, and cross-kind conflicts."""

    def test_seed_sequence_property_returns_adopted_sequence(self):
        sequence = SeedSequence(7)
        manager = RandomManager(sequence)
        assert manager.seed_sequence is sequence
        assert manager.seed == 7
        assert manager.spawn_key == ()

    def test_child_sequence_adopted(self):
        parent = RandomManager(42)
        child_seq = parent.seed_sequence.spawn(1)[0]
        _reset_singleton()
        child = RandomManager(child_seq)
        assert child.seed_sequence is child_seq
        assert child.seed == 42
        assert child.spawn_key == (0,)

    def test_child_stream_reconstructible_from_seed_and_spawn_key(self):
        parent = RandomManager(42)
        child_seq = parent.seed_sequence.spawn(1)[0]
        _reset_singleton()
        child = RandomManager(child_seq)
        reference = default_rng(SeedSequence(42, spawn_key=(0,)))
        assert (child.rng.random(5) == reference.random(5)).all()

    def test_grandchildren_match_reference_tree(self):
        parent = RandomManager(42)
        child_seq = parent.seed_sequence.spawn(1)[0]
        _reset_singleton()
        child = RandomManager(child_seq)
        draws = [g.random(5) for g in child.spawn(2)]
        reference_base = SeedSequence(42, spawn_key=(0,))
        reference = [
            default_rng(s).random(5) for s in reference_base.spawn(2)
        ]
        assert all((a == b).all() for a, b in zip(draws, reference))

    def test_same_sequence_object_accepted(self):
        sequence = SeedSequence(42, spawn_key=(0,))
        manager = RandomManager(sequence)
        assert RandomManager(sequence) is manager

    def test_equal_value_sequence_rejected(self):
        # SeedSequence defines no value equality, so sequences are matched
        # by identity: an equal-looking but different object conflicts.
        RandomManager(SeedSequence(42, spawn_key=(0,)))
        with pytest.raises(RuntimeError, match="already initialized"):
            RandomManager(SeedSequence(42, spawn_key=(0,)))

    def test_sequence_and_integer_conflict_both_ways(self):
        RandomManager(42)
        with pytest.raises(RuntimeError, match="already initialized"):
            RandomManager(SeedSequence(42))
        _reset_singleton()
        RandomManager(SeedSequence(42))
        with pytest.raises(RuntimeError, match="already initialized"):
            RandomManager(42)


class TestThreadOwnership:
    """Single-owner discipline of the shared stream."""

    def test_construction_does_not_claim_ownership(self):
        manager = RandomManager(42)
        assert manager._owner_thread is None

    def test_first_use_claims_ownership(self):
        manager = RandomManager(42)
        manager.rng
        assert manager._owner_thread is threading.current_thread()

    def test_other_live_thread_rejected_for_rng(self):
        manager = RandomManager(42)
        manager.rng
        outcome = _run_in_thread(lambda: manager.rng)
        assert isinstance(outcome.get("error"), RuntimeError)
        assert "owned by thread" in str(outcome["error"])

    def test_spawn_rejected_from_other_thread(self):
        manager = RandomManager(42)
        manager.rng
        outcome = _run_in_thread(lambda: manager.spawn(2))
        assert isinstance(outcome.get("error"), RuntimeError)

    def test_seed_sequence_rejected_from_other_thread(self):
        manager = RandomManager(42)
        manager.rng
        outcome = _run_in_thread(lambda: manager.seed_sequence)
        assert isinstance(outcome.get("error"), RuntimeError)

    def test_pure_reads_allowed_from_other_thread(self):
        manager = RandomManager(42)
        manager.rng
        outcome = _run_in_thread(lambda: (manager.seed, manager.spawn_key))
        assert "error" not in outcome
        assert outcome["result"] == (42, ())

    def test_ownership_transfers_when_owner_ends(self):
        manager = RandomManager(42)

        def _use():
            return manager.rng.random()

        outcome = _run_in_thread(_use)
        assert "error" not in outcome
        # The previous owner has ended, so the main thread takes over
        # without an explicit handoff.
        assert 0.0 <= manager.rng.random() < 1.0

    def test_claim_ownership_explicit_handoff(self):
        manager = RandomManager(42)
        manager.rng
        claimed = threading.Event()
        release = threading.Event()

        def _worker():
            manager.claim_ownership()
            manager.rng.random()
            claimed.set()
            release.wait()

        worker = threading.Thread(target=_worker)
        worker.start()
        assert claimed.wait(timeout=5)
        # While the new owner is alive, the main thread is rejected.
        with pytest.raises(RuntimeError, match="owned by thread"):
            manager.rng
        release.set()
        worker.join()
        # After the worker ends, ownership transfers back automatically.
        assert 0.0 <= manager.rng.random() < 1.0

    def test_spawned_generators_safe_in_threads(self):
        # The supported pattern: spawn up front, then draw from the
        # independent generators concurrently, without the manager.
        manager = RandomManager(42)
        first, second = manager.spawn(2)
        results = {}

        def _draw(gen, key):
            results[key] = gen.random(3)

        threads = [
            threading.Thread(target=_draw, args=(first, "first")),
            threading.Thread(target=_draw, args=(second, "second")),
        ]
        for thread in threads:
            thread.start()
        for thread in threads:
            thread.join()
        assert results["first"].shape == (3,)
        assert results["second"].shape == (3,)