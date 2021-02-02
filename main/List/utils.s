///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        02/Feb/2021  18:19:54
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\utils\utils.c
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EW3B95.tmp
//        (E:\cpp\nrf52_libraries\utils\utils.c -D NRF52840_XXAA -D
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
//    List file    =  E:\cpp\nrf52_libraries\main\List\utils.s
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

        PUBLIC _Z10crc16_fillPKhjt
        PUBLIC _Z10pincfg_regj
        PUBLIC _Z11seed_randomj
        PUBLIC _Z5crc16PKhj
        PUBLIC _Z6randomv
        PUBLIC _Z7rnd_maxi
        
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
        
// E:\cpp\nrf52_libraries\utils\utils.c
//    1 #include "utils.h"

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function _ZN28_INTERNAL_7_utils_c_731edefb24nrf_gpio_pin_port_decodeEPj
          CFI NoCalls
        THUMB
// static __interwork __softfp NRF_GPIO_Type *nrf_gpio_pin_port_decode(uint32_t *)
_ZN28_INTERNAL_7_utils_c_731edefb24nrf_gpio_pin_port_decodeEPj:
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
        LDR.N    R0,??DataTable2  ;; 0x50000300
??nrf_gpio_pin_port_decode_1:
        BX       LR               ;; return
          CFI EndBlock cfiBlock0
//    2 

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//    3 static unsigned long int _next = 1;
_next:
        DATA32
        DC32 1
//    4 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function _Z11seed_randomj
          CFI NoCalls
        THUMB
