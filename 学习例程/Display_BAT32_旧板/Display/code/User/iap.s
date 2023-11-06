;********************************************************************************
;* @file        iap.s
;* @version     $Rev:: 328          $
;* @date        $Date:: 2016-04-14 #$
;* @brief       Include IAP image
;*
;* @note        Copyright (C) Holtek Semiconductor Inc. All rights reserved.
;*
;* <h2><center>&copy; COPYRIGHT Holtek</center></h2>
;*
;********************************************************************************
;*----------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;********************************************************************************

HT32F52220_30       EQU     1
HT32F52231_41       EQU     2
HT32F52331_41       EQU     3
HT32F52342_52       EQU     4

;// <q> Include IAP image into user's application
INCLUDE_IAP      EQU     1

        AREA    IAP, DATA, READONLY

        IF (USE_HT32_CHIP=HT32F52220_30)
          INCBIN  HT32\52230\IAP\Obj\IAP.axf.bin
        ENDIF

        IF (USE_HT32_CHIP=HT32F52231_41)
          INCBIN  .\BootLoader.bin
        ENDIF

        IF (USE_HT32_CHIP=HT32F52331_41)
          INCBIN  HT32\52341\IAP\Obj\IAP.axf.bin
        ENDIF

        IF (USE_HT32_CHIP=HT32F52342_52)
          INCBIN  HT32\52352\IAP\Obj\IAP.axf.bin
        ENDIF

        END
