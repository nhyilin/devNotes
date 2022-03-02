#https://docs.microsoft.com/en-us/windows-hardware/customize/enterprise/predefined-key-combinations
#
# Copyright (C) Microsoft. All rights reserved.
#

<#
.Synopsis
    This script shows how to use the built in WMI providers to enable and add 
    keyboard filter rules through Windows PowerShell on the local computer.
.Parameter ComputerName
    Optional parameter to specify a remote machine that this script should
    manage.  If not specified, the script will execute all WMI operations
    locally.
#>
param (
    [String] $ComputerName
)

$CommonParams = @{"namespace"="root\standardcimv2\embedded"}
$CommonParams += $PSBoundParameters

function Enable-Predefined-Key($Id) {
    <#
    .Synopsis
        Toggle on a Predefined Key keyboard filter Rule
    .Description
        Use Get-WMIObject to enumerate all WEKF_PredefinedKey instances,
        filter against key value "Id", and set that instance's "Enabled"
        property to 1/true.
    .Example
        Enable-Predefined-Key "Ctrl+Alt+Del"
        Enable CAD filtering
#>

    $predefined = Get-WMIObject -class WEKF_PredefinedKey @CommonParams |
        where {
            $_.Id -eq "$Id"
        };

    if ($predefined) {
        $predefined.Enabled = 1;
        $predefined.Put() | Out-Null;
        Write-Host Enabled $Id
    } else {
        Write-Error "$Id is not a valid predefined key"
    }
}


function Enable-Custom-Key($Id) {
    <#
    .Synopsis
        Toggle on a Custom Key keyboard filter Rule
    .Description
        Use Get-WMIObject to enumerate all WEKF_CustomKey instances,
        filter against key value "Id", and set that instance's "Enabled"
        property to 1/true.

        In the case that the Custom instance does not exist, add a new
        instance of WEKF_CustomKey using Set-WMIInstance.
    .Example
        Enable-Custom-Key "Ctrl+V"
        Enable filtering of the Ctrl + V sequence.
#>

    $custom = Get-WMIObject -class WEKF_CustomKey @CommonParams |
        where {
            $_.Id -eq "$Id"
        };

    if ($custom) {
# Rule exists.  Just enable it.
        $custom.Enabled = 1;
        $custom.Put() | Out-Null;
        "Enabled Custom Filter $Id.";

    } else {
        Set-WMIInstance `
            -class WEKF_CustomKey `
            -argument @{Id="$Id"} `
            @CommonParams | Out-Null
        "Added Custom Filter $Id.";
    }
}

function Enable-Scancode($Modifiers, [int]$Code) {
    <#
    .Synopsis
        Toggle on a Scancode keyboard filter Rule
    .Description
        Use Get-WMIObject to enumerate all WEKF_Scancode instances,
        filter against key values of "Modifiers" and "Scancode", and set
        that instance's "Enabled" property to 1/true.

        In the case that the Scancode instance does not exist, add a new
        instance of WEKF_Scancode using Set-WMIInstance.
    .Example
        Enable-Scancode "Ctrl" 37
        Enable filtering of the Ctrl + keyboard scancode 37 (base-10)
        sequence.
#>

    $scancode =
        Get-WMIObject -class WEKF_Scancode @CommonParams |
            where {
                ($_.Modifiers -eq $Modifiers) -and ($_.Scancode -eq $Code)
            }

    if($scancode) {
        $scancode.Enabled = 1
        $scancode.Put() | Out-Null
        "Enabled Custom Scancode {0}+{1:X4}" -f $Modifiers, $Code
    } else {
        Set-WMIInstance `
            -class WEKF_Scancode `
            -argument @{Modifiers="$Modifiers"; Scancode=$Code} `
            @CommonParams | Out-Null
 
        "Added Custom Scancode {0}+{1:X4}" -f $Modifiers, $Code
    }
}


"关闭数字键盘"
$isNumLockOn = [console]::NumberLock
if($isNumLockOn)
{
    $wsh = New-Object -ComObject WScript.Shell
    $wsh.SendKeys('{NUMLOCK}')
}

# Some example uses of the functions defined above.
#Enable-Predefined-Key "Ctrl+Alt+Del"
Enable-Predefined-Key "Ctrl+Esc"
Enable-Predefined-Key "Alt+Tab"
Enable-Predefined-Key "Windows"
Enable-Predefined-Key "Alt+F4"
Enable-Predefined-Key "Alt+Esc"
Enable-Predefined-Key "Alt+Space"
                            

Enable-Scancode "" 69
#Enable-Custom-Key "Ctrl+V"
#Enable-Custom-Key "Numpad0"
#Enable-Custom-Key "Shift+Numpad1"
Enable-Custom-Key "%"
#Enable-Scancode "Ctrl" 37

get-appxpackage *Microsoft.XboxApp* | remove-appxpackage