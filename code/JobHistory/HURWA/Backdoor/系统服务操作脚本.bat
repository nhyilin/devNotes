::添加服务
sc create "My sample service" binPath=d:\SampleService.exe

::将服务设为自动启动
sc config "My Sample Service" start=auto

::启动服务
sc start " My Sample Service"

::停止服务
sc stop "My Sample Service"

::删除服务
sc delete "My Sample Service"