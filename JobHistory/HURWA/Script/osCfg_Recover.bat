::（1）关闭自动更新（ok）
sc config wuauserv start= auto

::（2）关闭防火墙(注册表关闭服务Windows Defender Firewall，原Start为2)（ok）
NetSh Advfirewall set allprofiles state on
REG ADD HKLM\SYSTEM\CurrentControlSet\Services\mpssvc /v Start /t REG_DWORD /d 2 /f
REG DELETE HKLM\System\CurrentControlSet\Services\SecurityHealthService /v Start /f

::（3）关闭消息中心
REG ADD HKLM\Software\Policies\Microsoft\Windows\Explorer /v DisableNotificationCenter /t REG_DWORD /d 1 /f
REG ADD HKCU\Software\Microsoft\Windows\CurrentVersion\PushNotifications /v ToastEnabled /t REG_DWORD /d 0 /f


::（5）小键盘默认关闭(OK)
REG ADD "HKU\.DEFAULT\Control Panel\Keyboard" /v InitialKeyboardIndicators /t REG_SZ /d 80000002 /f


::（6）禁止U盘自动启动（ok）
REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\Explorer /v NoDriveTypeAutoRun /t REG_DWORD /d 221 /f
REG ADD HKCU\Software\Microsoft\Windows\CurrentVersion\Explorer\AutoplayHandlers /v DisableAutoplay /t REG_DWORD /d 1 /f


::（7）用户访问控制（ok）
REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /v ConsentPromptBehaviorAdmin /t REG_DWORD /d 5 /f
REG ADD HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Policies\System /v EnableLUA /t REG_DWORD /d 0 /f

::（8）关闭Windows update（ok）
sc config wuauserv start= auto >> C:\osCfg.log

::（8）关闭休眠、睡眠、屏幕保护功能（建议手动根据需求进行恢复操作）
::c:\windows\system32\powercfg.exe -change -monitor-timeout-ac 0
::c:\windows\system32\powercfg.exe -change -monitor-timeout-dc 0
::c:\windows\system32\powercfg.exe -change -disk-timeout-ac 0
::c:\windows\system32\powercfg.exe -change -disk-timeout-dc 0
::c:\windows\system32\powercfg.exe -change -standby-timeout-ac 0
::c:\windows\system32\powercfg.exe -change -standby-timeout-dc 0
::c:\windows\system32\powercfg.exe -change -hibernate-timeout-ac 0
::c:\windows\system32\powercfg.exe -change -hibernate-timeout-dc 0


::（9）禁用网络(ok)
::sc config dot3svc start= auto
sc config WlanSvc start= auto
sc config WFDSConMgrSvc start= auto


::（10）关闭杀毒软件（建议手动根据需求进行恢复操作）
REG ADD "HKLM\SOFTWARE\Policies\Microsoft\Windows Defender" /v DisableAntiSpyware /t REG_DWORD /d 1 /f
REG ADD HKLM\SYSTEM\CurrentControlSet\Services\WinDefend /v Start /t REG_DWORD /d 4 /f


::（11）关闭superfetch（ok）
sc config SysMain start= auto

::（12）禁用Diagnostic policy service服务（ok）
sc config DPS start= auto

::（13）关闭Windows search服务（ok）
sc config WSearch start= auto
::修改注册表
::REG ADD HKLM\SYSTEM\CurrentControlSet\Services\WSearch /v Start /t REG_DWORD /d 4 /f


::（14）关闭显卡弹框（ok）
sc config NVDisplay.ContainerLocalSystem start= auto


::（15）关闭粘滞键（将506更改为510）(OK)
REG ADD "HKCU\Control Panel\Accessibility\StickyKeys" /v Flags /t REG_SZ /d 510 /f


::（16）关闭CD和DVD可移动存储类的写入权限(OK)
REG DELETE "HKLM\Software\Policies\Microsoft\Windows\RemovableStorageDevices" /f



::（15）关闭所有快捷键
::REG ADD "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" /v Shell /t REG_SZ /d C:\Program Files\SurgicalPlanningExpert\SPExpert.exe /f
::REG ADD "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon" /v Shell /t REG_SZ /d explorer.exe /f



pushd %~dp0
powershell.exe -command ^
  "& {set-executionpolicy Remotesigned -Scope Process; .'.\enable_all_shortcut.ps1' }" >> C:\osCfgRecover.log
popd 


pushd %~dp0
powershell.exe -command ^
  "& {set-executionpolicy Remotesigned -Scope Process; .'.\languageRecover.ps1' }" >> C:\osCfg.log
popd

pause
