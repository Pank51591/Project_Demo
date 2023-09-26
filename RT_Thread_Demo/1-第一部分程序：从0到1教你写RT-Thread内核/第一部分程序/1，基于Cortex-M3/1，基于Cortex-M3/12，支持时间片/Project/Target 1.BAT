SET PATH=D:\Program Files\Keil_v5\ARM\ARMCC\Bin;D:\Program Files\Python39\Scripts\;D:\Program Files\Python39\;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files\mingw64\bin;D:\Program Files\Git\cmd;C:\Users\ÅË¼ªÀ­±¦±´¶ù\AppData\Local\Microsoft\WindowsApps;D:\Program Files\Microsoft VS Code\bin
SET CPU_TYPE=ARMCM3
SET CPU_VENDOR=ARM
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x017D7840
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\main.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\context_rvds._ia"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\cpuport.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\scheduler.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\thread.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\object.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\kservice.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\idle.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\irq.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\clock.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\timer.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_armcm3._ia"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_armcm3.__i"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\YH-RT-Thread.lnp"
"D:\Program Files\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\YH-RT-Thread.axf" --i32combined --output ".\Objects\YH-RT-Thread.hex"
