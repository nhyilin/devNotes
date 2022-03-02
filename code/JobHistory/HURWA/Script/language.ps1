$LanguageList = Get-WinUserLanguageList
$LanguageList.Add("en-US")
$LanguageList.Remove(($LanguageList | Where-Object LanguageTag -like 'zh-Hans-CN')) | Out-Null
Set-WinUserLanguageList $LanguageList -Force 