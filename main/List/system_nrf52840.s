///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        02/Feb/2021  11:39:10
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\cmsis\system_nrf52840.c
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EW5113.tmp
//        (E:\cpp\nrf52_libraries\cmsis\system_nrf52840.c -D NRF52840_XXAA -D
//        CONFIG_NFCT_PINS_AS_GPIOS -D APP_TIMER_V2 -D
//        APP_TIMER_V2_RTC1_ENABLED -D DEBUG -D DEBUG_NRF -D FLOAT_ABI_HARD
//        -lCN E:\cpp\nrf52_libraries\main\List -lA
//        E:\cpp\nrf52_libraries\main\List -o E:\cpp\nrf52_libraries\main\Obj
//        --no_cse --no_unroll --no_inline --no_code_motion --no_tbaa
//        --no_clustering --no_scheduling --debug --endian=little
//        --cpu=Cortex-M3 -e --fpu=None --dlib_config "C:\Program Files
//        (x86)\IAR Systems\Embedded Workbench
//        8.3\arm\inc\c\DLib_Config_Normal.h" -I E:\cpp\nrf52_libraries\fsm\ -I
//        E:\cpp\nrf52_libraries\pwm\ -I E:\cpp\nrf52_libraries\spi\ -I
//        E:\cpp\nrf52_libraries\usb\ -I E:\cpp\nrf52_libraries\main\ -I
//        E:\cpp\nrf52_libraries\cmsis\ -I E:\cpp\nrf52_libraries\cmsis\device\
//        -I E:\cpp\nrf52_libraries\cmsis\include\ -On --c++ --no_exceptions
//        --no_rtti)
//    Locale       =  C
//    List file    =  E:\cpp\nrf52_libraries\main\List\system_nrf52840.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__CPP_Exceptions", "Disabled"
        RTMODEL "__CPP_Language", "C++14"
        RTMODEL "__SystemLibrary", "DLib"
        RTMODEL "__dlib_version", "6"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1

        PUBLIC SystemCoreClock
        PUBLIC SystemCoreClockUpdate
        PUBLIC SystemInit
        
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
        
// E:\cpp\nrf52_libraries\cmsis\system_nrf52840.c
//    1 /*
//    2 
//    3 Copyright (c) 2009-2018 ARM Limited. All rights reserved.
//    4 
//    5     SPDX-License-Identifier: Apache-2.0
//    6 
//    7 Licensed under the Apache License, Version 2.0 (the License); you may
//    8 not use this file except in compliance with the License.
//    9 You may obtain a copy of the License at
//   10 
//   11     www.apache.org/licenses/LICENSE-2.0
//   12 
//   13 Unless required by applicable law or agreed to in writing, software
//   14 distributed under the License is distributed on an AS IS BASIS, WITHOUT
//   15 WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   16 See the License for the specific language governing permissions and
//   17 limitations under the License.
//   18 
//   19 NOTICE: This file has been modified by Nordic Semiconductor ASA.
//   20 
//   21 */
//   22 
//   23 /* NOTE: Template files (including this one) are application specific and therefore expected to
//   24    be copied into the application project folder prior to its use! */
//   25 #ifdef NRF52840_XXAA
//   26 
//   27 #include <stdint.h>
//   28 #include <stdbool.h>
//   29 #include <intrinsics.h>
//   30 #include "nrf.h"

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6716NVIC_SystemResetEv
          CFI NoCalls
        THUMB
