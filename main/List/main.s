///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        03/Feb/2021  19:58:18
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\main\main.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EW7155.tmp
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
        EXTERN _ZN5Timer4initEjjb
        EXTERN _ZN5Timer6setIRQEhh
        EXTERN __aeabi_fmul
        EXTERN __aeabi_i2f
        EXTERN bl_btn_led
        EXTERN btn_pr_led
        EXTERN kb_led
        EXTERN red_led
        EXTERN sys_timer

        PUBLIC SAADC_IRQHandler
        PUBLIC _Z12adc_callbackj
        PUBLIC _ZN12ADCChannel_t8scaleRawEs
        PUBLIC _ZN12ADCChannel_tC1E12EADCChannelsfff
        PUBLIC _ZN12PowerControl12enableChargeE15EChargeCurrents
        PUBLIC _ZN12PowerControl16disableModulePwrEv
        PUBLIC _ZN12PowerControl16disableSupply3V0Ev
        PUBLIC _ZN12PowerControl6configE15EChargeCurrents
        PUBLIC _ZN12PowerControlC1Ejjjjj
        PUBLIC _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        PUBLIC _ZN3ADCILi6EE5onIRQEv
        PUBLIC _ZN3ADCILi6EE6enableEv
        PUBLIC _ZN3ADCILi6EE7disableEv
        PUBLIC _ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
        PUBLIC _ZN3ADCILi6EEC2E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
        PUBLIC _ZN5Timer11setCallbackEPFvjE
        PUBLIC adc_unite
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
//    9 #include "ADC.h"
//   10 #include "ADC.cpp"
//   11 #include "timer.h"
//   12 #include "PowerControl.h"
//   13 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function __sti__routine
        THUMB
