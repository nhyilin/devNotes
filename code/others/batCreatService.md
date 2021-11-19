


基于win下bat指令创建服务，指定路径的exe服务：

```bat
@echo off

set SERVICE_NAME=HHRBAssist
set TOOLBIN_PATH=D:\assistTools\

IF /I NOT "%~dp0"=="%TOOLBIN_PATH%" (
   echo Must put these files in "%TOOLBIN_PATH%"
   Exit /B 1
 )

echo register service %SERVICE_NAME% ...
sc.exe create "%SERVICE_NAME%" binPath=%~dp0%HHRBAssistService.exe
sc.exe config "%SERVICE_NAME%" start=auto

echo start service %SERVICE_NAME% ...
sc.exe start "%SERVICE_NAME%"
```

删除服务：

```bat
net stop "HHRBAssist"
sc.exe delete "HHRBAssist"
```


也许这个sc是server command的含义吧