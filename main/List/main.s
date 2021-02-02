///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        02/Feb/2021  20:02:58
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\main\main.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EW918E.tmp
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
//        E:\cpp\nrf52_libraries\timer\ -On --c++ --no_exceptions --no_rtti)
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
        EXTERN _ZN5Timer4initEjjb
        EXTERN _ZN5Timer6setIRQEhh
        EXTERN bl_btn_led
        EXTERN btn_pr_led
        EXTERN kb_led
        EXTERN red_led
        EXTERN sys_timer

        PUBLIC _ZN12PowerControl12enableChargeE15EChargeCurrents
        PUBLIC _ZN12PowerControl16disableModulePwrEv
        PUBLIC _ZN12PowerControl16disableSupply3V0Ev
        PUBLIC _ZN12PowerControl6configE15EChargeCurrents
        PUBLIC _ZN12PowerControlC1Ejjjjj
        PUBLIC _ZN5Timer11setCallbackEPFvjE
        PUBLIC board_power
        PUBLIC main
        
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
//    9 #include "timer.h"
//   10 #include "PowerControl.h"
//   11 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function __sti__routine
        THUMB
// static __intrinsic __interwork __softfp void __sti__routine()
__sti__routine:
        PUSH     {R5-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+16
//   12 PowerControl board_power(CHRG_EN_PIN, VBAT_MEAS_PIN, MAIN_MEAS_PIN, SYS_3V0_PIN, MODULE_PWR);
        MOVS     R0,#+40
        STR      R0,[SP, #+4]
        MOVS     R0,#+39
        STR      R0,[SP, #+0]
        MOVS     R3,#+28
        MOVS     R2,#+29
        MOVS     R1,#+3
        LDR.N    R0,??DataTable2
          CFI FunCall _ZN12PowerControlC1Ejjjjj
        BL       _ZN12PowerControlC1Ejjjjj
        POP      {R0-R2,PC}       ;; return
          CFI EndBlock cfiBlock0

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_0937e68b24nrf_gpio_pin_port_decodeEPj
          CFI NoCalls
        THUMB
// static __interwork __softfp NRF_GPIO_Type *nrf_gpio_pin_port_decode(uint32_t *)
_ZN29_INTERNAL_8_main_cpp_0937e68b24nrf_gpio_pin_port_decodeEPj:
        MOVS     R1,R0
        LDR      R0,[R1, #+0]
        CMP      R0,#+32
        BCS.N    ??nrf_gpio_pin_port_decode_0
        MOVS     R0,#+1342177280
        B.N      ??nrf_gpio_pin_port_decode_1
??nrf_gpio_pin_port_decode_0:
        LDRB     R0,[R1, #+0]
        ANDS     R0,R0,#0x1F
        STR      R0,[R1, #+0]
        LDR.N    R0,??DataTable2_1  ;; 0x50000300
??nrf_gpio_pin_port_decode_1:
        BX       LR               ;; return
          CFI EndBlock cfiBlock1

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_0937e68b12nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        THUMB
// static __interwork __softfp void nrf_gpio_cfg(uint32_t, nrf_gpio_pin_dir_t, nrf_gpio_pin_input_t, nrf_gpio_pin_pull_t, nrf_gpio_pin_drive_t, nrf_gpio_pin_sense_t)
_ZN29_INTERNAL_8_main_cpp_0937e68b12nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t:
        PUSH     {R0,R4-R8,LR}
          CFI R14 Frame(CFA, -4)
          CFI R8 Frame(CFA, -8)
          CFI R7 Frame(CFA, -12)
          CFI R6 Frame(CFA, -16)
          CFI R5 Frame(CFA, -20)
          CFI R4 Frame(CFA, -24)
          CFI CFA R13+28
        SUB      SP,SP,#+4
          CFI CFA R13+32
        MOVS     R6,R1
        MOVS     R7,R2
        MOV      R8,R3
        LDR      R4,[SP, #+32]
        LDR      R5,[SP, #+36]
        ADD      R0,SP,#+4
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b24nrf_gpio_pin_port_decodeEPj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b24nrf_gpio_pin_port_decodeEPj
        MOVS     R1,R6
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R2,R7
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ORRS     R1,R1,R2, LSL #+1
        MOV      R2,R8
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ORRS     R1,R1,R2, LSL #+2
        MOVS     R2,R4
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ORRS     R1,R1,R2, LSL #+8
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ORRS     R1,R1,R2, LSL #+16
        LDR      R2,[SP, #+4]
        ADD      R2,R0,R2, LSL #+2
        STR      R1,[R2, #+1792]
        POP      {R0,R1,R4-R8,PC}  ;; return
          CFI EndBlock cfiBlock2

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj
        THUMB
// static __interwork __softfp void nrf_gpio_cfg_output(uint32_t)
_ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj:
        PUSH     {R2-R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R0,#+0
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+0
        MOVS     R2,#+1
        MOVS     R1,#+1
        MOVS     R0,R4
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b12nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b12nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        POP      {R0,R1,R4,PC}    ;; return
          CFI EndBlock cfiBlock3

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        THUMB
// static __interwork __softfp void nrf_gpio_cfg_input(uint32_t, nrf_gpio_pin_pull_t)
_ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t:
        PUSH     {R1-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+24
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R0,#+0
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,R5
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MOVS     R2,#+0
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b12nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b12nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        POP      {R0-R2,R4,R5,PC}  ;; return
          CFI EndBlock cfiBlock4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj
        THUMB
// static __interwork __softfp void nrf_gpio_pin_clear(uint32_t)
_ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj:
        PUSH     {R0,R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+12
        SUB      SP,SP,#+4
          CFI CFA R13+16
        ADD      R0,SP,#+4
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b24nrf_gpio_pin_port_decodeEPj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b24nrf_gpio_pin_port_decodeEPj
        MOVS     R4,R0
        MOVS     R1,#+1
        LDR      R0,[SP, #+4]
        LSLS     R1,R1,R0
        MOVS     R0,R4
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b23nrf_gpio_port_out_clearEP13NRF_GPIO_Typej
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b23nrf_gpio_port_out_clearEP13NRF_GPIO_Typej
        POP      {R0,R1,R4,PC}    ;; return
          CFI EndBlock cfiBlock5

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_0937e68b23nrf_gpio_port_out_clearEP13NRF_GPIO_Typej
          CFI NoCalls
        THUMB
// static __interwork __softfp void nrf_gpio_port_out_clear(NRF_GPIO_Type *, uint32_t)
_ZN29_INTERNAL_8_main_cpp_0937e68b23nrf_gpio_port_out_clearEP13NRF_GPIO_Typej:
        STR      R1,[R0, #+1292]
        BX       LR               ;; return
          CFI EndBlock cfiBlock6

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
board_power:
        DS8 20
//   13 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function main
        THUMB
//   14 int main()
//   15 {
main:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//   16     sys_timer.setIRQ(0, TIMER_1MS_INT_PRIORITY);
        LDR.N    R4,??DataTable2_2
        MOVS     R2,#+5
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN5Timer6setIRQEhh
        BL       _ZN5Timer6setIRQEhh
//   17     sys_timer.setCallback(sys_timer_callback);
        LDR.N    R1,??DataTable2_3
        MOVS     R0,R4
          CFI FunCall _ZN5Timer11setCallbackEPFvjE
        BL       _ZN5Timer11setCallbackEPFvjE
//   18     sys_timer.init(7, 125, true);
        MOVS     R3,#+1
        MOVS     R2,#+125
        MOVS     R1,#+7
        MOVS     R0,R4
          CFI FunCall _ZN5Timer4initEjjb
        BL       _ZN5Timer4initEjjb
//   19     
//   20     board_power.config(CHRG_MAX_CURRENT);
        MOVS     R1,#+0
        LDR.N    R0,??DataTable2
          CFI FunCall _ZN12PowerControl6configE15EChargeCurrents
        BL       _ZN12PowerControl6configE15EChargeCurrents
//   21     
//   22     bl_btn_led.run(1);
        MOVS     R1,#+1
        LDR.N    R0,??DataTable2_4
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   23     kb_led.run(3);
        MOVS     R1,#+3
        LDR.N    R0,??DataTable2_5
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   24     btn_pr_led.run(7);
        MOVS     R1,#+7
        LDR.N    R0,??DataTable2_6
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   25     
//   26   	while(1)
//   27   	{        
//   28         red_led.run(1);
??main_0:
        MOVS     R1,#+1
        LDR.N    R0,??DataTable2_7
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
        B.N      ??main_0
//   29   	}
//   30 }
          CFI EndBlock cfiBlock7

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DATA32
        DC32     board_power

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DATA32
        DC32     0x50000300

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
        DC32     _Z18sys_timer_callbackj

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_4:
        DATA32
        DC32     bl_btn_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_5:
        DATA32
        DC32     kb_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_6:
        DATA32
        DC32     btn_pr_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_7:
        DATA32
        DC32     red_led

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN5Timer11setCallbackEPFvjE
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _ZN5Timer11setCallbackEPFvjE
          CFI NoCalls
        THUMB
// __interwork __softfp void Timer::setCallback(void (*)(uint32_t))
_ZN5Timer11setCallbackEPFvjE:
        STR      R1,[R0, #+8]
        BX       LR               ;; return
          CFI EndBlock cfiBlock8

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControlC1Ejjjjj
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function _ZN12PowerControlC1Ejjjjj
          CFI NoCalls
        THUMB
// __code __interwork __softfp PowerControl::PowerControl(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t)
_ZN12PowerControlC1Ejjjjj:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        LDR      R4,[SP, #+8]
        LDR      R5,[SP, #+12]
        STR      R1,[R0, #+0]
        STR      R4,[R0, #+4]
        STR      R5,[R0, #+8]
        STR      R2,[R0, #+12]
        STR      R3,[R0, #+16]
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock9

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN12PowerControl6configE15EChargeCurrents
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function _ZN12PowerControl6configE15EChargeCurrents
        THUMB
// __interwork __softfp void PowerControl::config(EChargeCurrents)
_ZN12PowerControl6configE15EChargeCurrents:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
        LDR      R0,[R4, #+4]
        CMN      R0,#+1
        BEQ.N    ??config_1
        LDR      R0,[R4, #+4]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj
        LDR.N    R0,??config_0    ;; 0x50000700
        LDR      R1,[R4, #+4]
        LDR      R1,[R0, R1, LSL #+2]
        ORRS     R1,R1,#0x200
        LDR      R2,[R4, #+4]
        STR      R1,[R0, R2, LSL #+2]
??config_1:
        LDR      R0,[R4, #+8]
        CMN      R0,#+1
        BEQ.N    ??config_2
        LDR      R0,[R4, #+8]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj
??config_2:
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN12PowerControl12enableChargeE15EChargeCurrents
        BL       _ZN12PowerControl12enableChargeE15EChargeCurrents
        MOVS     R0,R4
          CFI FunCall _ZN12PowerControl16disableSupply3V0Ev
        BL       _ZN12PowerControl16disableSupply3V0Ev
        MOVS     R0,R4
          CFI FunCall _ZN12PowerControl16disableModulePwrEv
        BL       _ZN12PowerControl16disableModulePwrEv
        POP      {R0,R4,R5,PC}    ;; return
        DATA
??config_0:
        DATA32
        DC32     0x50000700
          CFI EndBlock cfiBlock10

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControl12enableChargeE15EChargeCurrents
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function _ZN12PowerControl12enableChargeE15EChargeCurrents
        THUMB
// __interwork __softfp void PowerControl::enableCharge(EChargeCurrents)
_ZN12PowerControl12enableChargeE15EChargeCurrents:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??enableCharge_0
        CMP      R0,#+2
        BEQ.N    ??enableCharge_1
        BCC.N    ??enableCharge_2
        B.N      ??enableCharge_3
??enableCharge_0:
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b19nrf_gpio_cfg_outputEj
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj
        B.N      ??enableCharge_4
??enableCharge_2:
        MOVS     R1,#+0
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        B.N      ??enableCharge_4
??enableCharge_1:
        MOVS     R1,#+3
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        B.N      ??enableCharge_4
??enableCharge_3:
        MOVS     R1,#+3
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
??enableCharge_4:
        POP      {R0,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock11

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControl16disableModulePwrEv
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function _ZN12PowerControl16disableModulePwrEv
        THUMB
// __interwork __softfp void PowerControl::disableModulePwr()
_ZN12PowerControl16disableModulePwrEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        LDR      R0,[R4, #+8]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock12

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControl16disableSupply3V0Ev
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function _ZN12PowerControl16disableSupply3V0Ev
        THUMB
// __interwork __softfp void PowerControl::disableSupply3V0()
_ZN12PowerControl16disableSupply3V0Ev:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        LDR      R0,[R4, #+4]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj
        BL       _ZN29_INTERNAL_8_main_cpp_0937e68b18nrf_gpio_pin_clearEj
        POP      {R4,PC}          ;; return
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
// 
//  20 bytes in section .bss
//   4 bytes in section .init_array
// 512 bytes in section .text
// 
// 322 bytes of CODE memory (+ 194 bytes shared)
//  20 bytes of DATA memory
//
//Errors: none
//Warnings: none
