@echo off
REM 声明采用UTF-8编码
del D:\osCfg.log

chcp 65001
set d=%date:~0,2%
set mo=%date:~3,2%
set y=%date:~6,4%
set h=%time:~0,2%
set mi=%time:~3,2%
echo %y%_%mo%_%d%_%h%_%mi% >> D:\osCfg.log

set /a success=0
set /a failure=0

::（1）关闭Windows热键，参考脚本disable_shortcut.ps1
echo '开始执行osCfg脚本... ...' >> D:\osCfg.log
echo （1）关闭Windows快捷键，参考脚本disable_shortcut.ps1 >> D:\osCfg.log
pushd %~dp0
powershell.exe -command ^
  "& {set-executionpolicy Remotesigned -Scope Process; .'.\disable_shortcut.ps1' }" >> D:\osCfg.log
  
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
popd 


echo （2）关闭CD和DVD可移动存储类的写入权限 >> D:\osCfg.log
REG ADD "HKLM\Software\Policies\Microsoft\Windows\RemovableStorageDevices\{53f56308-b6bf-11d0-94f2-00a0c91efb8b}" /v Deny_Write /t REG_DWORD /d 1 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （3）关闭休眠、睡眠、屏幕保护功能 >> D:\osCfg.log
C:\windows\system32\powercfg.exe -change -monitor-timeout-ac 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
c:\windows\system32\powercfg.exe -change -monitor-timeout-dc 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
c:\windows\system32\powercfg.exe -change -disk-timeout-ac 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
c:\windows\system32\powercfg.exe -change -disk-timeout-dc 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
c:\windows\system32\powercfg.exe -change -standby-timeout-ac 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
c:\windows\system32\powercfg.exe -change -standby-timeout-dc 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
c:\windows\system32\powercfg.exe -change -hibernate-timeout-ac 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
c:\windows\system32\powercfg.exe -change -hibernate-timeout-dc 0 >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

echo （4）关闭粘滞键 >> D:\osCfg.log
REG ADD "HKCU\Control Panel\Accessibility\StickyKeys" /v Flags /t REG_SZ /d 506 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

echo （5）禁止U盘自动启动 >> D:\osCfg.log
REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoDriveTypeAutoRun /t REG_DWORD /d 255 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
REG ADD HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\AutoplayHandlers /v DisableAutoplay /t REG_DWORD /d 1 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

echo （6）关闭UAC >> D:\osCfg.log
REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /v ConsentPromptBehaviorAdmin /t REG_DWORD /d 0 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /v EnableLUA /t REG_DWORD /d 0 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

echo （7）关闭Windows update >> D:\osCfg.log
::sc config wuauserv start= disabled >> D:\osCfg.log
REG ADD HKLM\SYSTEM\ControlSet001\Services\WaaSMedicSvc /v Start /t REG_DWORD /d 4 /F >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
REG ADD HKLM\SYSTEM\ControlSet001\Services\wuauserv /v Start /t REG_DWORD /d 4 /F >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

echo （8）禁用网络 >> D:\osCfg.log
::sc config dot3svc start= disabled
sc config WlanSvc start= disabled >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
sc config WFDSConMgrSvc start= disabled >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

echo （9）关闭Windows search服务 >> D:\osCfg.log
sc config WSearch start= disabled >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
::修改注册表
::REG ADD HKLM\SYSTEM\CurrentControlSet\Services\WSearch /v Start /t REG_DWORD /d 4 /f


echo （10）关闭superfetch >> D:\osCfg.log
sc config SysMain start= disabled >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （11）关闭防火墙(注册表关闭服务Windows Defender Firewall，原Start为2) >> D:\osCfg.log
::NetSh Advfirewall set allprofiles state off >> D:\osCfg.log
REG ADD HKLM\System\CurrentControlSet\Services\SecurityHealthService /v Start /t REG_DWORD /d 4 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
REG ADD HKLM\SYSTEM\CurrentControlSet\Services\mpssvc /v Start /t REG_DWORD /d 4 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （12）禁用Diagnostic policy service服务 >> D:\osCfg.log
sc config DPS start= disabled >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （13）关闭消息通知 >> D:\osCfg.log
REG ADD HKCU\Software\Microsoft\Windows\CurrentVersion\PushNotifications /v ToastEnabled /t REG_DWORD /d 0 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （14）关闭杀毒软件 >> D:\osCfg.log
REG ADD "HKLM\SOFTWARE\Policies\Microsoft\Windows Defender" /v DisableAntiSpyware /t REG_DWORD /d 1 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
REG ADD HKLM\SYSTEM\CurrentControlSet\Services\WinDefend /v Start /t REG_DWORD /d 4 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （15）关闭显卡弹框 >> D:\osCfg.log
sc config NVDisplay.ContainerLocalSystem start= disabled >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （16）删除通知和操作中心 >> D:\osCfg.log
REG ADD HKLM\Software\Policies\Microsoft\Windows\Explorer /v DisableNotificationCenter /t REG_DWORD /d 1 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo （17）删除中文输入法，安装英文输入法，参考脚本language.ps1 >> D:\osCfg.log

pushd %~dp0
powershell.exe -command ^
  "& {set-executionpolicy Remotesigned -Scope Process; .'.\language.ps1' }" >> D:\osCfg.log

if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
popd

::（18）关闭explorer.exe
::REG ADD "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" /v Shell /t REG_SZ /d D:\Program Files\SurgicalPlanningExpert\SPExpert.exe /f
::if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

::（19）修改WIN键造成锁屏问题
REG ADD "HKLM\SOFTWARE\Microsoft\Windows Embedded\KeyboardFilter" /v BreakoutKeyScanCode /t REG_DWORD /d 0 /f >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

::（20）按电源键后关机、按睡眠键后不做任何操作
powercfg.exe /setacvalueindex 381b4222-f694-41f0-9685-ff5bb260df2e 4f971e89-eebd-4455-a8de-9e59040e7347 7648efa3-dd9c-4e3e-b566-50f929386280 003
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)
powercfg.exe /setacvalueindex 381b4222-f694-41f0-9685-ff5bb260df2e 4f971e89-eebd-4455-a8de-9e59040e7347 96996bc0-ad50-47ec-923b-6f41874dd9eb 000
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)

::(21)设置Bitlocker服务为自动运行
sc config BDESVC start= auto >> D:\osCfg.log
if "%errorlevel%"=="0" (set /a success+=1) else (set /a failure+=1)


echo 脚本执行结束... ...				>> D:\osCfg.log
echo 									>> D:\osCfg.log
echo 									>> D:\osCfg.log
echo Over								>> D:\osCfg.log
echo success： %success%  failed：%failure%
if %failure% neq 0 (echo "脚本执行失败" >> D:\osCfg.log) else (echo "脚本执行成功" >> D:\osCfg.log)
pause
