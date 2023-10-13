SET PATH=D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\VMware\VMware Workstation\bin\;C:\Program Files\Python311\Scripts\;C:\Program Files\Python311\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\dotnet\;C:\Program Files\TortoiseSVN\bin;D:\Program Files\Microchip\xc8\v2.36\bin;C:\mingw-w64\x86_64-8.1.0-release-win32-seh-rt_v6-rev0\mingw64\bin;D:\Program Files\Git\cmd;C:\Users\80023166\AppData\Roaming\Python\Python311\Scripts\;C:\Users\80023166\AppData\Local\Microsoft\WindowsApps;D:\Program Files\VS Code\Microsoft VS Code\bin
SET ARMCC5_ASMOPT=--diag_suppress=9931
SET ARMCC5_CCOPT=--diag_suppress=9931
SET ARMCC5_LINKOPT=--diag_suppress=9931
SET CPU_TYPE=MM32F0144C6P
SET CPU_VENDOR=MindMotion
SET UV2_TARGET=MM32Series
SET CPU_CLOCK=0x00B71B00
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\system_mm32f0140.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\obj\startup_mm32f0140_keil._ia"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\key.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\tim1_interrupt.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\led_rf.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\rf_a7325.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\test.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\delay.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\sys.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\uart.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\main.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_adc.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_comp.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_crc.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_dbg.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_div.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_dma.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_exti.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_flash.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_flexcan.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_gpio.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_i2c.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_iwdg.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_misc.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_pwr.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_rcc.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_spi.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_sqrt.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_tim.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_uart.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_uid.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_ver.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\obj\hal_wwdg.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\OBJ\MBOUT.lnp"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\OBJ\MBOUT.axf" --i32combined --output ".\OBJ\MBOUT.hex"