// static __intrinsic __interwork __softfp void __sti__routine()
__sti__routine:
        PUSH     {R5-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+16
//   14 ADC<6> adc_unite(GAIN_1DIV6, BYPASS, ACQ_20us, RES_12B);
        MOVS     R0,#+2
        STR      R0,[SP, #+0]
        MOVS     R3,#+4
        MOVS     R2,#+0
        MOVS     R1,#+0
        LDR.N    R0,??DataTable3
          CFI FunCall _ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
        BL       _ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
//   15 PowerControl board_power(CHRG_EN_PIN, VBAT_MEAS_PIN, MAIN_MEAS_PIN, SYS_3V0_PIN, MODULE_PWR);
        MOVS     R0,#+40
        STR      R0,[SP, #+4]
        MOVS     R0,#+39
        STR      R0,[SP, #+0]
        MOVS     R3,#+28
        MOVS     R2,#+29
        MOVS     R1,#+3
        LDR.N    R0,??DataTable3_1
          CFI FunCall _ZN12PowerControlC1Ejjjjj
        BL       _ZN12PowerControlC1Ejjjjj
        POP      {R0-R2,PC}       ;; return
          CFI EndBlock cfiBlock0

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_6570f55724nrf_gpio_pin_port_decodeEPj
          CFI NoCalls
        THUMB
// static __interwork __softfp NRF_GPIO_Type *nrf_gpio_pin_port_decode(uint32_t *)
_ZN29_INTERNAL_8_main_cpp_6570f55724nrf_gpio_pin_port_decodeEPj:
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
        LDR.N    R0,??DataTable3_2  ;; 0x50000300
??nrf_gpio_pin_port_decode_1:
        BX       LR               ;; return
          CFI EndBlock cfiBlock1

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_6570f55712nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        THUMB
// static __interwork __softfp void nrf_gpio_cfg(uint32_t, nrf_gpio_pin_dir_t, nrf_gpio_pin_input_t, nrf_gpio_pin_pull_t, nrf_gpio_pin_drive_t, nrf_gpio_pin_sense_t)
_ZN29_INTERNAL_8_main_cpp_6570f55712nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t:
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55724nrf_gpio_pin_port_decodeEPj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55724nrf_gpio_pin_port_decodeEPj
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
          CFI Function _ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj
        THUMB
// static __interwork __softfp void nrf_gpio_cfg_output(uint32_t)
_ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj:
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55712nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55712nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        POP      {R0,R1,R4,PC}    ;; return
          CFI EndBlock cfiBlock3

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        THUMB
// static __interwork __softfp void nrf_gpio_cfg_input(uint32_t, nrf_gpio_pin_pull_t)
_ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t:
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55712nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55712nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        POP      {R0-R2,R4,R5,PC}  ;; return
          CFI EndBlock cfiBlock4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj
        THUMB
// static __interwork __softfp void nrf_gpio_pin_clear(uint32_t)
_ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj:
        PUSH     {R0,R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+12
        SUB      SP,SP,#+4
          CFI CFA R13+16
        ADD      R0,SP,#+4
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55724nrf_gpio_pin_port_decodeEPj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55724nrf_gpio_pin_port_decodeEPj
        MOVS     R4,R0
        MOVS     R1,#+1
        LDR      R0,[SP, #+4]
        LSLS     R1,R1,R0
        MOVS     R0,R4
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55723nrf_gpio_port_out_clearEP13NRF_GPIO_Typej
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55723nrf_gpio_port_out_clearEP13NRF_GPIO_Typej
        POP      {R0,R1,R4,PC}    ;; return
          CFI EndBlock cfiBlock5

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN29_INTERNAL_8_main_cpp_6570f55723nrf_gpio_port_out_clearEP13NRF_GPIO_Typej
          CFI NoCalls
        THUMB
// static __interwork __softfp void nrf_gpio_port_out_clear(NRF_GPIO_Type *, uint32_t)
_ZN29_INTERNAL_8_main_cpp_6570f55723nrf_gpio_port_out_clearEP13NRF_GPIO_Typej:
        STR      R1,[R0, #+1292]
        BX       LR               ;; return
          CFI EndBlock cfiBlock6

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
adc_unite:
        DS8 184

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
board_power:
        DS8 20
//   16 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function main
        THUMB
//   17 int main()
//   18 {
main:
        PUSH     {R2-R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+16
//   19     sys_timer.setIRQ(0, TIMER_1MS_INT_PRIORITY);
        LDR.N    R4,??DataTable3_3
        MOVS     R2,#+5
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN5Timer6setIRQEhh
        BL       _ZN5Timer6setIRQEhh
//   20     sys_timer.setCallback(sys_timer_callback);
        LDR.N    R1,??DataTable3_4
        MOVS     R0,R4
          CFI FunCall _ZN5Timer11setCallbackEPFvjE
        BL       _ZN5Timer11setCallbackEPFvjE
//   21     sys_timer.init(7, 125, true);
        MOVS     R3,#+1
        MOVS     R2,#+125
        MOVS     R1,#+7
        MOVS     R0,R4
          CFI FunCall _ZN5Timer4initEjjb
        BL       _ZN5Timer4initEjjb
//   22     
//   23     adc_unite.configChannel(AIN_4,GAIN_1DIV4, BYPASS);
        LDR.N    R4,??DataTable3
        MOVS     R0,#+0
        STR      R0,[SP, #+4]
        MOVS     R0,#+4
        STR      R0,[SP, #+0]
        MOVS     R3,#+0
        MOVS     R2,#+2
        MOVS     R1,#+5
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
//   24     adc_unite.configChannel(AIN_5,GAIN_1DIV4, PULLDOWN);
        MOVS     R0,#+0
        STR      R0,[SP, #+4]
        MOVS     R0,#+4
        STR      R0,[SP, #+0]
        MOVS     R3,#+1
        MOVS     R2,#+2
        MOVS     R1,#+6
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
//   25     adc_unite.configChannel(AIN_6,GAIN_1DIV6, PULLUP);
        MOVS     R0,#+0
        STR      R0,[SP, #+4]
        MOVS     R0,#+4
        STR      R0,[SP, #+0]
        MOVS     R3,#+2
        MOVS     R2,#+0
        MOVS     R1,#+7
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
//   26     adc_unite.configChannel(AIN_7,GAIN_1DIV6, PULLUP);
        MOVS     R0,#+0
        STR      R0,[SP, #+4]
        MOVS     R0,#+4
        STR      R0,[SP, #+0]
        MOVS     R3,#+2
        MOVS     R2,#+0
        MOVS     R1,#+8
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
        BL       _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
//   27     
//   28     board_power.config(CHRG_MAX_CURRENT);
        MOVS     R1,#+0
        LDR.N    R0,??DataTable3_1
          CFI FunCall _ZN12PowerControl6configE15EChargeCurrents
        BL       _ZN12PowerControl6configE15EChargeCurrents
//   29     
//   30     bl_btn_led.run(1);
        MOVS     R1,#+1
        LDR.N    R0,??DataTable3_5
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   31     kb_led.run(3);
        MOVS     R1,#+3
        LDR.N    R0,??DataTable3_6
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   32     btn_pr_led.run(7);
        MOVS     R1,#+7
        LDR.N    R0,??DataTable3_7
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   33     
//   34   	while(1)
//   35   	{        
//   36         red_led.run(1);
??main_0:
        MOVS     R1,#+1
        LDR.N    R0,??DataTable3_8
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
        B.N      ??main_0
//   37   	}
//   38 }
          CFI EndBlock cfiBlock7
//   39 
//   40 // because this is template of class, definition of irqhandler done in file where implementation of template is.

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _Z12adc_callbackj
          CFI NoCalls
        THUMB
//   41 void adc_callback(uint32_t value) { return; }
_Z12adc_callbackj:
        BX       LR               ;; return
          CFI EndBlock cfiBlock8

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function SAADC_IRQHandler
        THUMB
//   42 extern "C" void SAADC_IRQHandler() { adc_unite.onIRQ(); }   
SAADC_IRQHandler:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
        LDR.N    R0,??DataTable3
          CFI FunCall _ZN3ADCILi6EE5onIRQEv
        BL       _ZN3ADCILi6EE5onIRQEv
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock9

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3:
        DATA32
        DC32     adc_unite

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_1:
        DATA32
        DC32     board_power

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_2:
        DATA32
        DC32     0x50000300

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_3:
        DATA32
        DC32     sys_timer

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_4:
        DATA32
        DC32     _Z18sys_timer_callbackj

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_5:
        DATA32
        DC32     bl_btn_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_6:
        DATA32
        DC32     kb_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_7:
        DATA32
        DC32     btn_pr_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable3_8:
        DATA32
        DC32     red_led

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN5Timer11setCallbackEPFvjE
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function _ZN5Timer11setCallbackEPFvjE
          CFI NoCalls
        THUMB
// __interwork __softfp void Timer::setCallback(void (*)(uint32_t))
_ZN5Timer11setCallbackEPFvjE:
        STR      R1,[R0, #+8]
        BX       LR               ;; return
          CFI EndBlock cfiBlock10

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12ADCChannel_tC1E12EADCChannelsfff
          CFI Block cfiBlock11 Using cfiCommon0
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
          CFI EndBlock cfiBlock11

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12ADCChannel_t8scaleRawEs
          CFI Block cfiBlock12 Using cfiCommon0
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
          CFI EndBlock cfiBlock12

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN3ADCILi6EEC2E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function _ZN3ADCILi6EEC2E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
        THUMB
// __code __interwork __softfp ADC<6>::subobject ADC(EADCGain, EADCPull, EADCAcquisitionTime, EADCResolution)
_ZN3ADCILi6EEC2E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution:
        PUSH     {R2-R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+16
        MOVS     R4,R0
        LDRB     R0,[SP, #+16]
        STR      R0,[SP, #+0]
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
        BL       _ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
        POP      {R1,R2,R4,PC}    ;; return
          CFI EndBlock cfiBlock13

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE6enableEv
          CFI Block cfiBlock14 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE6enableEv
          CFI NoCalls
        THUMB
// __interwork __softfp void ADC<6>::enable()
_ZN3ADCILi6EE6enableEv:
        MOVS     R1,#+1
        LDR.N    R2,??enable_0    ;; 0x40007500
        STR      R1,[R2, #+0]
        BX       LR               ;; return
        DATA
??enable_0:
        DATA32
        DC32     0x40007500
          CFI EndBlock cfiBlock14

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE7disableEv
          CFI Block cfiBlock15 Using cfiCommon0
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
          CFI EndBlock cfiBlock15

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
          CFI Block cfiBlock16 Using cfiCommon0
          CFI Function _ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution
        THUMB
// __code __interwork __softfp ADC<6>::ADC(EADCGain, EADCPull, EADCAcquisitionTime, EADCResolution)
_ZN3ADCILi6EEC1E8EADCGain8EADCPull19EADCAcquisitionTime14EADCResolution:
        PUSH     {R3-R11,LR}
          CFI R14 Frame(CFA, -4)
          CFI R11 Frame(CFA, -8)
          CFI R10 Frame(CFA, -12)
          CFI R9 Frame(CFA, -16)
          CFI R8 Frame(CFA, -20)
          CFI R7 Frame(CFA, -24)
          CFI R6 Frame(CFA, -28)
          CFI R5 Frame(CFA, -32)
          CFI R4 Frame(CFA, -36)
          CFI CFA R13+40
        MOVS     R5,R0
        MOVS     R6,R1
        MOVS     R7,R2
        MOV      R8,R3
        LDR      R4,[SP, #+40]
        LDR.W    R9,??ADC_0       ;; 0x43960000
        MOVS     R0,#+1056964608
        STR      R0,[SP, #+0]
        MOV      R3,R9
        LDR.N    R2,??ADC_0+0x4   ;; 0x4028c000
        MOVS     R1,#+1
        MOVS     R0,R5
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        LDR.N    R0,??ADC_0+0x8   ;; 0x3dcccccd
        STR      R0,[SP, #+0]
        MOV      R3,R9
        LDR.N    R2,??ADC_0+0xC   ;; 0x3fe10000
        MOVS     R1,#+5
        ADDS     R0,R5,#+24
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        MOVS     R0,#+1065353216
        STR      R0,[SP, #+0]
        MOVS     R3,#+0
        LDR.N    R2,??ADC_0+0x10  ;; 0x3f160000
        MOVS     R1,#+6
        ADDS     R0,R5,#+48
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        LDR.W    R9,??ADC_0+0x14  ;; 0x3f610000
        LDR.W    R10,??ADC_0+0x18  ;; 0x43fa0000
        LDR.W    R11,??ADC_0+0x1C  ;; 0x3e99999a
        STR      R11,[SP, #+0]
        MOV      R3,R10
        MOV      R2,R9
        MOVS     R1,#+7
        ADDS     R0,R5,#+72
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        STR      R11,[SP, #+0]
        MOV      R3,R10
        MOV      R2,R9
        MOVS     R1,#+8
        ADDS     R0,R5,#+96
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        LDR.N    R0,??ADC_0+0x20  ;; 0x3f666666
        STR      R0,[SP, #+0]
        LDR.N    R3,??ADC_0+0x24  ;; 0x42c80000
        MOV      R2,R9
        MOVS     R1,#+9
        ADDS     R0,R5,#+120
          CFI FunCall _ZN12ADCChannel_tC1E12EADCChannelsfff
        BL       _ZN12ADCChannel_tC1E12EADCChannelsfff
        MOVS     R0,#+0
        STR      R0,[R5, #+160]
        MOVS     R0,#+0
        MOVS     R1,#+0
        STRD     R0,R1,[R5, #+168]
        MOVS     R0,#+1
        STRB     R0,[R5, #+176]
        STRB     R4,[R5, #+156]
        MOVS     R0,R5
          CFI FunCall _ZN3ADCILi6EE6enableEv
        BL       _ZN3ADCILi6EE6enableEv
        MOVS     R0,#+0
??ADC_1:
        CMP      R0,#+6
        BCS.N    ??ADC_2
        MOVS     R1,#+24
        MUL      R1,R1,R0
        LDRB     R1,[R5, R1]
        LDR.N    R2,??ADC_0+0x28  ;; 0x40007510
        LSLS     R3,R0,#+4
        STR      R1,[R2, R3]
        ADDS     R0,R0,#+1
        B.N      ??ADC_1
??ADC_2:
        MOVS     R1,#+0
??ADC_3:
        CMP      R1,#+6
        BCS.N    ??ADC_4
        MOV      R0,R8
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        MOVS     R2,R6
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LSLS     R2,R2,#+8
        ORRS     R2,R2,R0, LSL #+16
        MOVS     R0,R7
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        ORRS     R2,R0,R2
        LDR.N    R0,??ADC_0+0x28  ;; 0x40007510
        LSLS     R3,R1,#+4
        ADD      R0,R0,R3
        STR      R2,[R0, #+8]
        ADDS     R1,R1,#+1
        B.N      ??ADC_3
??ADC_4:
        MOVS     R0,R5
          CFI FunCall _ZN3ADCILi6EE7disableEv
        BL       _ZN3ADCILi6EE7disableEv
        MOVS     R0,R5
        POP      {R1,R4-R11,PC}   ;; return
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
        DC32     0x40007510
          CFI EndBlock cfiBlock16

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
          CFI Block cfiBlock17 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage
          CFI NoCalls
        THUMB
// __interwork __softfp void ADC<6>::configChannel(EADCChannels, EADCGain, EADCPull, EADCAcquisitionTime, EADCReferenceVoltage)
_ZN3ADCILi6EE13configChannelE12EADCChannels8EADCGain8EADCPull19EADCAcquisitionTime20EADCReferenceVoltage:
        PUSH     {R4-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+20
        LDR      R5,[SP, #+20]
        LDR      R4,[SP, #+24]
        MOVS     R7,#+0
??configChannel_1:
        MOVS     R6,R7
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        CMP      R6,#+6
        BGE.N    ??configChannel_2
        MOV      R12,R7
        UXTB     R12,R12          ;; ZeroExt  R12,R12,#+24,#+24
        MOVS     R6,#+24
        MUL      R12,R6,R12
        LDRB     R6,[R0, R12]
        MOV      R12,R1
        UXTB     R12,R12          ;; ZeroExt  R12,R12,#+24,#+24
        CMP      R6,R12
        BEQ.N    ??configChannel_2
??configChannel_3:
        ADDS     R7,R7,#+1
        B.N      ??configChannel_1
??configChannel_2:
        MOVS     R6,R5
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        MOV      R12,R4
        UXTB     R12,R12          ;; ZeroExt  R12,R12,#+24,#+24
        LSLS     R12,R12,#+12
        ORRS     R12,R12,R6, LSL #+16
        MOVS     R6,R2
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        ORRS     R12,R12,R6, LSL #+8
        MOVS     R6,R3
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        ORRS     R12,R6,R12
        LDR.N    R6,??configChannel_0  ;; 0x40007510
        MOV      LR,R7
        UXTB     LR,LR            ;; ZeroExt  LR,LR,#+24,#+24
        LSLS     LR,LR,#+4
        ADD      R6,R6,LR
        STR      R12,[R6, #+8]
        POP      {R4-R7,PC}       ;; return
        DATA
??configChannel_0:
        DATA32
        DC32     0x40007510
          CFI EndBlock cfiBlock17

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE5onIRQEv
          CFI Block cfiBlock18 Using cfiCommon0
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
        LDRSH    R1,[R0, #+144]
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
        LDR      R0,[R4, #+160]
        CMP      R0,#+0
        BEQ.N    ??onIRQ_1
        LDR      R0,[R4, #+160]
          CFI FunCall
        BLX      R0
??onIRQ_1:
        POP      {R0,R4,R5,PC}    ;; return
        DATA
??onIRQ_0:
        DATA32
        DC32     0x40007104
        DC32     0x40007100
          CFI EndBlock cfiBlock18

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControlC1Ejjjjj
          CFI Block cfiBlock19 Using cfiCommon0
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
          CFI EndBlock cfiBlock19

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN12PowerControl6configE15EChargeCurrents
          CFI Block cfiBlock20 Using cfiCommon0
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj
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
          CFI EndBlock cfiBlock20

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControl12enableChargeE15EChargeCurrents
          CFI Block cfiBlock21 Using cfiCommon0
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55719nrf_gpio_cfg_outputEj
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj
        B.N      ??enableCharge_4
??enableCharge_2:
        MOVS     R1,#+0
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        B.N      ??enableCharge_4
??enableCharge_1:
        MOVS     R1,#+3
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        B.N      ??enableCharge_4
??enableCharge_3:
        MOVS     R1,#+0
        LDR      R0,[R4, #+0]
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_cfg_inputEj19nrf_gpio_pin_pull_t
??enableCharge_4:
        POP      {R0,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock21

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControl16disableModulePwrEv
          CFI Block cfiBlock22 Using cfiCommon0
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock22

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN12PowerControl16disableSupply3V0Ev
          CFI Block cfiBlock23 Using cfiCommon0
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
          CFI FunCall _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj
        BL       _ZN29_INTERNAL_8_main_cpp_6570f55718nrf_gpio_pin_clearEj
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock23

        SECTION `.init_array`:CODE:ROOT(2)
        SECTION_TYPE SHT_INIT_ARRAY, 0
        DATA
        DC32    RELOC_ARM_TARGET1 __sti__routine

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//   43 
//   44 
//   45 
// 
//   204 bytes in section .bss
//     4 bytes in section .init_array
// 1'204 bytes in section .text
// 
// 436 bytes of CODE memory (+ 772 bytes shared)
// 204 bytes of DATA memory
//
//Errors: none
//Warnings: none
