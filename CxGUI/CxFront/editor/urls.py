from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path("simulate",views.simulate),
    path("load_example",views.load_example)
]