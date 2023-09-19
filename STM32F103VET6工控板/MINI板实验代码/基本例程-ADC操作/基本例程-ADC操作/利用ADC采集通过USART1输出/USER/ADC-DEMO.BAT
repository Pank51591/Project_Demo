SET PATH=D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin;C:\Program Files (x86)\VMware\VMware Workstation\bin\;C:\Program Files\Python311\Scripts\;C:\Program Files\Python311\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;C:\Program Files\dotnet\;C:\Program Files\TortoiseSVN\bin;D:\Program Files\Microchip\xc8\v2.36\bin;C:\mingw-w64\x86_64-8.1.0-release-win32-seh-rt_v6-rev0\mingw64\bin;D:\Program Files\Git\cmd;C:\Users\80023166\AppData\Roaming\Python\Python311\Scripts\;C:\Users\80023166\AppData\Local\Microsoft\WindowsApps;D:\Program Files\VS Code\Microsoft VS Code\bin
SET CPU_TYPE=STM32F103VE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=ADC-DEMO
SET CPU_CLOCK=0x007A1200
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via "..\output\startup_stm32f10x_hd._ia"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\main.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\stm32f10x_it.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\usart1.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\adc.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\stm32f10x_gpio.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\stm32f10x_rcc.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\stm32f10x_usart.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\stm32f10x_adc.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\stm32f10x_dma.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\stm32f10x_flash.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\core_cm3.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmCC" --Via "..\output\system_stm32f10x.__i"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\ArmLink" --Via "..\Output\STM32-DEMO.lnp"
"D:\Program Files (x86)\keil_v5\ARM\ARMCC\Bin\fromelf.exe" "..\Output\STM32-DEMO.axf" --i32combined --output "..\Output\STM32-DEMO.hex"