// static __interwork __softfp void NVIC_SystemReset()
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a6716NVIC_SystemResetEv:
        DSB      SY
        LDR.N    R1,??DataTable9  ;; 0xe000ed0c
        LDR      R2,[R1, #+0]
        ANDS     R2,R2,#0x700
        LDR.N    R0,??DataTable9_1  ;; 0x5fa0004
        ORRS     R2,R0,R2
        STR      R2,[R1, #+0]
        DSB      SY
??NVIC_SystemReset_0:
        Nop      
        B.N      ??NVIC_SystemReset_0
          CFI EndBlock cfiBlock0
//   31 #include "system_nrf52840.h"
//   32 
//   33 /*lint ++flb "Enter library region" */
//   34 
//   35 #define __SYSTEM_CLOCK_64M      (64000000UL)
//   36 #define VECT_TAB_OFFSET         0x2000
//   37 
//   38 static bool errata_36(void);
//   39 static bool errata_66(void);
//   40 static bool errata_98(void);
//   41 static bool errata_103(void);
//   42 static bool errata_115(void);
//   43 static bool errata_120(void);
//   44 static bool errata_136(void);
//   45 
//   46 
//   47 #if defined ( __CC_ARM )
//   48     uint32_t SystemCoreClock __attribute__((used)) = __SYSTEM_CLOCK_64M;
//   49 #elif defined ( __ICCARM__ )

        SECTION `.data`:DATA:REORDER:ROOT(2)
        DATA
//   50     __root uint32_t SystemCoreClock = __SYSTEM_CLOCK_64M;
SystemCoreClock:
        DATA32
        DC32 64'000'000
//   51 #elif defined ( __GNUC__ )
//   52     uint32_t SystemCoreClock __attribute__((used)) = __SYSTEM_CLOCK_64M;
//   53 #endif
//   54 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function SystemCoreClockUpdate
          CFI NoCalls
        THUMB
//   55 void SystemCoreClockUpdate(void)
//   56 {
//   57     SystemCoreClock = __SYSTEM_CLOCK_64M;
SystemCoreClockUpdate:
        LDR.N    R0,??DataTable9_2  ;; 0x3d09000
        LDR.N    R1,??DataTable9_3
        STR      R0,[R1, #+0]
//   58 }
        BX       LR               ;; return
          CFI EndBlock cfiBlock1
//   59 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function SystemInit
        THUMB
//   60 void SystemInit(void)
//   61 {
SystemInit:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//   62     /* Enable SWO trace functionality. If ENABLE_SWO is not defined, SWO pin will be used as GPIO (see Product
//   63        Specification to see which one). */
//   64     #if defined (ENABLE_SWO)
//   65         CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//   66         NRF_CLOCK->TRACECONFIG |= CLOCK_TRACECONFIG_TRACEMUX_Serial << CLOCK_TRACECONFIG_TRACEMUX_Pos;
//   67         NRF_P1->PIN_CNF[0] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//   68     #endif
//   69 
//   70     /* Enable Trace functionality. If ENABLE_TRACE is not defined, TRACE pins will be used as GPIOs (see Product
//   71        Specification to see which ones). */
//   72     #if defined (ENABLE_TRACE)
//   73         CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//   74         NRF_CLOCK->TRACECONFIG |= CLOCK_TRACECONFIG_TRACEMUX_Parallel << CLOCK_TRACECONFIG_TRACEMUX_Pos;
//   75         NRF_P0->PIN_CNF[7]  = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//   76         NRF_P1->PIN_CNF[0]  = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//   77         NRF_P0->PIN_CNF[12] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//   78         NRF_P0->PIN_CNF[11] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//   79         NRF_P1->PIN_CNF[9]  = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//   80     #endif
//   81     
//   82     /* Workaround for Errata 36 "CLOCK: Some registers are not reset when expected" found at the Errata document
//   83        for your device located at https://infocenter.nordicsemi.com/  */
//   84     if (errata_36()){
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_36Ev
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_36Ev
        CMP      R0,#+0
        BEQ.N    ??SystemInit_0
//   85         NRF_CLOCK->EVENTS_DONE = 0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable9_4  ;; 0x4000010c
        STR      R0,[R1, #+0]
//   86         NRF_CLOCK->EVENTS_CTTO = 0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable9_5  ;; 0x40000110
        STR      R0,[R1, #+0]
//   87         NRF_CLOCK->CTIV = 0;
        MOVS     R0,#+0
        LDR.N    R1,??DataTable9_6  ;; 0x40000538
        STR      R0,[R1, #+0]
//   88     }
//   89     
//   90     /* Workaround for Errata 66 "TEMP: Linearity specification not met with default settings" found at the Errata document
//   91        for your device located at https://infocenter.nordicsemi.com/  */
//   92     if (errata_66()){
??SystemInit_0:
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_66Ev
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_66Ev
        CMP      R0,#+0
        BEQ.N    ??SystemInit_1
//   93         NRF_TEMP->A0 = NRF_FICR->TEMP.A0;
        LDR.N    R0,??DataTable9_7  ;; 0x10000404
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_8  ;; 0x4000c520
        STR      R0,[R1, #+0]
//   94         NRF_TEMP->A1 = NRF_FICR->TEMP.A1;
        LDR.N    R0,??DataTable9_9  ;; 0x10000408
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_10  ;; 0x4000c524
        STR      R0,[R1, #+0]
//   95         NRF_TEMP->A2 = NRF_FICR->TEMP.A2;
        LDR.N    R0,??DataTable9_11  ;; 0x1000040c
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_12  ;; 0x4000c528
        STR      R0,[R1, #+0]
//   96         NRF_TEMP->A3 = NRF_FICR->TEMP.A3;
        LDR.N    R0,??DataTable9_13  ;; 0x10000410
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_14  ;; 0x4000c52c
        STR      R0,[R1, #+0]
//   97         NRF_TEMP->A4 = NRF_FICR->TEMP.A4;
        LDR.N    R0,??DataTable9_15  ;; 0x10000414
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_16  ;; 0x4000c530
        STR      R0,[R1, #+0]
//   98         NRF_TEMP->A5 = NRF_FICR->TEMP.A5;
        LDR.N    R0,??DataTable9_17  ;; 0x10000418
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_18  ;; 0x4000c534
        STR      R0,[R1, #+0]
//   99         NRF_TEMP->B0 = NRF_FICR->TEMP.B0;
        LDR.N    R0,??DataTable9_19  ;; 0x1000041c
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_20  ;; 0x4000c540
        STR      R0,[R1, #+0]
//  100         NRF_TEMP->B1 = NRF_FICR->TEMP.B1;
        LDR.N    R0,??DataTable9_21  ;; 0x10000420
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_22  ;; 0x4000c544
        STR      R0,[R1, #+0]
//  101         NRF_TEMP->B2 = NRF_FICR->TEMP.B2;
        LDR.N    R0,??DataTable9_23  ;; 0x10000424
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_24  ;; 0x4000c548
        STR      R0,[R1, #+0]
//  102         NRF_TEMP->B3 = NRF_FICR->TEMP.B3;
        LDR.N    R0,??DataTable9_25  ;; 0x10000428
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_26  ;; 0x4000c54c
        STR      R0,[R1, #+0]
//  103         NRF_TEMP->B4 = NRF_FICR->TEMP.B4;
        LDR.N    R0,??DataTable9_27  ;; 0x1000042c
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_28  ;; 0x4000c550
        STR      R0,[R1, #+0]
//  104         NRF_TEMP->B5 = NRF_FICR->TEMP.B5;
        LDR.N    R0,??DataTable9_29  ;; 0x10000430
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_30  ;; 0x4000c554
        STR      R0,[R1, #+0]
//  105         NRF_TEMP->T0 = NRF_FICR->TEMP.T0;
        LDR.N    R0,??DataTable9_31  ;; 0x10000434
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_32  ;; 0x4000c560
        STR      R0,[R1, #+0]
//  106         NRF_TEMP->T1 = NRF_FICR->TEMP.T1;
        LDR.N    R0,??DataTable9_33  ;; 0x10000438
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_34  ;; 0x4000c564
        STR      R0,[R1, #+0]
//  107         NRF_TEMP->T2 = NRF_FICR->TEMP.T2;
        LDR.N    R0,??DataTable9_35  ;; 0x1000043c
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_36  ;; 0x4000c568
        STR      R0,[R1, #+0]
//  108         NRF_TEMP->T3 = NRF_FICR->TEMP.T3;
        LDR.N    R0,??DataTable9_37  ;; 0x10000440
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_38  ;; 0x4000c56c
        STR      R0,[R1, #+0]
//  109         NRF_TEMP->T4 = NRF_FICR->TEMP.T4;
        LDR.N    R0,??DataTable9_39  ;; 0x10000444
        LDR      R0,[R0, #+0]
        LDR.N    R1,??DataTable9_40  ;; 0x4000c570
        STR      R0,[R1, #+0]
//  110     }
//  111     
//  112     /* Workaround for Errata 98 "NFCT: Not able to communicate with the peer" found at the Errata document
//  113        for your device located at https://infocenter.nordicsemi.com/  */
//  114     if (errata_98()){
??SystemInit_1:
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_98Ev
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_98Ev
        CMP      R0,#+0
        BEQ.N    ??SystemInit_2
//  115         *(volatile uint32_t *)0x4000568Cul = 0x00038148ul;
        LDR.N    R0,??DataTable9_41  ;; 0x38148
        LDR.N    R1,??DataTable9_42  ;; 0x4000568c
        STR      R0,[R1, #+0]
//  116     }
//  117     
//  118     /* Workaround for Errata 103 "CCM: Wrong reset value of CCM MAXPACKETSIZE" found at the Errata document
//  119        for your device located at https://infocenter.nordicsemi.com/  */
//  120     if (errata_103()){
??SystemInit_2:
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_103Ev
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_103Ev
        CMP      R0,#+0
        BEQ.N    ??SystemInit_3
//  121         NRF_CCM->MAXPACKETSIZE = 0xFBul;
        MOVS     R0,#+251
        LDR.N    R1,??DataTable9_43  ;; 0x4000f518
        STR      R0,[R1, #+0]
//  122     }
//  123     
//  124     /* Workaround for Errata 115 "RAM: RAM content cannot be trusted upon waking up from System ON Idle or System OFF mode" found at the Errata document
//  125        for your device located at https://infocenter.nordicsemi.com/  */
//  126     if (errata_115()){
??SystemInit_3:
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_115Ev
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_115Ev
        CMP      R0,#+0
        BEQ.N    ??SystemInit_4
//  127         *(volatile uint32_t *)0x40000EE4 = (*(volatile uint32_t *)0x40000EE4 & 0xFFFFFFF0) | (*(uint32_t *)0x10000258 & 0x0000000F);
        LDR.N    R0,??DataTable9_44  ;; 0x40000ee4
        LDR      R1,[R0, #+0]
        LSRS     R1,R1,#+4
        LSLS     R1,R1,#+4
        LDR.N    R2,??DataTable9_45  ;; 0x10000258
        LDRB     R2,[R2, #+0]
        ANDS     R2,R2,#0xF
        ORRS     R1,R2,R1
        STR      R1,[R0, #+0]
//  128     }
//  129     
//  130     /* Workaround for Errata 120 "QSPI: Data read or written is corrupted" found at the Errata document
//  131        for your device located at https://infocenter.nordicsemi.com/  */
//  132     if (errata_120()){
??SystemInit_4:
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_120Ev
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_120Ev
        CMP      R0,#+0
        BEQ.N    ??SystemInit_5
//  133         *(volatile uint32_t *)0x40029640ul = 0x200ul;
        MOV      R0,#+512
        LDR.N    R1,??DataTable9_46  ;; 0x40029640
        STR      R0,[R1, #+0]
//  134     }
//  135     
//  136     /* Workaround for Errata 136 "System: Bits in RESETREAS are set when they should not be" found at the Errata document
//  137        for your device located at https://infocenter.nordicsemi.com/  */
//  138     if (errata_136()){
??SystemInit_5:
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_136Ev
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_136Ev
        CMP      R0,#+0
        BEQ.N    ??SystemInit_6
//  139         if (NRF_POWER->RESETREAS & POWER_RESETREAS_RESETPIN_Msk){
        LDR.N    R0,??DataTable9_47  ;; 0x40000400
        LDR      R1,[R0, #+0]
        LSLS     R1,R1,#+31
        BPL.N    ??SystemInit_6
//  140             NRF_POWER->RESETREAS =  ~POWER_RESETREAS_RESETPIN_Msk;
        MVNS     R1,#+1
        STR      R1,[R0, #+0]
//  141         }
//  142     }
//  143     
//  144     /* Enable the FPU if the compiler used floating point unit instructions. __FPU_USED is a MACRO defined by the
//  145      * compiler. Since the FPU consumes energy, remember to disable FPU use in the compiler if floating point unit
//  146      * operations are not used in your code. */
//  147     #if (__FPU_USED == 1)
//  148         SCB->CPACR |= (3UL << 20) | (3UL << 22);
//  149         __DSB();
//  150         __ISB();
//  151     #endif
//  152 
//  153     /* Configure NFCT pins as GPIOs if NFCT is not to be used in your code. If CONFIG_NFCT_PINS_AS_GPIOS is not defined,
//  154        two GPIOs (see Product Specification to see which ones) will be reserved for NFC and will not be available as
//  155        normal GPIOs. */
//  156     #if defined (CONFIG_NFCT_PINS_AS_GPIOS)
//  157         if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) == (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)){
??SystemInit_6:
        LDR.N    R1,??DataTable9_48  ;; 0x1000120c
        LDR      R0,[R1, #+0]
        LSLS     R0,R0,#+31
        BPL.N    ??SystemInit_7
//  158             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
        LDR.N    R2,??DataTable9_49  ;; 0x4001e504
        MOVS     R0,#+1
        STR      R0,[R2, #+0]
//  159             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
??SystemInit_8:
        LDR.N    R3,??DataTable9_50  ;; 0x4001e400
        LDR      R0,[R3, #+0]
        CMP      R0,#+0
        BEQ.N    ??SystemInit_8
//  160             NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
        LDR      R0,[R1, #+0]
        LSRS     R0,R0,#+1
        LSLS     R0,R0,#+1
        STR      R0,[R1, #+0]
//  161             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
??SystemInit_9:
        LDR      R0,[R3, #+0]
        CMP      R0,#+0
        BEQ.N    ??SystemInit_9
//  162             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
        MOVS     R0,#+0
        STR      R0,[R2, #+0]
//  163             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
??SystemInit_10:
        LDR      R0,[R3, #+0]
        CMP      R0,#+0
        BEQ.N    ??SystemInit_10
//  164             NVIC_SystemReset();
          CFI FunCall _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6716NVIC_SystemResetEv
        BL       _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6716NVIC_SystemResetEv
//  165         }
//  166     #endif
//  167 
//  168     /* Configure GPIO pads as pPin Reset pin if Pin Reset capabilities desired. If CONFIG_GPIO_AS_PINRESET is not
//  169       defined, pin reset will not be available. One GPIO (see Product Specification to see which one) will then be
//  170       reserved for PinReset and not available as normal GPIO. */
//  171     #if defined (CONFIG_GPIO_AS_PINRESET)
//  172         if (((NRF_UICR->PSELRESET[0] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos)) ||
//  173             ((NRF_UICR->PSELRESET[1] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos))){
//  174             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
//  175             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  176             NRF_UICR->PSELRESET[0] = 18;
//  177             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  178             NRF_UICR->PSELRESET[1] = 18;
//  179             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  180             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
//  181             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  182             NVIC_SystemReset();
//  183         }
//  184     #endif
//  185 
//  186     SystemCoreClockUpdate();
??SystemInit_7:
          CFI FunCall SystemCoreClockUpdate
        BL       SystemCoreClockUpdate
//  187 #ifndef BOOTLOADER
//  188     SCB->VTOR = VECT_TAB_OFFSET;
        MOV      R0,#+8192
        LDR.N    R1,??DataTable9_51  ;; 0xe000ed08
        STR      R0,[R1, #+0]
//  189 #endif
//  190     NRF_POWER->DCDCEN = POWER_DCDCEN_DCDCEN_Enabled << POWER_DCDCEN_DCDCEN_Pos;
        MOVS     R0,#+1
        LDR.N    R1,??DataTable9_52  ;; 0x40000578
        STR      R0,[R1, #+0]
//  191     //NRF_NVMC->CONFIG |= NVMC_ICACHECNF_CACHEEN_Enabled; 
//  192 }
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock2
//  193 
//  194 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_36Ev
          CFI NoCalls
        THUMB
//  195 static bool errata_36(void)
//  196 {
//  197     if (*(uint32_t *)0x10000130ul == 0x8ul){
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_36Ev:
        LDR.N    R0,??DataTable9_53  ;; 0x10000130
        LDR      R0,[R0, #+0]
        CMP      R0,#+8
        BNE.N    ??errata_36_0
//  198         if (*(uint32_t *)0x10000134ul == 0x0ul){
        LDR.N    R1,??DataTable9_54  ;; 0x10000134
        LDR      R0,[R1, #+0]
        CMP      R0,#+0
        BNE.N    ??errata_36_1
//  199             return true;
        MOVS     R0,#+1
        B.N      ??errata_36_2
//  200         }
//  201         if (*(uint32_t *)0x10000134ul == 0x1ul){
??errata_36_1:
        LDR      R0,[R1, #+0]
        CMP      R0,#+1
        BNE.N    ??errata_36_3
//  202             return true;
        MOVS     R0,#+1
        B.N      ??errata_36_2
//  203         }
//  204         if (*(uint32_t *)0x10000134ul == 0x2ul){
??errata_36_3:
        LDR      R0,[R1, #+0]
        CMP      R0,#+2
        BNE.N    ??errata_36_0
//  205             return true;
        MOVS     R0,#+1
        B.N      ??errata_36_2
//  206         }
//  207     }
//  208     
//  209     return true;
??errata_36_0:
        MOVS     R0,#+1
??errata_36_2:
        BX       LR               ;; return
//  210 }
          CFI EndBlock cfiBlock3
//  211 
//  212 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_66Ev
          CFI NoCalls
        THUMB
//  213 static bool errata_66(void)
//  214 {
//  215     if (*(uint32_t *)0x10000130ul == 0x8ul){
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_66Ev:
        LDR.N    R0,??DataTable9_53  ;; 0x10000130
        LDR      R0,[R0, #+0]
        CMP      R0,#+8
        BNE.N    ??errata_66_0
//  216         if (*(uint32_t *)0x10000134ul == 0x0ul){
        LDR.N    R1,??DataTable9_54  ;; 0x10000134
        LDR      R0,[R1, #+0]
        CMP      R0,#+0
        BNE.N    ??errata_66_1
//  217             return true;
        MOVS     R0,#+1
        B.N      ??errata_66_2
//  218         }
//  219         if (*(uint32_t *)0x10000134ul == 0x1ul){
??errata_66_1:
        LDR      R0,[R1, #+0]
        CMP      R0,#+1
        BNE.N    ??errata_66_3
//  220             return true;
        MOVS     R0,#+1
        B.N      ??errata_66_2
//  221         }
//  222         if (*(uint32_t *)0x10000134ul == 0x2ul){
??errata_66_3:
        LDR      R0,[R1, #+0]
        CMP      R0,#+2
        BNE.N    ??errata_66_0
//  223             return true;
        MOVS     R0,#+1
        B.N      ??errata_66_2
//  224         }
//  225     }
//  226     
//  227     return true;
??errata_66_0:
        MOVS     R0,#+1
??errata_66_2:
        BX       LR               ;; return
//  228 }
          CFI EndBlock cfiBlock4
//  229 
//  230 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_98Ev
          CFI NoCalls
        THUMB
//  231 static bool errata_98(void)
//  232 {
//  233     if (*(uint32_t *)0x10000130ul == 0x8ul){
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a679errata_98Ev:
        LDR.N    R0,??DataTable9_53  ;; 0x10000130
        LDR      R0,[R0, #+0]
        CMP      R0,#+8
        BNE.N    ??errata_98_0
//  234         if (*(uint32_t *)0x10000134ul == 0x0ul){
        LDR.N    R0,??DataTable9_54  ;; 0x10000134
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??errata_98_0
//  235             return true;
        MOVS     R0,#+1
        B.N      ??errata_98_1
//  236         }
//  237     }
//  238     
//  239     return false;
??errata_98_0:
        MOVS     R0,#+0
??errata_98_1:
        BX       LR               ;; return
//  240 }
          CFI EndBlock cfiBlock5
//  241 
//  242 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_103Ev
          CFI NoCalls
        THUMB
//  243 static bool errata_103(void)
//  244 {
//  245     if (*(uint32_t *)0x10000130ul == 0x8ul){
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_103Ev:
        LDR.N    R0,??DataTable9_53  ;; 0x10000130
        LDR      R0,[R0, #+0]
        CMP      R0,#+8
        BNE.N    ??errata_103_0
//  246         if (*(uint32_t *)0x10000134ul == 0x0ul){
        LDR.N    R0,??DataTable9_54  ;; 0x10000134
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??errata_103_0
//  247             return true;
        MOVS     R0,#+1
        B.N      ??errata_103_1
//  248         }
//  249     }
//  250     
//  251     return false;
??errata_103_0:
        MOVS     R0,#+0
??errata_103_1:
        BX       LR               ;; return
//  252 }
          CFI EndBlock cfiBlock6
//  253 
//  254 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_115Ev
          CFI NoCalls
        THUMB
//  255 static bool errata_115(void)
//  256 {
//  257     if (*(uint32_t *)0x10000130ul == 0x8ul){
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_115Ev:
        LDR.N    R0,??DataTable9_53  ;; 0x10000130
        LDR      R0,[R0, #+0]
        CMP      R0,#+8
        BNE.N    ??errata_115_0
//  258         if (*(uint32_t *)0x10000134ul == 0x0ul){
        LDR.N    R0,??DataTable9_54  ;; 0x10000134
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??errata_115_0
//  259             return true;
        MOVS     R0,#+1
        B.N      ??errata_115_1
//  260         }
//  261     }
//  262     
//  263     return false;
??errata_115_0:
        MOVS     R0,#+0
??errata_115_1:
        BX       LR               ;; return
//  264 }
          CFI EndBlock cfiBlock7
//  265 
//  266 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_120Ev
          CFI NoCalls
        THUMB
//  267 static bool errata_120(void)
//  268 {
//  269     if (*(uint32_t *)0x10000130ul == 0x8ul){
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_120Ev:
        LDR.N    R0,??DataTable9_53  ;; 0x10000130
        LDR      R0,[R0, #+0]
        CMP      R0,#+8
        BNE.N    ??errata_120_0
//  270         if (*(uint32_t *)0x10000134ul == 0x0ul){
        LDR.N    R0,??DataTable9_54  ;; 0x10000134
        LDR      R0,[R0, #+0]
        CMP      R0,#+0
        BNE.N    ??errata_120_0
//  271             return true;
        MOVS     R0,#+1
        B.N      ??errata_120_1
//  272         }
//  273     }
//  274     
//  275     return false;
??errata_120_0:
        MOVS     R0,#+0
??errata_120_1:
        BX       LR               ;; return
//  276 }
          CFI EndBlock cfiBlock8
//  277 
//  278 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function _ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_136Ev
          CFI NoCalls
        THUMB
//  279 static bool errata_136(void)
//  280 {
//  281     if (*(uint32_t *)0x10000130ul == 0x8ul){
_ZN39_INTERNAL_17_system_nrf52840_c_5d646a6710errata_136Ev:
        LDR.N    R0,??DataTable9_53  ;; 0x10000130
        LDR      R0,[R0, #+0]
        CMP      R0,#+8
        BNE.N    ??errata_136_0
//  282         if (*(uint32_t *)0x10000134ul == 0x0ul){
        LDR.N    R1,??DataTable9_54  ;; 0x10000134
        LDR      R0,[R1, #+0]
        CMP      R0,#+0
        BNE.N    ??errata_136_1
//  283             return true;
        MOVS     R0,#+1
        B.N      ??errata_136_2
//  284         }
//  285         if (*(uint32_t *)0x10000134ul == 0x1ul){
??errata_136_1:
        LDR      R0,[R1, #+0]
        CMP      R0,#+1
        BNE.N    ??errata_136_3
//  286             return true;
        MOVS     R0,#+1
        B.N      ??errata_136_2
//  287         }
//  288         if (*(uint32_t *)0x10000134ul == 0x2ul){
??errata_136_3:
        LDR      R0,[R1, #+0]
        CMP      R0,#+2
        BNE.N    ??errata_136_0
//  289             return true;
        MOVS     R0,#+1
        B.N      ??errata_136_2
//  290         }
//  291     }
//  292     
//  293     return true;
??errata_136_0:
        MOVS     R0,#+1
??errata_136_2:
        BX       LR               ;; return
//  294 }
          CFI EndBlock cfiBlock9

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9:
        DATA32
        DC32     0xe000ed0c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_1:
        DATA32
        DC32     0x5fa0004

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_2:
        DATA32
        DC32     0x3d09000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_3:
        DATA32
        DC32     SystemCoreClock

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_4:
        DATA32
        DC32     0x4000010c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_5:
        DATA32
        DC32     0x40000110

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_6:
        DATA32
        DC32     0x40000538

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_7:
        DATA32
        DC32     0x10000404

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_8:
        DATA32
        DC32     0x4000c520

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_9:
        DATA32
        DC32     0x10000408

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_10:
        DATA32
        DC32     0x4000c524

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_11:
        DATA32
        DC32     0x1000040c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_12:
        DATA32
        DC32     0x4000c528

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_13:
        DATA32
        DC32     0x10000410

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_14:
        DATA32
        DC32     0x4000c52c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_15:
        DATA32
        DC32     0x10000414

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_16:
        DATA32
        DC32     0x4000c530

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_17:
        DATA32
        DC32     0x10000418

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_18:
        DATA32
        DC32     0x4000c534

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_19:
        DATA32
        DC32     0x1000041c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_20:
        DATA32
        DC32     0x4000c540

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_21:
        DATA32
        DC32     0x10000420

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_22:
        DATA32
        DC32     0x4000c544

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_23:
        DATA32
        DC32     0x10000424

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_24:
        DATA32
        DC32     0x4000c548

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_25:
        DATA32
        DC32     0x10000428

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_26:
        DATA32
        DC32     0x4000c54c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_27:
        DATA32
        DC32     0x1000042c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_28:
        DATA32
        DC32     0x4000c550

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_29:
        DATA32
        DC32     0x10000430

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_30:
        DATA32
        DC32     0x4000c554

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_31:
        DATA32
        DC32     0x10000434

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_32:
        DATA32
        DC32     0x4000c560

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_33:
        DATA32
        DC32     0x10000438

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_34:
        DATA32
        DC32     0x4000c564

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_35:
        DATA32
        DC32     0x1000043c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_36:
        DATA32
        DC32     0x4000c568

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_37:
        DATA32
        DC32     0x10000440

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_38:
        DATA32
        DC32     0x4000c56c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_39:
        DATA32
        DC32     0x10000444

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_40:
        DATA32
        DC32     0x4000c570

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_41:
        DATA32
        DC32     0x38148

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_42:
        DATA32
        DC32     0x4000568c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_43:
        DATA32
        DC32     0x4000f518

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_44:
        DATA32
        DC32     0x40000ee4

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_45:
        DATA32
        DC32     0x10000258

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_46:
        DATA32
        DC32     0x40029640

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_47:
        DATA32
        DC32     0x40000400

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_48:
        DATA32
        DC32     0x1000120c

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_49:
        DATA32
        DC32     0x4001e504

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_50:
        DATA32
        DC32     0x4001e400

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_51:
        DATA32
        DC32     0xe000ed08

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_52:
        DATA32
        DC32     0x40000578

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_53:
        DATA32
        DC32     0x10000130

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable9_54:
        DATA32
        DC32     0x10000134

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//  295 
//  296 /*lint --flb "Leave library region" */
//  297 #endif
// 
//   4 bytes in section .data
// 818 bytes in section .text
// 
// 818 bytes of CODE memory
//   4 bytes of DATA memory
//
//Errors: none
//Warnings: none
