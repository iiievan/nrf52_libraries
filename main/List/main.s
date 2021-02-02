///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        02/Feb/2021  18:20:23
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\main\main.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EWADE0.tmp
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

        EXTERN _Z18sys_timer_callbackj
        EXTERN _ZN10led_driver3runEi
        EXTERN _ZN5Timer4initEjjb
        EXTERN _ZN5Timer6setIRQEhh
        EXTERN bl_btn_led
        EXTERN btn_pr_led
        EXTERN green_led
        EXTERN kb_led
        EXTERN red_led
        EXTERN sys_timer

        PUBLIC _ZN5Timer11setCallbackEPFvjE
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

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _ZN5Timer11setCallbackEPFvjE
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function _ZN5Timer11setCallbackEPFvjE
          CFI NoCalls
        THUMB
// __interwork __softfp void Timer::setCallback(void (*)(uint32_t))
_ZN5Timer11setCallbackEPFvjE:
        STR      R1,[R0, #+8]
        BX       LR               ;; return
          CFI EndBlock cfiBlock0
//    8 #include "nrf_hw_pwm.h"
//    9 #include "timer.h"
//   10 

        SECTION `.text`:CODE:NOROOT(2)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function main
        THUMB
//   11 int main()
//   12 {
main:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//   13     sys_timer.setIRQ(0, TIMER_1MS_INT_PRIORITY);
        LDR.N    R4,??main_0
        MOVS     R2,#+5
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN5Timer6setIRQEhh
        BL       _ZN5Timer6setIRQEhh
//   14     sys_timer.setCallback(sys_timer_callback);
        LDR.N    R1,??main_0+0x4
        MOVS     R0,R4
          CFI FunCall _ZN5Timer11setCallbackEPFvjE
        BL       _ZN5Timer11setCallbackEPFvjE
//   15     sys_timer.init(7, 125, true);
        MOVS     R3,#+1
        MOVS     R2,#+125
        MOVS     R1,#+7
        MOVS     R0,R4
          CFI FunCall _ZN5Timer4initEjjb
        BL       _ZN5Timer4initEjjb
//   16     
//   17     bl_btn_led.run(1);
        MOVS     R1,#+1
        LDR.N    R0,??main_0+0x8
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   18     kb_led.run(3);
        MOVS     R1,#+3
        LDR.N    R0,??main_0+0xC
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   19     
//   20   	while(1)
//   21   	{
//   22         btn_pr_led.run(1);
??main_1:
        MOVS     R1,#+1
        LDR.N    R0,??main_0+0x10
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   23         red_led.run(1);
        MOVS     R1,#+1
        LDR.N    R0,??main_0+0x14
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
//   24         green_led.run(1);
        MOVS     R1,#+1
        LDR.N    R0,??main_0+0x18
          CFI FunCall _ZN10led_driver3runEi
        BL       _ZN10led_driver3runEi
        B.N      ??main_1
        DATA
??main_0:
        DATA32
        DC32     sys_timer
        DC32     _Z18sys_timer_callbackj
        DC32     bl_btn_led
        DC32     kb_led
        DC32     btn_pr_led
        DC32     red_led
        DC32     green_led
//   25   	}
//   26 }
          CFI EndBlock cfiBlock1

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
// 108 bytes in section .text
// 
// 104 bytes of CODE memory (+ 4 bytes shared)
//
//Errors: none
//Warnings: none
