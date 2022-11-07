chcp 65001
::start KeyboardFilter
start /w pkgmgr /iu:Client-DeviceLockdown;Client-KeyboardFilter


::stop KeyboardFilter
::start /w pkgmgr /uu:Client-DeviceLockdown;Client-KeyboardFilter