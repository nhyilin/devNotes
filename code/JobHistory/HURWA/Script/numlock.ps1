"关闭数字键盘"
$isNumLockOn = [console]::NumberLock
if($isNumLockOn)
{
    $wsh = New-Object -ComObject WScript.Shell
    $wsh.SendKeys('{NUMLOCK}')
}