//    5 void seed_random(unsigned int seed)
//    6 {
_Z11seed_randomj:
        PUSH     {R0-R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+20
//    7   if (seed == 0)
        CMP      R0,#+0
        BNE.N    ??seed_random_0
//    8   {
//    9     uint32_t v[4];
//   10     
//   11     for (uint8_t i = 0; i < 4; i++)
        MOVS     R2,#+0
??seed_random_1:
        MOVS     R1,R2
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+4
        BGE.N    ??seed_random_2
//   12     {
//   13       NRF_RNG->EVENTS_VALRDY = 0;
        LDR.N    R3,??DataTable2_1  ;; 0x4000d100
        MOVS     R1,#+0
        STR      R1,[R3, #+0]
//   14       NRF_RNG->TASKS_START = 1;
        MOVS     R1,#+1
        LDR.N    R4,??DataTable2_2  ;; 0x4000d000
        STR      R1,[R4, #+0]
//   15       while (NRF_RNG->EVENTS_VALRDY == 0);
??seed_random_3:
        LDR      R1,[R3, #+0]
        CMP      R1,#+0
        BEQ.N    ??seed_random_3
//   16       v[i] = NRF_RNG->VALUE;
        LDR.N    R1,??DataTable2_3  ;; 0x4000d508
        LDR      R1,[R1, #+0]
        MOV      R3,SP
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        STR      R1,[R3, R4, LSL #+2]
//   17     }
        ADDS     R2,R2,#+1
        B.N      ??seed_random_1
//   18     
//   19     NRF_RNG->TASKS_STOP = 1;
??seed_random_2:
        MOVS     R1,#+1
        LDR.N    R2,??DataTable2_4  ;; 0x4000d004
        STR      R1,[R2, #+0]
//   20     
//   21     _next = (v[0] << 24) | (v[1] << 16) | (v[2] << 8) | v[3];
        MOV      R1,SP
        LDR      R2,[SP, #+0]
        LDR      R3,[R1, #+4]
        LSLS     R3,R3,#+16
        ORRS     R3,R3,R2, LSL #+24
        LDR      R1,[R1, #+8]
        ORRS     R3,R3,R1, LSL #+8
        LDR      R1,[SP, #+12]
        ORRS     R3,R1,R3
        LDR.N    R1,??DataTable2_5
        STR      R3,[R1, #+0]
        B.N      ??seed_random_4
//   22   }
//   23   else
//   24     _next = seed;
??seed_random_0:
        LDR.N    R1,??DataTable2_5
        STR      R0,[R1, #+0]
//   25 }
??seed_random_4:
        POP      {R0-R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock1
//   26 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function _Z6randomv
          CFI NoCalls
        THUMB
//   27 int random(void) // RAND_MAX assumed to be 32767
//   28 {
//   29   _next = _next * 1103515245 + 12345;
_Z6randomv:
        LDR.N    R1,??DataTable2_5
        LDR      R2,[R1, #+0]
        LDR.N    R3,??DataTable2_6  ;; 0x41c64e6d
        MOVW     R0,#+12345
        MLA      R2,R3,R2,R0
        STR      R2,[R1, #+0]
//   30   return (unsigned int)(_next/65536) % 32768;
        LDR      R0,[R1, #+0]
        UBFX     R0,R0,#+16,#+15
        BX       LR               ;; return
//   31 }
          CFI EndBlock cfiBlock2

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DATA32
        DC32     0x50000300

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DATA32
        DC32     0x4000d100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_2:
        DATA32
        DC32     0x4000d000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_3:
        DATA32
        DC32     0x4000d508

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_4:
        DATA32
        DC32     0x4000d004

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_5:
        DATA32
        DC32     _next

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_6:
        DATA32
        DC32     0x41c64e6d
//   32 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function _Z7rnd_maxi
        THUMB
//   33 int rnd_max(int max)
//   34 {
_Z7rnd_maxi:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//   35   return (max*random()) / 32767;
          CFI FunCall _Z6randomv
        BL       _Z6randomv
        MUL      R0,R0,R4
        MOVW     R1,#+32767
        SDIV     R0,R0,R1
        POP      {R4,PC}          ;; return
//   36 }
          CFI EndBlock cfiBlock3
//   37 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _Z10crc16_fillPKhjt
          CFI NoCalls
        THUMB
//   38 uint16_t crc16_fill( const uint8_t *pBuf, uint32_t uiLength, uint16_t fill )
//   39 {
_Z10crc16_fillPKhjt:
        PUSH     {R4-R7}
          CFI R7 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R4,R0
//   40     register uint8_t Lo, Hi, ucSym;
//   41  
//   42     if (!uiLength){
        CMP      R1,#+0
        BNE.N    ??crc16_fill_0
//   43         return 1;
        MOVS     R0,#+1
        B.N      ??crc16_fill_1
//   44     }
//   45    
//   46     Lo = fill & 0xFF;
??crc16_fill_0:
        MOVS     R3,R2
//   47     Hi = (fill & 0xFF00) >> 8;
        MOVS     R5,R2
        UXTH     R5,R5            ;; ZeroExt  R5,R5,#+16,#+16
        LSRS     R5,R5,#+8
//   48  
//   49     do {
//   50         ucSym = *(pBuf++);
??crc16_fill_2:
        LDRB     R7,[R4, #+0]
        ADDS     R4,R4,#+1
//   51         ucSym ^= Hi;
        EORS     R7,R5,R7
//   52           
//   53         Hi = ( ucSym & 0x02 ) ? (Lo - 0x80) : Lo;
        LSLS     R0,R7,#+30
        BPL.N    ??crc16_fill_3
        SUBS     R5,R3,#+128
        B.N      ??crc16_fill_4
??crc16_fill_3:
        MOVS     R5,R3
//   54           
//   55         if ( ucSym & 0x01 )
??crc16_fill_4:
        LSLS     R0,R7,#+31
        BPL.N    ??crc16_fill_5
//   56             Hi ^= 0xC0;
        EORS     R5,R5,#0xC0
//   57           
//   58         Lo = ucSym;
??crc16_fill_5:
        MOVS     R0,R7
//   59         Lo >>= 1;
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        LSRS     R0,R0,#+1
//   60         Lo ^= ucSym;
        EORS     R0,R7,R0
//   61         Lo >>= 1;
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        LSRS     R0,R0,#+1
        MOVS     R3,R0
//   62         ucSym ^= Lo;
        MOVS     R6,R7
        EORS     R6,R3,R6
//   63           
//   64         if ( ucSym & 0x08 )
        LSLS     R0,R6,#+28
        BPL.N    ??crc16_fill_6
//   65             --ucSym;
        SUBS     R6,R6,#+1
//   66           
//   67         if ( ucSym & 0x40 )
??crc16_fill_6:
        LSLS     R0,R6,#+25
        BPL.N    ??crc16_fill_7
//   68             --ucSym;
        SUBS     R6,R6,#+1
//   69           
//   70         ucSym &= 0x01;
??crc16_fill_7:
        ANDS     R6,R6,#0x1
//   71   
//   72         if ( ucSym )
        MOVS     R0,R6
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??crc16_fill_8
//   73             Lo ^= 0xC0;
        EORS     R3,R3,#0xC0
//   74   
//   75         Hi ^= ucSym;
??crc16_fill_8:
        EORS     R5,R6,R5
//   76     } while ( --uiLength );
        SUBS     R1,R1,#+1
        CMP      R1,#+0
        BNE.N    ??crc16_fill_2
//   77   
//   78     return (uint16_t)((((uint16_t)Hi)<<8) | Lo);
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ORRS     R3,R3,R5, LSL #+8
        MOVS     R0,R3
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
??crc16_fill_1:
        POP      {R4-R7}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
//   79 }
          CFI EndBlock cfiBlock4
//   80 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _Z5crc16PKhj
        THUMB
//   81 uint16_t crc16( const uint8_t *pBuf, uint32_t uiLength )
//   82 {
_Z5crc16PKhj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
//   83     return crc16_fill(pBuf, uiLength, 0xFFFF);
        MOVW     R2,#+65535
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _Z10crc16_fillPKhjt
        BL       _Z10crc16_fillPKhjt
        POP      {R1,R4,R5,PC}    ;; return
//   84 }
          CFI EndBlock cfiBlock5
//   85 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _Z10pincfg_regj
        THUMB
//   86 volatile uint32_t* pincfg_reg(uint32_t pin)
//   87 {
_Z10pincfg_regj:
        PUSH     {R0,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
//   88   	NRF_GPIO_Type * port = nrf_gpio_pin_port_decode(&pin);
        MOV      R0,SP
          CFI FunCall _ZN28_INTERNAL_7_utils_c_731edefb24nrf_gpio_pin_port_decodeEPj
        BL       _ZN28_INTERNAL_7_utils_c_731edefb24nrf_gpio_pin_port_decodeEPj
//   89 
//   90   	return &port->PIN_CNF[pin];
        LDR      R1,[SP, #+0]
        ADD      R0,R0,R1, LSL #+2
        ADDS     R0,R0,#+1792
        POP      {R1,PC}          ;; return
//   91 }
          CFI EndBlock cfiBlock6

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
// 
//   4 bytes in section .data
// 350 bytes in section .text
// 
// 350 bytes of CODE memory
//   4 bytes of DATA memory
//
//Errors: none
//Warnings: none
