定制脚本：
（1）osCfg.bat:用于关闭通用服务
（2）disable_shortcut.ps1:关闭快捷键
（3）langeuage.ps1:去掉中文输入法，添加英文输入法




恢复脚本：
（1）osCfg_Recover.bat:恢复关闭的服务
（2）enalbe_all_shortcut.ps1:恢复快捷键
（3）languageRecover.ps1:添加中文输入法，去掉英文输入法



运行方式：
（1）bat脚本：管理员运行
（2）ps1脚本：管理员运行powershell，拖进ps1脚本，回车进行运行



计算机\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows Embedded\KeyboardFilter

执行顺序：
1.Start_FilterKeyBoard.bat
2.osCfg.bat