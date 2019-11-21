from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path("simulate", views.simulate),
    path("load_example", views.load_example),
    path("download_workspace", views.download_workspace),
    path("ls_workspace", views.ls_workspace)
]
