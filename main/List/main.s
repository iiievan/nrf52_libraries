///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        05/Feb/2021  13:10:42
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\main\main.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EWEF4E.tmp
//        (E:\cpp\nrf52_libraries\main\main.cpp -D NRF52840_XXAA -D
//        CONFIG_NFCT_PINS_AS_GPIOS -D _AUDIOGUDE_V2_BOARD -D DEBUG -lCN
//        E:\cpp\nrf52_libraries\main\List -lA E:\cpp\nrf52_libraries\main\List
//        -o E:\cpp\nrf52_libraries\main\Obj --no_cse --no_unroll --no_inline
//        --no_code_motion --no_tbaa --no_clustering --no_scheduling --debug
//        --endian=little --cpu=Cortex-M4 -e --fpu=None --dlib_config
//        "C:\Program Files (x86)\IAR Systems\Embedded Workbench
//        8.3\arm\inc\c\DLib_Config_Full.h" -I E:\cpp\nrf52_libraries\fsm\ -I
//        E:\cpp\nrf52_libraries\pwm\ -I E:\cpp\nrf52_libraries\spi\ -I
//        E:\cpp\nrf52_libraries\usb\ -I E:\cpp\nrf52_libraries\main\ -I
//        E:\cpp\nrf52_libraries\cmsis\ -I E:\cpp\nrf52_libraries\cmsis\device\
//        -I E:\cpp\nrf52_libraries\cmsis\include\ -I
//        E:\cpp\nrf52_libraries\board\ -I E:\cpp\nrf52_libraries\utils\ -I
//        E:\cpp\nrf52_libraries\timer\ -I E:\cpp\nrf52_libraries\adc\ -On
//        --c++ --no_exceptions --no_rtti)
//    Locale       =  C
//    List file    =  E:\cpp\nrf52_libraries\main\List\main.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__CPP_Exceptions", "Disabled"
        RTMODEL "__CPP_Language", "C++14"
        RTMODEL "__SystemLibrary", "DLib"
        RTMODEL "__dlib_full_locale_support", "1"
        RTMODEL "__dlib_version", "6"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1
        #define SHT_INIT_ARRAY 0xe

        EXTERN _Z18sys_timer_callbackj
        EXTERN _ZN10led_driver3runEi
        EXTERN _ZN12PowerControl6configE15EChargeCurrents
        EXTERN _ZN12PowerControl6handleEv
        EXTERN _ZN5Timer4initEjjb
        EXTERN _ZN5Timer6setIRQEhh
        EXTERN __aeabi_fmul
        EXTERN __aeabi_i2f
        EXTERN bl_btn_led
        EXTERN btn_pr_led
        EXTERN kb_led
        EXTERN led_list
        EXTERN red_led
        EXTERN sys_timer

        PUBLIC SAADC_IRQHandler
        PUBLIC _Z12adc_callbackj
        PUBLIC _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        PUBLIC _ZN12ADCChannel_t8scaleRawEs
        PUBLIC _ZN12ADCChannel_tC1E12EADCChannelsfff
        PUBLIC _ZN12PowerControlC1EjR3ADCILi6EER5TimerPP10led_driverjjjj
        PUBLIC _ZN3ADCILi6EE5onIRQEv
        PUBLIC _ZN3ADCILi6EE6deinitEv
        PUBLIC _ZN3ADCILi6EE7disableEv
        PUBLIC _ZN3ADCILi6EEC1E14EADCResolution
        PUBLIC _ZN3ADCILi6EEC2E14EADCResolution
        PUBLIC _ZN5Timer11setCallbackEPFvjE
        PUBLIC adc_unite
        PUBLIC main
        PUBLIC power_manager
        
          CFI Names cfiNames0
          CFI StackFrame CFA R13 DATA
          CFI Resource R0:32, R1:32, R2:32, R3:32, R4:32, R5:32, R6:32, R7:32
          CFI Resource R8:32, R9:32, R10:32, R11:32, R12:32, R13:32, R14:32
          CFI EndNames cfiNames0
        
          CFI Common cfiCommon0 Using cfiNames0
          CFI CodeAlign 2
          CFI DataAlign 4
          CFI ReturnAddress R14 CODE
          CFI CFA R13+0
          CFI R0 Undefined
          CFI R1 Undefined
          CFI R2 Undefined
          CFI R3 Undefined
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI R8 SameValue
          CFI R9 SameValue
          CFI R10 SameValue
          CFI R11 SameValue
          CFI R12 Undefined
          CFI R14 SameValue
          CFI EndCommon cfiCommon0
        
