from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path("simulate", views.simulate),
    path("load_example", views.load_example),
    path("download_workspace", views.download_workspace),
    path("download_files", views.download_files),
    path("ls_workspace", views.ls_workspace),
    path("simoutput", views.sim_output),
    path("simstatus", views.sim_status),
    path("delete", views.delete_all),
    path("visualize", views.visualize),
]
