///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        02/Feb/2021  11:39:10
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\cmsis\system_nrf52.c
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EW5112.tmp
//        (E:\cpp\nrf52_libraries\cmsis\system_nrf52.c -D NRF52840_XXAA -D
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
//    List file    =  E:\cpp\nrf52_libraries\main\List\system_nrf52.s
//
///////////////////////////////////////////////////////////////////////////////

        RTMODEL "__CPP_Exceptions", "Disabled"
        RTMODEL "__CPP_Language", "C++14"
        RTMODEL "__SystemLibrary", "DLib"
        AAPCS BASE,INTERWORK
        PRESERVE8
        REQUIRE8

        #define SHT_PROGBITS 0x1


        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// E:\cpp\nrf52_libraries\cmsis\system_nrf52.c
//    1 /* Copyright (c) 2012 ARM LIMITED
//    2  * All rights reserved.
//    3  *
//    4  * Redistribution and use in source and binary forms, with or without
//    5  * modification, are permitted provided that the following conditions are met:
//    6  *
//    7  *   * Redistributions of source code must retain the above copyright notice, this
//    8  *     list of conditions and the following disclaimer.
//    9  *
//   10  *   * Redistributions in binary form must reproduce the above copyright notice,
//   11  *     this list of conditions and the following disclaimer in the documentation
//   12  *     and/or other materials provided with the distribution.
//   13  *
//   14  *   * Neither the name of ARM nor the names of its contributors may be used to
//   15  *     endorse or promote products derived from this software without specific
//   16  *     prior written permission.
//   17  *
//   18  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//   19  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//   20  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   21  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//   22  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//   23  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//   24  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//   25  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//   26  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//   27  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//   28  *
//   29  */
//   30 #ifdef NRF52832_XXAA
//   31    
//   32 #include <stdint.h>
//   33 #include <stdbool.h>
//   34 #include "nrf.h"
//   35 #include "system_nrf52.h"
//   36 
//   37 /*lint ++flb "Enter library region" */
//   38 
//   39 #define __SYSTEM_CLOCK_64M      (64000000UL)
//   40 #define VECT_TAB_OFFSET         0x2000
//   41 
//   42 static bool errata_16(void);
//   43 static bool errata_31(void);
//   44 static bool errata_32(void);
//   45 static bool errata_36(void);
//   46 static bool errata_37(void);
//   47 static bool errata_57(void);
//   48 static bool errata_66(void);
//   49 static bool errata_108(void);
//   50 
//   51 
//   52 #if defined ( __CC_ARM )
//   53     uint32_t SystemCoreClock __attribute__((used)) = __SYSTEM_CLOCK_64M;
//   54 #elif defined ( __ICCARM__ )
//   55     __root uint32_t SystemCoreClock = __SYSTEM_CLOCK_64M;
//   56 #elif defined ( __GNUC__ )
//   57     uint32_t SystemCoreClock __attribute__((used)) = __SYSTEM_CLOCK_64M;
//   58 #endif
//   59 
//   60 void SystemCoreClockUpdate(void)
//   61 {
//   62     SystemCoreClock = __SYSTEM_CLOCK_64M;
//   63 }
//   64 
//   65 void SystemInit(void)
//   66 {
//   67     /* Workaround for Errata 16 "System: RAM may be corrupt on wakeup from CPU IDLE" found at the Errata document
//   68        for your device located at https://infocenter.nordicsemi.com/ */
//   69     if (errata_16()){
//   70         *(volatile uint32_t *)0x4007C074 = 3131961357ul;
//   71     }
//   72 
//   73     /* Workaround for Errata 31 "CLOCK: Calibration values are not correctly loaded from FICR at reset" found at the Errata document
//   74        for your device located at https://infocenter.nordicsemi.com/ */
//   75     if (errata_31()){
//   76         *(volatile uint32_t *)0x4000053C = ((*(volatile uint32_t *)0x10000244) & 0x0000E000) >> 13;
//   77     }
//   78 
//   79     /* Workaround for Errata 32 "DIF: Debug session automatically enables TracePort pins" found at the Errata document
//   80        for your device located at https://infocenter.nordicsemi.com/ */
//   81     if (errata_32()){
//   82         CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;
//   83     }
//   84 
//   85     /* Workaround for Errata 36 "CLOCK: Some registers are not reset when expected" found at the Errata document
//   86        for your device located at https://infocenter.nordicsemi.com/  */
//   87     if (errata_36()){
//   88         NRF_CLOCK->EVENTS_DONE = 0;
//   89         NRF_CLOCK->EVENTS_CTTO = 0;
//   90         NRF_CLOCK->CTIV = 0;
//   91     }
//   92 
//   93     /* Workaround for Errata 37 "RADIO: Encryption engine is slow by default" found at the Errata document
//   94        for your device located at https://infocenter.nordicsemi.com/  */
//   95     if (errata_37()){
//   96         *(volatile uint32_t *)0x400005A0 = 0x3;
//   97     }
//   98 
//   99     /* Workaround for Errata 57 "NFCT: NFC Modulation amplitude" found at the Errata document
//  100        for your device located at https://infocenter.nordicsemi.com/  */
//  101     if (errata_57()){
//  102         *(volatile uint32_t *)0x40005610 = 0x00000005;
//  103         *(volatile uint32_t *)0x40005688 = 0x00000001;
//  104         *(volatile uint32_t *)0x40005618 = 0x00000000;
//  105         *(volatile uint32_t *)0x40005614 = 0x0000003F;
//  106     }
//  107 
//  108     /* Workaround for Errata 66 "TEMP: Linearity specification not met with default settings" found at the Errata document
//  109        for your device located at https://infocenter.nordicsemi.com/  */
//  110     if (errata_66()){
//  111         NRF_TEMP->A0 = NRF_FICR->TEMP.A0;
//  112         NRF_TEMP->A1 = NRF_FICR->TEMP.A1;
//  113         NRF_TEMP->A2 = NRF_FICR->TEMP.A2;
//  114         NRF_TEMP->A3 = NRF_FICR->TEMP.A3;
//  115         NRF_TEMP->A4 = NRF_FICR->TEMP.A4;
//  116         NRF_TEMP->A5 = NRF_FICR->TEMP.A5;
//  117         NRF_TEMP->B0 = NRF_FICR->TEMP.B0;
//  118         NRF_TEMP->B1 = NRF_FICR->TEMP.B1;
//  119         NRF_TEMP->B2 = NRF_FICR->TEMP.B2;
//  120         NRF_TEMP->B3 = NRF_FICR->TEMP.B3;
//  121         NRF_TEMP->B4 = NRF_FICR->TEMP.B4;
//  122         NRF_TEMP->B5 = NRF_FICR->TEMP.B5;
//  123         NRF_TEMP->T0 = NRF_FICR->TEMP.T0;
//  124         NRF_TEMP->T1 = NRF_FICR->TEMP.T1;
//  125         NRF_TEMP->T2 = NRF_FICR->TEMP.T2;
//  126         NRF_TEMP->T3 = NRF_FICR->TEMP.T3;
//  127         NRF_TEMP->T4 = NRF_FICR->TEMP.T4;
//  128     }
//  129 
//  130     /* Workaround for Errata 108 "RAM: RAM content cannot be trusted upon waking up from System ON Idle or System OFF mode" found at the Errata document
//  131        for your device located at https://infocenter.nordicsemi.com/  */
//  132     if (errata_108()){
//  133         *(volatile uint32_t *)0x40000EE4 = *(volatile uint32_t *)0x10000258 & 0x0000004F;
//  134     }
//  135     
//  136     /* Enable the FPU if the compiler used floating point unit instructions. __FPU_USED is a MACRO defined by the
//  137      * compiler. Since the FPU consumes energy, remember to disable FPU use in the compiler if floating point unit
//  138      * operations are not used in your code. */
//  139     #if (__FPU_USED == 1)
//  140         SCB->CPACR |= (3UL << 20) | (3UL << 22);
//  141         __DSB();
//  142         __ISB();
//  143     #endif
//  144 
//  145     /* Configure NFCT pins as GPIOs if NFCT is not to be used in your code. If CONFIG_NFCT_PINS_AS_GPIOS is not defined,
//  146        two GPIOs (see Product Specification to see which ones) will be reserved for NFC and will not be available as
//  147        normal GPIOs. */
//  148     #if defined (CONFIG_NFCT_PINS_AS_GPIOS)
//  149         if ((NRF_UICR->NFCPINS & UICR_NFCPINS_PROTECT_Msk) == (UICR_NFCPINS_PROTECT_NFC << UICR_NFCPINS_PROTECT_Pos)){
//  150             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
//  151             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  152             NRF_UICR->NFCPINS &= ~UICR_NFCPINS_PROTECT_Msk;
//  153             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  154             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
//  155             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  156             NVIC_SystemReset();
//  157         }
//  158     #endif
//  159 
//  160     /* Configure GPIO pads as pPin Reset pin if Pin Reset capabilities desired. If CONFIG_GPIO_AS_PINRESET is not
//  161       defined, pin reset will not be available. One GPIO (see Product Specification to see which one) will then be
//  162       reserved for PinReset and not available as normal GPIO. */
//  163     #if defined (CONFIG_GPIO_AS_PINRESET)
//  164         if (((NRF_UICR->PSELRESET[0] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos)) ||
//  165             ((NRF_UICR->PSELRESET[1] & UICR_PSELRESET_CONNECT_Msk) != (UICR_PSELRESET_CONNECT_Connected << UICR_PSELRESET_CONNECT_Pos))){
//  166             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
//  167             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  168             NRF_UICR->PSELRESET[0] = 21;
//  169             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  170             NRF_UICR->PSELRESET[1] = 21;
//  171             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  172             NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
//  173             while (NRF_NVMC->READY == NVMC_READY_READY_Busy){}
//  174             NVIC_SystemReset();
//  175         }
//  176     #endif
//  177 
//  178     /* Enable SWO trace functionality. If ENABLE_SWO is not defined, SWO pin will be used as GPIO (see Product
//  179        Specification to see which one). */
//  180     #if defined (ENABLE_SWO)
//  181         CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//  182         NRF_CLOCK->TRACECONFIG |= CLOCK_TRACECONFIG_TRACEMUX_Serial << CLOCK_TRACECONFIG_TRACEMUX_Pos;
//  183         NRF_P0->PIN_CNF[18] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//  184     #endif
//  185 
//  186     /* Enable Trace functionality. If ENABLE_TRACE is not defined, TRACE pins will be used as GPIOs (see Product
//  187        Specification to see which ones). */
//  188     #if defined (ENABLE_TRACE)
//  189         CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
//  190         NRF_CLOCK->TRACECONFIG |= CLOCK_TRACECONFIG_TRACEMUX_Parallel << CLOCK_TRACECONFIG_TRACEMUX_Pos;
//  191         NRF_P0->PIN_CNF[14] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//  192         NRF_P0->PIN_CNF[15] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//  193         NRF_P0->PIN_CNF[16] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//  194         NRF_P0->PIN_CNF[18] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//  195         NRF_P0->PIN_CNF[20] = (GPIO_PIN_CNF_DRIVE_H0H1 << GPIO_PIN_CNF_DRIVE_Pos) | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
//  196     #endif
//  197 
//  198     SystemCoreClockUpdate();
//  199 #ifndef BOOTLOADER
//  200     SCB->VTOR = VECT_TAB_OFFSET;
//  201 #endif
//  202     NRF_POWER->DCDCEN = POWER_DCDCEN_DCDCEN_Enabled << POWER_DCDCEN_DCDCEN_Pos;
//  203     //NRF_NVMC->CONFIG |= NVMC_ICACHECNF_CACHEEN_Enabled; 
//  204 }
//  205 
//  206 
//  207 static bool errata_16(void)
//  208 {
//  209     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  210         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30){
//  211             return true;
//  212         }
//  213     }
//  214 
//  215     return false;
//  216 }
//  217 
//  218 static bool errata_31(void)
//  219 {
//  220     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  221         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30){
//  222             return true;
//  223         }
//  224         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x40){
//  225             return true;
//  226         }
//  227         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x50){
//  228             return true;
//  229         }
//  230     }
//  231 
//  232     return false;
//  233 }
//  234 
//  235 static bool errata_32(void)
//  236 {
//  237     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  238         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30){
//  239             return true;
//  240         }
//  241     }
//  242 
//  243     return false;
//  244 }
//  245 
//  246 static bool errata_36(void)
//  247 {
//  248     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  249         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30){
//  250             return true;
//  251         }
//  252         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x40){
//  253             return true;
//  254         }
//  255         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x50){
//  256             return true;
//  257         }
//  258     }
//  259 
//  260     return false;
//  261 }
//  262 
//  263 static bool errata_37(void)
//  264 {
//  265     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  266         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30){
//  267             return true;
//  268         }
//  269     }
//  270 
//  271     return false;
//  272 }
//  273 
//  274 static bool errata_57(void)
//  275 {
//  276     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  277         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30){
//  278             return true;
//  279         }
//  280     }
//  281 
//  282     return false;
//  283 }
//  284 
//  285 static bool errata_66(void)
//  286 {
//  287     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  288         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x50){
//  289             return true;
//  290         }
//  291     }
//  292 
//  293     return false;
//  294 }
//  295 
//  296 
//  297 static bool errata_108(void)
//  298 {
//  299     if ((((*(uint32_t *)0xF0000FE0) & 0x000000FF) == 0x6) && (((*(uint32_t *)0xF0000FE4) & 0x0000000F) == 0x0)){
//  300         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x30){
//  301             return true;
//  302         }
//  303         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x40){
//  304             return true;
//  305         }
//  306         if (((*(uint32_t *)0xF0000FE8) & 0x000000F0) == 0x50){
//  307             return true;
//  308         }
//  309     }
//  310 
//  311     return false;
//  312 }
//  313 
//  314 #endif
//  315 /*lint --flb "Leave library region" */
// 
// 
// 0 bytes of memory
//
//Errors: none
//Warnings: none