// E:\cpp\nrf52_libraries\main\main.cpp
//    1 #include <string.h>
//    2 #include <ctype.h>
//    3 #include <intrinsics.h>
//    4 #include "nrf.h"
//    5 #include "nrf_gpio.h"
//    6 
//    7 #include "led_driver.h"
//    8 #include "nrf_hw_pwm.h"
//    9 #include "ADC.h"
//   10 #include "timer.h"
//   11 #include "PowerControl.h"
//   12 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function __sti__routine
        THUMB
// static __intrinsic __interwork __softfp void __sti__routine()
__sti__routine:
        PUSH     {LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+4
        SUB      SP,SP,#+20
          CFI CFA R13+24
//   13 ADC<ADC_CHANNELS_NUM> adc_unite(RES_12B);
        MOVS     R1,#+2
        LDR.N    R0,??DataTable2
          CFI FunCall _ZN3ADCILi6EEC1E14EADCResolution
        BL       _ZN3ADCILi6EEC1E14EADCResolution
//   14 PowerControl power_manager(CHRG_EN_PIN, adc_unite, sys_timer, led_list, VBAT_MEAS_PIN, MAIN_MEAS_PIN, SYS_3V0_PIN, MODULE_PWR);
        MOVS     R1,#+40
        STR      R1,[SP, #+16]
        MOVS     R1,#+39
        STR      R1,[SP, #+12]
        MOVS     R1,#+28
        STR      R1,[SP, #+8]
        MOVS     R1,#+29
        STR      R1,[SP, #+4]
        LDR.N    R1,??DataTable2_1
        STR      R1,[SP, #+0]
        LDR.N    R3,??DataTable2_2
        MOVS     R2,R0
        MOVS     R1,#+3
        LDR.N    R0,??DataTable2_3
          CFI FunCall _ZN12PowerControlC1EjR3ADCILi6EER5TimerPP10led_driverjjjj
        BL       _ZN12PowerControlC1EjR3ADCILi6EER5TimerPP10led_driverjjjj
        ADD      SP,SP,#+20
          CFI CFA R13+4
        POP      {PC}             ;; return
          CFI EndBlock cfiBlock0

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
adc_unite:
        DS8 208

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
power_manager:
        DS8 48
//   15 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function main
        THUMB
//   16 int main()
//   17 {
main:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//   18     sys_timer.setIRQ(0, TIMER_1MS_INT_PRIORITY);
        LDR.N    R4,??DataTable2_2
        MOVS     R2,#+5
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN5Timer6setIRQEhh
        BL       _ZN5Timer6setIRQEhh
//   19     sys_timer.setCallback(sys_timer_callback);
        LDR.N    R1,??DataTable2_4
        MOVS     R0,R4
          CFI FunCall _ZN5Timer11setCallbackEPFvjE
        BL       _ZN5Timer11setCallbackEPFvjE
//   20     sys_timer.init(7, 125, true);
        MOVS     R3,#+1
        MOVS     R2,#+125
        MOVS     R1,#+7
        MOVS     R0,R4
          CFI FunCall _ZN5Timer4initEjjb
        BL       _ZN5Timer4initEjjb
//   21     
//   22     power_manager.config(CHRG_MAX_CURRENT);
        LDR.N    R4,??DataTable2_3
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN12PowerControl6configE15EChargeCurrents
        BL       _ZN12PowerControl6configE15EChargeCurrents
//   23     
//   24     bl_btn_led.run(1);
        MOVS     R1,#+1
        LDR.N    R0,??DataTable2_5
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   25     kb_led.run(3);
        MOVS     R1,#+3
        LDR.N    R0,??DataTable2_6
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   26     btn_pr_led.run(7);
        MOVS     R1,#+7
        LDR.N    R0,??DataTable2_7
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   27     
//   28   	while(1)
//   29   	{        
//   30         red_led.run(1);
??main_0:
        MOVS     R1,#+1
        LDR.N    R0,??DataTable2_8
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   31         power_manager.handle();
        MOVS     R0,R4
          CFI FunCall _ZN12PowerControl6handleEv
        BL       _ZN12PowerControl6handleEv
        B.N      ??main_0
//   32   	}
//   33 }
          CFI EndBlock cfiBlock1
//   34 
//   35 // because this is template of class, definition of irqhandler done in file where implementation of template is.

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function _Z12adc_callbackj
          CFI NoCalls
        THUMB
//   36 void adc_callback(uint32_t value) { return; }
_Z12adc_callbackj:
        BX       LR               ;; return
          CFI EndBlock cfiBlock2

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function SAADC_IRQHandler
        THUMB
//   37 extern "C" void SAADC_IRQHandler() { adc_unite.onIRQ(); }   
SAADC_IRQHandler:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
        LDR.N    R0,??DataTable2
          CFI FunCall _ZN3ADCILi6EE5onIRQEv
        BL       _ZN3ADCILi6EE5onIRQEv
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock3

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DATA32
        DC32     adc_unite

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DATA32
        DC32     led_list

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_2:
        DATA32
        DC32     sys_timer

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_3:
        DATA32
        DC32     power_manager

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_4:
        DATA32
        DC32     _Z18sys_timer_callbackj

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_5:
        DATA32
        DC32     bl_btn_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_6:
        DATA32
        DC32     kb_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_7:
        DATA32
        DC32     btn_pr_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_8:
        DATA32
        DC32     red_led

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN5Timer11setCallbackEPFvjE
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _ZN5Timer11setCallbackEPFvjE
          CFI NoCalls
        THUMB
// __interwork __softfp void Timer::setCallback(void (*)(uint32_t))
_ZN5Timer11setCallbackEPFvjE:
        STR      R1,[R0, #+8]
        BX       LR               ;; return
          CFI EndBlock cfiBlock4

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12ADCChannel_tC1E12EADCChannelsfff
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _ZN12ADCChannel_tC1E12EADCChannelsfff
          CFI NoCalls
        THUMB
// __code __interwork __softfp ADCChannel_t::ADCChannel_t(EADCChannels, float, float, float)
_ZN12ADCChannel_tC1E12EADCChannelsfff:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        LDR      R4,[SP, #+8]
        STRB     R1,[R0, #+0]
        STR      R2,[R0, #+4]
        STR      R3,[R0, #+8]
        STR      R4,[R0, #+12]
        MOVS     R5,#+0
        STR      R5,[R0, #+16]
        MOVS     R5,#+0
        STR      R5,[R0, #+20]
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock5

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12ADCChannel_t8scaleRawEs
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN12ADCChannel_t8scaleRawEs
        THUMB
// __interwork __softfp ADCChannel_t &ADCChannel_t::scaleRaw(int16_t)
_ZN12ADCChannel_t8scaleRawEs:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R0,R5
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
          CFI FunCall __aeabi_i2f
        BL       __aeabi_i2f
        LDR      R1,[R4, #+4]
          CFI FunCall __aeabi_fmul
        BL       __aeabi_fmul
        STR      R0,[R4, #+16]
        MOVS     R0,R4
        POP      {R1,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock6

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
          CFI NoCalls
        THUMB
// __code __interwork __softfp ADCConfig_t::ADCConfig_t(EADCGain, EADCPull, EADCAcquisitionTime, EADCReferenceVoltage)
_ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
        LDR      R4,[SP, #+4]
        STRB     R1,[R0, #+0]
        STRB     R2,[R0, #+1]
        STRB     R3,[R0, #+2]
        STRB     R4,[R0, #+3]
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock7

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN3ADCILi6EEC2E14EADCResolution
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _ZN3ADCILi6EEC2E14EADCResolution
        THUMB
// __code __interwork __softfp ADC<6>::subobject ADC(EADCResolution)
_ZN3ADCILi6EEC2E14EADCResolution:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EEC1E14EADCResolution
        BL       _ZN3ADCILi6EEC1E14EADCResolution
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock8

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE7disableEv
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE7disableEv
          CFI NoCalls
        THUMB
// __interwork __softfp void ADC<6>::disable()
_ZN3ADCILi6EE7disableEv:
        MOVS     R1,#+0
        LDR.N    R2,??disable_0   ;; 0x40007500
        STR      R1,[R2, #+0]
        BX       LR               ;; return
        DATA
??disable_0:
        DATA32
        DC32     0x40007500
          CFI EndBlock cfiBlock9

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EEC1E14EADCResolution
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function _ZN3ADCILi6EEC1E14EADCResolution
        THUMB
// __code __interwork __softfp ADC<6>::ADC(EADCResolution)
_ZN3ADCILi6EEC1E14EADCResolution:
        PUSH     {R2-R8,LR}
          CFI R14 Frame(CFA, -4)
          CFI R8 Frame(CFA, -8)
          CFI R7 Frame(CFA, -12)
          CFI R6 Frame(CFA, -16)
          CFI R5 Frame(CFA, -20)
          CFI R4 Frame(CFA, -24)
          CFI CFA R13+32
        MOVS     R4,R0
        MOVS     R5,R1
        LDR.N    R6,??ADC_0       ;; 0x43960000
        MOVS     R0,#+1056964608
        STR      R0,[SP, #+0]
        MOVS     R3,R6
        LDR.N    R2,??ADC_0+0x4   ;; 0x4028c000
        MOVS     R1,#+5
        MOVS     R0,R4
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        LDR.N    R0,??ADC_0+0x8   ;; 0x3dcccccd
        STR      R0,[SP, #+0]
        MOVS     R3,R6
        LDR.N    R2,??ADC_0+0xC   ;; 0x3fe10000
        MOVS     R1,#+6
        ADDS     R0,R4,#+24
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        MOVS     R0,#+1065353216
        STR      R0,[SP, #+0]
        MOVS     R3,#+0
        LDR.N    R2,??ADC_0+0x10  ;; 0x3f160000
        MOVS     R1,#+1
        ADDS     R0,R4,#+48
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        LDR.N    R6,??ADC_0+0x14  ;; 0x3f610000
        LDR.N    R7,??ADC_0+0x18  ;; 0x43fa0000
        LDR.W    R8,??ADC_0+0x1C  ;; 0x3e99999a
        STR      R8,[SP, #+0]
        MOVS     R3,R7
        MOVS     R2,R6
        MOVS     R1,#+7
        ADDS     R0,R4,#+72
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        STR      R8,[SP, #+0]
        MOVS     R3,R7
        MOVS     R2,R6
        MOVS     R1,#+8
        ADDS     R0,R4,#+96
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        LDR.N    R0,??ADC_0+0x20  ;; 0x3f666666
        STR      R0,[SP, #+0]
        LDR.N    R3,??ADC_0+0x24  ;; 0x42c80000
        MOVS     R2,R6
        MOVS     R1,#+9
        ADDS     R0,R4,#+120
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+0
        MOVS     R1,#+0
        ADDS     R0,R4,#+144
          CFI FunCall _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+0
        MOVS     R1,#+2
        ADDS     R0,R4,#+148
          CFI FunCall _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+1
        MOVS     R1,#+2
        ADDS     R0,R4,#+152
          CFI FunCall _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+2
        MOVS     R1,#+0
        ADDS     R0,R4,#+156
          CFI FunCall _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+2
        MOVS     R1,#+0
        ADDS     R0,R4,#+160
          CFI FunCall _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+0
        MOVS     R1,#+0
        ADDS     R0,R4,#+164
          CFI FunCall _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN11ADCConfig_tC1E8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        STRB     R5,[R4, #+180]
        MOVS     R0,#+0
        STR      R0,[R4, #+184]
        MOVS     R0,#+0
        MOVS     R1,#+0
        STRD     R0,R1,[R4, #+192]
        MOVS     R0,#+1
        STRB     R0,[R4, #+200]
        MOVS     R0,R4
        POP      {R1,R2,R4-R8,PC}  ;; return
        Nop      
        DATA
??ADC_0:
        DATA32
        DC32     0x43960000
        DC32     0x4028c000
        DC32     0x3dcccccd
        DC32     0x3fe10000
        DC32     0x3f160000
        DC32     0x3f610000
        DC32     0x43fa0000
        DC32     0x3e99999a
        DC32     0x3f666666
        DC32     0x42c80000
          CFI EndBlock cfiBlock10

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE6deinitEv
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE6deinitEv
        THUMB
// __interwork __softfp void ADC<6>::deinit()
_ZN3ADCILi6EE6deinitEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        MOVS     R0,#+0
??deinit_1:
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+6
        BGE.N    ??deinit_2
        LDR.N    R1,??deinit_0    ;; 0x40007510
        MOVS     R2,#+0
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        LSLS     R3,R3,#+4
        STR      R2,[R1, R3]
        MOVS     R2,#+0
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        LSLS     R3,R3,#+4
        ADD      R1,R1,R3
        STR      R2,[R1, #+8]
        ADDS     R0,R0,#+1
        B.N      ??deinit_1
??deinit_2:
        MOVS     R0,#+1
        LDR.N    R1,??deinit_0+0x4  ;; 0x40007008
        STR      R0,[R1, #+0]
        MOVS     R0,#+0
        LDR.N    R1,??deinit_0+0x8  ;; 0x40007300
        STR      R0,[R1, #+0]
        MOVS     R0,#+0
        LDR.N    R1,??deinit_0+0xC  ;; 0x40007308
        STR      R0,[R1, #+0]
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE7disableEv
        BL       _ZN3ADCILi6EE7disableEv
        POP      {R4,PC}          ;; return
        DATA
??deinit_0:
        DATA32
        DC32     0x40007510
        DC32     0x40007008
        DC32     0x40007300
        DC32     0x40007308
          CFI EndBlock cfiBlock11

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE5onIRQEv
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE5onIRQEv
        THUMB
// __interwork __softfp void ADC<6>::onIRQ()
_ZN3ADCILi6EE5onIRQEv:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        LDR.N    R1,??onIRQ_0     ;; 0x40007104
        LDR      R0,[R1, #+0]
        CMP      R0,#+0
        BEQ.N    ??onIRQ_1
        MOVS     R0,#+0
        STR      R0,[R1, #+0]
        MOVS     R0,#+0
        LDR.N    R1,??onIRQ_0+0x4  ;; 0x40007100
        STR      R0,[R1, #+0]
        MOVS     R5,#+0
??onIRQ_2:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+6
        BGE.N    ??onIRQ_3
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        ADD      R0,R4,R0, LSL #+1
        LDRSH    R1,[R0, #+168]
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R0,#+24
        MULS     R2,R0,R2
        ADD      R0,R4,R2
          CFI FunCall _ZN12ADCChannel_t8scaleRawEs
        BL       _ZN12ADCChannel_t8scaleRawEs
        ADDS     R5,R5,#+1
        B.N      ??onIRQ_2
??onIRQ_3:
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE6deinitEv
        BL       _ZN3ADCILi6EE6deinitEv
        LDR      R0,[R4, #+184]
        CMP      R0,#+0
        BEQ.N    ??onIRQ_1
        LDR      R0,[R4, #+184]
          CFI FunCall
        BLX      R0
??onIRQ_1:
        POP      {R0,R4,R5,PC}    ;; return
        Nop      
        DATA
??onIRQ_0:
        DATA32
        DC32     0x40007104
        DC32     0x40007100
          CFI EndBlock cfiBlock12

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControlC1EjR3ADCILi6EER5TimerPP10led_driverjjjj
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function _ZN12PowerControlC1EjR3ADCILi6EER5TimerPP10led_driverjjjj
          CFI NoCalls
        THUMB
// __code __interwork __softfp PowerControl::PowerControl(uint32_t, ADC<6> &, Timer &, led_driver **, uint32_t, uint32_t, uint32_t, uint32_t)
_ZN12PowerControlC1EjR3ADCILi6EER5TimerPP10led_driverjjjj:
        PUSH     {R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+20
        LDR      R4,[SP, #+20]
        LDR      R5,[SP, #+24]
        LDR      R6,[SP, #+28]
        LDR      R7,[SP, #+32]
        LDR      R12,[SP, #+36]
        MOVS     LR,#+0
        STRB     LR,[R0, #+0]
        MOVS     LR,#+0
        STRB     LR,[R0, #+1]
        STR      R2,[R0, #+4]
        STR      R3,[R0, #+8]
        STR      R4,[R0, #+12]
        STR      R1,[R0, #+16]
        STR      R7,[R0, #+20]
        STR      R12,[R0, #+24]
        STR      R5,[R0, #+28]
        STR      R6,[R0, #+32]
        MOVS     LR,#+0
        STR      LR,[R0, #+36]
        MOVS     LR,#+0
        STRB     LR,[R0, #+40]
        MOVS     LR,#+0
        STR      LR,[R0, #+44]
        POP      {R4-R7,PC}       ;; return
          CFI EndBlock cfiBlock13

        SECTION `.init_array`:CODE:ROOT(2)
        SECTION_TYPE SHT_INIT_ARRAY, 0
        DATA
        DC32    RELOC_ARM_TARGET1 __sti__routine

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//   38 
//   39 
//   40 
// 
// 256 bytes in section .bss
//   4 bytes in section .init_array
// 838 bytes in section .text
// 
// 184 bytes of CODE memory (+ 658 bytes shared)
// 256 bytes of DATA memory
//
//Errors: none
//Warnings: none
