#! /usr/bin/env python3
# -*- coding: utf-8 -*-
__author__ = 'Andalibi, V.'


class ParameterNotFoundError(Exception):
    pass


class ClusterNotReachableError(Exception):
    pass


class RelativePathError(Exception):
    pass


class InvalidConfigurationError(Exception):
    pass
