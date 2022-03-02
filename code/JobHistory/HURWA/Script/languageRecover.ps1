$LanguageList = Get-WinUserLanguageList
$LanguageList.Add("zh-Hans-CN")
$LanguageList.Remove(($LanguageList | Where-Object LanguageTag -like 'en-US')) | Out-Null
Set-WinUserLanguageList $LanguageList -Force 