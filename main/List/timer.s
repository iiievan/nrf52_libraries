///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        03/Feb/2021  19:58:18
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\timer\timer.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EW7156.tmp
//        (E:\cpp\nrf52_libraries\timer\timer.cpp -D NRF52840_XXAA -D
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
//    List file    =  E:\cpp\nrf52_libraries\main\List\timer.s
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

        EXTERN _Z18led_drivers_handlev
        EXTERN adc_unite

        PUBLIC TIMER0_IRQHandler
        PUBLIC TIMER1_IRQHandler
        PUBLIC TIMER2_IRQHandler
        PUBLIC TIMER3_IRQHandler
        PUBLIC TIMER4_IRQHandler
        PUBLIC _Z18sys_timer_callbackj
        PUBLIC _ZN3ADCILi6EE20setConvertionEND_IRQEh
        PUBLIC _ZN3ADCILi6EE4initEv
        PUBLIC _ZN3ADCILi6EE6deinitEv
        PUBLIC _ZN3ADCILi6EE6enableEv
        PUBLIC _ZN3ADCILi6EE7disableEv
        PUBLIC _ZN3ADCILi6EE7measureEv
        PUBLIC _ZN5Timer17setCaptureCompareEhhb
        PUBLIC _ZN5Timer4initEjjb
        PUBLIC _ZN5Timer5onIRQEv
        PUBLIC _ZN5Timer5pauseEv
        PUBLIC _ZN5Timer6get_usEv
        PUBLIC _ZN5Timer6resumeEv
        PUBLIC _ZN5Timer6setIRQEhh
        PUBLIC _ZN5Timer8delay_msEj
        PUBLIC _ZN5Timer8delay_usEj
        PUBLIC _ZN5Timer9incrementEj
        PUBLIC _ZN5TimerC1Eh
        PUBLIC _ZN5TimerC2Eh
        PUBLIC _ZNK5Timer6get_msEv
        PUBLIC sys_timer
        
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
        
// E:\cpp\nrf52_libraries\timer\timer.cpp
//    1 #include "Timer.h"
//    2 #include "led_driver.h"
//    3 
//    4 #include "ADC.h"
//    5 #include "ADC.cpp" // because this is template of class
//    6 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function _ZN5TimerC2Eh
        THUMB
// __code __interwork __softfp Timer::subobject Timer(uint8_t)
_ZN5TimerC2Eh:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN5TimerC1Eh
        BL       _ZN5TimerC1Eh
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock0

        SECTION `.bss`:DATA:REORDER:NOROOT(0)
        DATA
`sys_timer_callback(uint32_t)::activeLeds`:
        DS8 1

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
`sys_timer_callback(uint32_t)::adcTmr`:
        DS8 8

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function __sti__routine
        THUMB
// static __intrinsic __interwork __softfp void __sti__routine()
__sti__routine:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
        MOVS     R1,#+0
        LDR.W    R0,??DataTable8
          CFI FunCall _ZN5TimerC1Eh
        BL       _ZN5TimerC1Eh
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock1

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function _ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type
          CFI NoCalls
        THUMB
// static __interwork __softfp void NVIC_EnableIRQ(IRQn_Type)
_ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type:
        MOVS     R2,#+1
        ANDS     R1,R0,#0x1F
        LSLS     R2,R2,R1
        LDR.W    R1,??DataTable8_1  ;; 0xe000e100
        MOVS     R3,R0
        SXTB     R3,R3            ;; SignExt  R3,R3,#+24,#+24
        LSRS     R3,R3,#+5
        STR      R2,[R1, R3, LSL #+2]
        BX       LR               ;; return
          CFI EndBlock cfiBlock2

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function _ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type
          CFI NoCalls
        THUMB
// static __interwork __softfp void NVIC_ClearPendingIRQ(IRQn_Type)
_ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type:
        MOVS     R2,#+1
        ANDS     R1,R0,#0x1F
        LSLS     R2,R2,R1
        LDR.W    R1,??DataTable8_2  ;; 0xe000e280
        MOVS     R3,R0
        SXTB     R3,R3            ;; SignExt  R3,R3,#+24,#+24
        LSRS     R3,R3,#+5
        STR      R2,[R1, R3, LSL #+2]
        BX       LR               ;; return
          CFI EndBlock cfiBlock3

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej
          CFI NoCalls
        THUMB
// static __interwork __softfp void NVIC_SetPriority(IRQn_Type, uint32_t)
_ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
        MOVS     R2,R0
        SXTB     R2,R2            ;; SignExt  R2,R2,#+24,#+24
        CMP      R2,#+0
        BPL.N    ??NVIC_SetPriority_0
        LSLS     R2,R1,#+5
        LDR.W    R3,??DataTable8_3  ;; 0xe000ed18
        MOVS     R4,R0
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ANDS     R4,R4,#0xF
        ADD      R3,R3,R4
        STRB     R2,[R3, #-4]
        B.N      ??NVIC_SetPriority_1
??NVIC_SetPriority_0:
        LSLS     R2,R1,#+5
        LDR.W    R3,??DataTable8_4  ;; 0xe000e400
        MOVS     R4,R0
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        STRB     R2,[R3, R4]
??NVIC_SetPriority_1:
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _ZN5TimerC1Eh
          CFI NoCalls
        THUMB
//    7 Timer::Timer(uint8_t tmr_num)
//    8 {
_ZN5TimerC1Eh:
        MOVS     R2,#+0
        STR      R2,[R0, #+8]
        MOVS     R2,#+0
        MOVS     R3,#+0
        STRD     R2,R3,[R0, #+16]
        MOVS     R2,#+1
        STRB     R2,[R0, #+24]
//    9     switch(tmr_num)
        MOVS     R2,R1
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+0
        BEQ.N    ??Timer_0
        CMP      R2,#+2
        BEQ.N    ??Timer_1
        BCC.N    ??Timer_2
        CMP      R2,#+4
        BEQ.N    ??Timer_3
        BCC.N    ??Timer_4
        B.N      ??Timer_5
//   10     {        
//   11         case 0:
//   12             _TIMER = NRF_TIMER0;
??Timer_0:
        LDR.W    R2,??DataTable8_5  ;; 0x40008000
        STR      R2,[R0, #+0]
//   13             _IRQn = TIMER0_IRQn;
        MOVS     R2,#+8
        STRB     R2,[R0, #+4]
//   14             break;
        B.N      ??Timer_6
//   15         case 1:
//   16             _TIMER = NRF_TIMER1;
??Timer_2:
        LDR.W    R2,??DataTable8_6  ;; 0x40009000
        STR      R2,[R0, #+0]
//   17             _IRQn = TIMER1_IRQn;
        MOVS     R2,#+9
        STRB     R2,[R0, #+4]
//   18             break;
        B.N      ??Timer_6
//   19         case 2:
//   20             _TIMER = NRF_TIMER2;
??Timer_1:
        LDR.W    R2,??DataTable8_7  ;; 0x4000a000
        STR      R2,[R0, #+0]
//   21             _IRQn = TIMER2_IRQn;
        MOVS     R2,#+10
        STRB     R2,[R0, #+4]
//   22             break;
        B.N      ??Timer_6
//   23         case 3:
//   24             _TIMER = NRF_TIMER3;
??Timer_4:
        LDR.W    R2,??DataTable8_8  ;; 0x4001a000
        STR      R2,[R0, #+0]
//   25             _IRQn = TIMER3_IRQn;
        MOVS     R2,#+26
        STRB     R2,[R0, #+4]
//   26             break;
        B.N      ??Timer_6
//   27         case 4:
//   28             _TIMER = NRF_TIMER4;
??Timer_3:
        LDR.W    R2,??DataTable8_9  ;; 0x4001b000
        STR      R2,[R0, #+0]
//   29             _IRQn = TIMER4_IRQn;
        MOVS     R2,#+27
        STRB     R2,[R0, #+4]
//   30             break;
        B.N      ??Timer_6
//   31         default:
//   32              _TIMER = nullptr;
??Timer_5:
        MOVS     R2,#+0
        STR      R2,[R0, #+0]
//   33             break;
//   34     }
//   35 }
??Timer_6:
        BX       LR               ;; return
          CFI EndBlock cfiBlock5
//   36 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN5Timer4initEjjb
        THUMB
//   37 void    Timer::init(uint32_t presc, uint32_t compare_val, bool circulary)
//   38 {
_ZN5Timer4initEjjb:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R7,R3
//   39     _TIMER->MODE = TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
        MOVS     R0,#+0
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+1284]
//   40     _TIMER->BITMODE = TIMER_BITMODE_BITMODE_24Bit << TIMER_BITMODE_BITMODE_Pos;
        MOVS     R0,#+2
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+1288]
//   41 
//   42     _TIMER->PRESCALER = presc << TIMER_PRESCALER_PRESCALER_Pos;
        LDR      R0,[R4, #+0]
        STR      R5,[R0, #+1296]
//   43     setCaptureCompare(0, compare_val, circulary);
        MOVS     R3,R7
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MOVS     R2,R6
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN5Timer17setCaptureCompareEhhb
        BL       _ZN5Timer17setCaptureCompareEhhb
//   44 
//   45     resume();
        MOVS     R0,R4
          CFI FunCall _ZN5Timer6resumeEv
        BL       _ZN5Timer6resumeEv
//   46 }
        POP      {R0,R4-R7,PC}    ;; return
          CFI EndBlock cfiBlock6
//   47 
//   48  // cc_num:0..5, priority 0..7

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function _ZN5Timer6setIRQEhh
        THUMB
//   49 void Timer::setIRQ(uint8_t cc_num, uint8_t priority)  
//   50 { 
_ZN5Timer6setIRQEhh:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
//   51     switch(cc_num)
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??setIRQ_0
        CMP      R0,#+2
        BEQ.N    ??setIRQ_1
        BCC.N    ??setIRQ_2
        CMP      R0,#+4
        BEQ.N    ??setIRQ_3
        BCC.N    ??setIRQ_4
        CMP      R0,#+5
        BEQ.N    ??setIRQ_5
        B.N      ??setIRQ_6
//   52     {
//   53         case 0:
//   54             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
??setIRQ_0:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x10000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   55             break;
        B.N      ??setIRQ_7
//   56         case 1:
//   57             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos;
??setIRQ_2:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x20000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   58             break;
        B.N      ??setIRQ_7
//   59         case 2:
//   60             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE2_Enabled << TIMER_INTENSET_COMPARE2_Pos;
??setIRQ_1:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x40000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   61             break;
        B.N      ??setIRQ_7
//   62         case 3:
//   63             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE3_Enabled << TIMER_INTENSET_COMPARE3_Pos;
??setIRQ_4:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x80000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   64             break;
        B.N      ??setIRQ_7
//   65         case 4:
//   66             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE4_Enabled << TIMER_INTENSET_COMPARE4_Pos;
??setIRQ_3:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x100000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   67             break;
        B.N      ??setIRQ_7
//   68         case 5:
//   69             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE5_Enabled << TIMER_INTENSET_COMPARE5_Pos;
??setIRQ_5:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x200000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   70             break;
        B.N      ??setIRQ_7
//   71         default:
//   72             break;
//   73     }
//   74 
//   75     NVIC_SetPriority(_IRQn, priority);
??setIRQ_6:
??setIRQ_7:
        MOVS     R1,R6
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        LDRSB    R0,[R4, #+4]
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej
//   76     NVIC_ClearPendingIRQ(_IRQn);
        LDRSB    R0,[R4, #+4]
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type
//   77     NVIC_EnableIRQ(_IRQn);
        LDRSB    R0,[R4, #+4]
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type
//   78 }
        POP      {R4-R6,PC}       ;; return
          CFI EndBlock cfiBlock7
//   79 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _ZN5Timer17setCaptureCompareEhhb
          CFI NoCalls
        THUMB
//   80 void Timer::setCaptureCompare(uint8_t cc_num, uint8_t value, bool circulary)  
//   81 { 
_ZN5Timer17setCaptureCompareEhhb:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//   82     switch(cc_num)
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+0
        BEQ.N    ??setCaptureCompare_0
        CMP      R4,#+2
        BEQ.N    ??setCaptureCompare_1
        BCC.N    ??setCaptureCompare_2
        CMP      R4,#+4
        BEQ.N    ??setCaptureCompare_3
        BCC.N    ??setCaptureCompare_4
        CMP      R4,#+5
        BEQ.N    ??setCaptureCompare_5
        B.N      ??setCaptureCompare_6
//   83     {
//   84         case 0:
//   85             _TIMER->CC[0] = value;
??setCaptureCompare_0:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1344]
//   86             break;
        B.N      ??setCaptureCompare_7
//   87         case 1:
//   88             _TIMER->CC[1] = value;
??setCaptureCompare_2:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1348]
//   89             break;
        B.N      ??setCaptureCompare_7
//   90         case 2:
//   91             _TIMER->CC[2] = value;
??setCaptureCompare_1:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1352]
//   92             break;
        B.N      ??setCaptureCompare_7
//   93         case 3:
//   94             _TIMER->CC[3] = value;
??setCaptureCompare_4:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1356]
//   95             break;
        B.N      ??setCaptureCompare_7
//   96         case 4:
//   97             _TIMER->CC[4] = value;
??setCaptureCompare_3:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1360]
//   98             break;
        B.N      ??setCaptureCompare_7
//   99         case 5:
//  100             _TIMER->CC[5] = value;
??setCaptureCompare_5:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1364]
//  101             break;
        B.N      ??setCaptureCompare_7
//  102         default:
//  103             break;
//  104     }
//  105 
//  106     if(circulary)
??setCaptureCompare_6:
??setCaptureCompare_7:
        MOVS     R4,R3
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+0
        BEQ.N    ??setCaptureCompare_8
//  107     {
//  108         switch(cc_num)
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+0
        BEQ.N    ??setCaptureCompare_9
        CMP      R4,#+2
        BEQ.N    ??setCaptureCompare_10
        BCC.N    ??setCaptureCompare_11
        CMP      R4,#+4
        BEQ.N    ??setCaptureCompare_12
        BCC.N    ??setCaptureCompare_13
        CMP      R4,#+5
        BEQ.N    ??setCaptureCompare_14
        B.N      ??setCaptureCompare_15
//  109         {
//  110             case 0:
//  111                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
??setCaptureCompare_9:
        MOVS     R4,#+1
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  112                 break;
        B.N      ??setCaptureCompare_8
//  113             case 1:
//  114                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE1_CLEAR_Enabled << TIMER_SHORTS_COMPARE1_CLEAR_Pos;
??setCaptureCompare_11:
        MOVS     R4,#+2
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  115                 break;
        B.N      ??setCaptureCompare_8
//  116             case 2:
//  117                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE2_CLEAR_Enabled << TIMER_SHORTS_COMPARE2_CLEAR_Pos;
??setCaptureCompare_10:
        MOVS     R4,#+4
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  118                 break;
        B.N      ??setCaptureCompare_8
//  119             case 3:
//  120                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE3_CLEAR_Enabled << TIMER_SHORTS_COMPARE3_CLEAR_Pos;
??setCaptureCompare_13:
        MOVS     R4,#+8
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  121                 break;
        B.N      ??setCaptureCompare_8
//  122             case 4:
//  123                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE4_CLEAR_Enabled << TIMER_SHORTS_COMPARE4_CLEAR_Pos;
??setCaptureCompare_12:
        MOVS     R4,#+16
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  124                 break;
        B.N      ??setCaptureCompare_8
//  125             case 5:
//  126                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE5_CLEAR_Enabled << TIMER_SHORTS_COMPARE5_CLEAR_Pos;
??setCaptureCompare_14:
        MOVS     R4,#+32
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  127                 break;
        B.N      ??setCaptureCompare_8
//  128             default:
//  129                 break;
//  130         }      
//  131     }
//  132    
//  133 }
??setCaptureCompare_15:
??setCaptureCompare_8:
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock8
//  134 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function _ZN5Timer9incrementEj
          CFI NoCalls
        THUMB
//  135 void   Timer::increment(uint32_t dT)
//  136 {
_ZN5Timer9incrementEj:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//  137     __disable_interrupt();
        CPSID    I
//  138 
//  139     _time += dT;
        LDRD     R4,R5,[R0, #+16]
        MOVS     R2,R1
        MOVS     R3,#+0
        ADDS     R2,R4,R2
        ADCS     R3,R5,R3
        STRD     R2,R3,[R0, #+16]
//  140 
//  141     __enable_interrupt();  
        CPSIE    I
//  142 }
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock9
//  143 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function _ZNK5Timer6get_msEv
          CFI NoCalls
        THUMB
//  144 uint64_t   Timer::get_ms(void) const
//  145 {
_ZNK5Timer6get_msEv:
        MOVS     R2,R0
//  146     uint64_t res;
//  147     
//  148     __disable_interrupt();
        CPSID    I
//  149     res = _time;
        LDRD     R0,R1,[R2, #+16]
//  150     __enable_interrupt();
        CPSIE    I
//  151     
//  152     return res; 
        BX       LR               ;; return
//  153 }
          CFI EndBlock cfiBlock10
//  154 
//  155 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function _ZN5Timer8delay_msEj
        THUMB
//  156 void Timer::delay_ms(uint32_t ms)
//  157 {
_ZN5Timer8delay_msEj:
        PUSH     {R4-R8,LR}
          CFI R14 Frame(CFA, -4)
          CFI R8 Frame(CFA, -8)
          CFI R7 Frame(CFA, -12)
          CFI R6 Frame(CFA, -16)
          CFI R5 Frame(CFA, -20)
          CFI R4 Frame(CFA, -24)
          CFI CFA R13+24
        MOV      R8,R0
        MOVS     R6,R1
//  158     uint64_t time = get_ms();
        MOV      R0,R8
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
//  159     
//  160     time += (uint64_t)ms;
        MOVS     R7,#+0
        ADDS     R4,R0,R6
        ADCS     R5,R1,R7
//  161     
//  162     do 
//  163     {
//  164         __WFI();
??delay_ms_0:
        WFI      
//  165         WATCHDOGRESET;
        LDR.N    R0,??DataTable8_10  ;; 0x6e524635
        LDR.N    R1,??DataTable8_11  ;; 0x40010600
        STR      R0,[R1, #+0]
//  166     }while (time > get_ms());
        MOV      R0,R8
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        CMP      R1,R5
        BCC.N    ??delay_ms_0
        BHI.N    ??delay_ms_1
        CMP      R0,R4
        BCC.N    ??delay_ms_0
//  167 }
??delay_ms_1:
        POP      {R4-R8,PC}       ;; return
          CFI EndBlock cfiBlock11
//  168 
//  169 #pragma optimize=none

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function _ZN5Timer8delay_usEj
          CFI NoCalls
        THUMB
//  170 void Timer::delay_us(uint32_t us)
//  171 {
_ZN5Timer8delay_usEj:
        SUB      SP,SP,#+4
          CFI CFA R13+4
//  172 	for(; us; us--)
??delay_us_0:
        CMP      R1,#+0
        BEQ.N    ??delay_us_1
//  173 		for(volatile uint32_t j = DELAY_1US; j; j--);
        MOVS     R2,#+4
        STR      R2,[SP, #+0]
??delay_us_2:
        LDR      R2,[SP, #+0]
        CMP      R2,#+0
        BEQ.N    ??delay_us_3
        LDR      R2,[SP, #+0]
        SUBS     R2,R2,#+1
        STR      R2,[SP, #+0]
        B.N      ??delay_us_2
??delay_us_3:
        SUBS     R1,R1,#+1
        B.N      ??delay_us_0
//  174 }
??delay_us_1:
        ADD      SP,SP,#+4
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock12
//  175 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function _ZN5Timer6get_usEv
          CFI NoCalls
        THUMB
//  176 uint64_t   Timer::get_us(void)
//  177 {
_ZN5Timer6get_usEv:
        PUSH     {R4-R9}
          CFI R9 Frame(CFA, -4)
          CFI R8 Frame(CFA, -8)
          CFI R7 Frame(CFA, -12)
          CFI R6 Frame(CFA, -16)
          CFI R5 Frame(CFA, -20)
          CFI R4 Frame(CFA, -24)
          CFI CFA R13+24
        MOVS     R2,R0
//  178     uint64_t res;
//  179 
//  180     __disable_interrupt();
        CPSID    I
//  181 
//  182     _TIMER->TASKS_CAPTURE[0] = 0;
        MOVS     R0,#+0
        LDR      R1,[R2, #+0]
        STR      R0,[R1, #+64]
//  183     _TIMER->TASKS_CAPTURE[0] = 1;
        MOVS     R0,#+1
        LDR      R1,[R2, #+0]
        STR      R0,[R1, #+64]
//  184 
//  185     res = (uint64_t)_TIMER->CC[0];
        LDR      R0,[R2, #+0]
        LDR      R0,[R0, #+1344]
        MOVS     R1,#+0
//  186 
//  187     __enable_interrupt();
        CPSIE    I
//  188 
//  189     res += _time * 1000;
        LDRD     R4,R5,[R2, #+16]
        MOV      R6,#+1000
        MOVS     R7,#+0
        UMULL    R8,R9,R6,R4
        MLA      R9,R6,R5,R9
        MLA      R9,R7,R4,R9
        ADDS     R0,R0,R8
        ADCS     R1,R1,R9
//  190 
//  191     return res;  
        POP      {R4-R9}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI R8 SameValue
          CFI R9 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
//  192 }
          CFI EndBlock cfiBlock13
//  193 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock14 Using cfiCommon0
          CFI Function _ZN5Timer5pauseEv
          CFI NoCalls
        THUMB
//  194 void   Timer::pause()
//  195 {
//  196     _TIMER->TASKS_STOP = 1;
_ZN5Timer5pauseEv:
        MOVS     R1,#+1
        LDR      R2,[R0, #+0]
        STR      R1,[R2, #+4]
//  197     _TIMER->TASKS_SHUTDOWN = 1;
        MOVS     R1,#+1
        LDR      R2,[R0, #+0]
        STR      R1,[R2, #+16]
//  198 
//  199     _is_paused = true;
        MOVS     R1,#+1
        STRB     R1,[R0, #+24]
//  200 }
        BX       LR               ;; return
          CFI EndBlock cfiBlock14
//  201 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock15 Using cfiCommon0
          CFI Function _ZN5Timer6resumeEv
          CFI NoCalls
        THUMB
//  202 void   Timer::resume()
//  203 {
//  204     if(_is_paused)
_ZN5Timer6resumeEv:
        LDRB     R1,[R0, #+24]
        CMP      R1,#+0
        BEQ.N    ??resume_0
//  205     {
//  206         _TIMER->TASKS_START = 1;
        MOVS     R1,#+1
        LDR      R2,[R0, #+0]
        STR      R1,[R2, #+0]
//  207         _is_paused = false;
        MOVS     R1,#+0
        STRB     R1,[R0, #+24]
//  208     }
//  209 }
??resume_0:
        BX       LR               ;; return
          CFI EndBlock cfiBlock15
//  210 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock16 Using cfiCommon0
          CFI Function _ZN5Timer5onIRQEv
        THUMB
//  211 void   Timer::onIRQ()
//  212 {
_ZN5Timer5onIRQEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  213     _TIMER->EVENTS_COMPARE[0] = 0;
        MOVS     R0,#+0
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+320]
//  214 
//  215     if (_on_irq_callback)
        LDR      R0,[R4, #+8]
        CMP      R0,#+0
        BEQ.N    ??onIRQ_0
//  216     {
//  217         _on_irq_callback(1);
        MOVS     R0,#+1
        LDR      R1,[R4, #+8]
          CFI FunCall
        BLX      R1
//  218     }
//  219 }
??onIRQ_0:
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock16
//  220 
//  221 #define ADC_MEAS_INTERVAL  (300)    // in milliseconds

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock17 Using cfiCommon0
          CFI Function _Z18sys_timer_callbackj
        THUMB
//  222 void sys_timer_callback(uint32_t value)
//  223 {
_Z18sys_timer_callbackj:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R4,R0
//  224     static  uint8_t activeLeds = 0;    
//  225     static uint64_t adcTmr = 0;
//  226     
//  227     sys_timer.increment(value);
        LDR.N    R5,??DataTable8
        MOVS     R1,R4
        MOVS     R0,R5
          CFI FunCall _ZN5Timer9incrementEj
        BL       _ZN5Timer9incrementEj
//  228     
//  229     activeLeds = led_drivers_handle();
        LDR.N    R6,??DataTable8_12
          CFI FunCall _Z18led_drivers_handlev
        BL       _Z18led_drivers_handlev
        STRB     R0,[R6, #+0]
//  230     
//  231     // periodically start measure task for adc
//  232     if((sys_timer.get_ms() - adcTmr) > ADC_MEAS_INTERVAL)
        MOVS     R0,R5
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR.N    R7,??DataTable8_13
        LDRD     R2,R3,[R7, #+0]
        SUBS     R0,R0,R2
        SBCS     R1,R1,R3
        MOVW     R2,#+301
        MOVS     R3,#+0
        CMP      R1,R3
        BCC.N    ??sys_timer_callback_0
        BHI.N    ??sys_timer_callback_1
        CMP      R0,R2
        BCC.N    ??sys_timer_callback_0
//  233     {
//  234         adcTmr = sys_timer.get_ms();
??sys_timer_callback_1:
        MOVS     R0,R5
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        STRD     R0,R1,[R7, #+0]
//  235         adc_unite.measure();
        LDR.N    R0,??DataTable8_14
          CFI FunCall _ZN3ADCILi6EE7measureEv
        BL       _ZN3ADCILi6EE7measureEv
//  236     }
//  237     
//  238     UNUSED(activeLeds);
??sys_timer_callback_0:
        LDRB     R0,[R6, #+0]
        STRB     R0,[R6, #+0]
//  239 }
        POP      {R0,R4-R7,PC}    ;; return
          CFI EndBlock cfiBlock17
//  240 

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//  241 Timer sys_timer(0);
sys_timer:
        DS8 32
//  242 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock18 Using cfiCommon0
          CFI Function TIMER0_IRQHandler
        THUMB
//  243 extern "C" void TIMER0_IRQHandler(){ sys_timer.onIRQ(); }
TIMER0_IRQHandler:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
        LDR.N    R0,??DataTable8
          CFI FunCall _ZN5Timer5onIRQEv
        BL       _ZN5Timer5onIRQEv
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock18

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8:
        DATA32
        DC32     sys_timer

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_1:
        DATA32
        DC32     0xe000e100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_2:
        DATA32
        DC32     0xe000e280

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_3:
        DATA32
        DC32     0xe000ed18

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_4:
        DATA32
        DC32     0xe000e400

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_5:
        DATA32
        DC32     0x40008000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_6:
        DATA32
        DC32     0x40009000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_7:
        DATA32
        DC32     0x4000a000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_8:
        DATA32
        DC32     0x4001a000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_9:
        DATA32
        DC32     0x4001b000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_10:
        DATA32
        DC32     0x6e524635

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_11:
        DATA32
        DC32     0x40010600

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_12:
        DATA32
        DC32     `sys_timer_callback(uint32_t)::activeLeds`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_13:
        DATA32
        DC32     `sys_timer_callback(uint32_t)::adcTmr`

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable8_14:
        DATA32
        DC32     adc_unite

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock19 Using cfiCommon0
          CFI Function TIMER1_IRQHandler
          CFI NoCalls
        THUMB
//  244 extern "C" void TIMER1_IRQHandler(){ return; }
TIMER1_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock19

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock20 Using cfiCommon0
          CFI Function TIMER2_IRQHandler
          CFI NoCalls
        THUMB
//  245 extern "C" void TIMER2_IRQHandler(){ return; }
TIMER2_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock20

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock21 Using cfiCommon0
          CFI Function TIMER3_IRQHandler
          CFI NoCalls
        THUMB
//  246 extern "C" void TIMER3_IRQHandler(){ return; }
TIMER3_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock21

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock22 Using cfiCommon0
          CFI Function TIMER4_IRQHandler
          CFI NoCalls
        THUMB
//  247 extern "C" void TIMER4_IRQHandler(){ return; }
TIMER4_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock22

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE6enableEv
          CFI Block cfiBlock23 Using cfiCommon0
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
          CFI EndBlock cfiBlock23

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE7disableEv
          CFI Block cfiBlock24 Using cfiCommon0
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
          CFI EndBlock cfiBlock24

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE4initEv
          CFI Block cfiBlock25 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE4initEv
        THUMB
// __interwork __softfp void ADC<6>::init()
_ZN3ADCILi6EE4initEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE6enableEv
        BL       _ZN3ADCILi6EE6enableEv
        ADDS     R0,R4,#+144
        LDR.N    R1,??init_0      ;; 0x4000762c
        STR      R0,[R1, #+0]
        MOVS     R0,#+6
        LDR.N    R1,??init_0+0x4  ;; 0x40007630
        STR      R0,[R1, #+0]
        LDRB     R0,[R4, #+156]
        LDR.N    R1,??init_0+0x8  ;; 0x400075f0
        STR      R0,[R1, #+0]
        LDR.N    R1,??init_0+0xC  ;; 0x40007110
        MOVS     R0,#+0
        STR      R0,[R1, #+0]
        MOVS     R0,#+1
        LDR.N    R2,??init_0+0x10  ;; 0x4000700c
        STR      R0,[R2, #+0]
??init_1:
        LDR      R0,[R1, #+0]
        CMP      R0,#+0
        BEQ.N    ??init_1
        MOVS     R1,#+80
        LDR.N    R0,??init_0+0x14
          CFI FunCall _ZN5Timer8delay_usEj
        BL       _ZN5Timer8delay_usEj
        MOVS     R1,#+7
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE20setConvertionEND_IRQEh
        BL       _ZN3ADCILi6EE20setConvertionEND_IRQEh
        POP      {R4,PC}          ;; return
        DATA
??init_0:
        DATA32
        DC32     0x4000762c
        DC32     0x40007630
        DC32     0x400075f0
        DC32     0x40007110
        DC32     0x4000700c
        DC32     sys_timer
          CFI EndBlock cfiBlock25

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE6deinitEv
          CFI Block cfiBlock26 Using cfiCommon0
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
        MOVS     R1,#+0
        LDR.N    R2,??deinit_0    ;; 0x40007510
        STR      R1,[R2, #+0]
        MOVS     R1,#+0
        LDR.N    R2,??deinit_0+0x4  ;; 0x40007518
        STR      R1,[R2, #+0]
        ADDS     R0,R0,#+1
        B.N      ??deinit_1
??deinit_2:
        MOVS     R0,#+1
        LDR.N    R1,??deinit_0+0x8  ;; 0x40007008
        STR      R0,[R1, #+0]
        MOVS     R0,#+0
        LDR.N    R1,??deinit_0+0xC  ;; 0x40007300
        STR      R0,[R1, #+0]
        MOVS     R0,#+0
        LDR.N    R1,??deinit_0+0x10  ;; 0x40007308
        STR      R0,[R1, #+0]
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE7disableEv
        BL       _ZN3ADCILi6EE7disableEv
        POP      {R4,PC}          ;; return
        DATA
??deinit_0:
        DATA32
        DC32     0x40007510
        DC32     0x40007518
        DC32     0x40007008
        DC32     0x40007300
        DC32     0x40007308
          CFI EndBlock cfiBlock26

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE7measureEv
          CFI Block cfiBlock27 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE7measureEv
        THUMB
// __interwork __softfp void ADC<6>::measure()
_ZN3ADCILi6EE7measureEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE4initEv
        BL       _ZN3ADCILi6EE4initEv
        LDR.N    R1,??measure_0   ;; 0x40007100
        MOVS     R0,#+0
        STR      R0,[R1, #+0]
        MOVS     R0,#+1
        LDR.N    R2,??measure_0+0x4  ;; 0x40007000
        STR      R0,[R2, #+0]
??measure_1:
        LDR      R0,[R1, #+0]
        CMP      R0,#+0
        BEQ.N    ??measure_1
        MOVS     R0,#+1
        LDR.N    R1,??measure_0+0x8  ;; 0x40007004
        STR      R0,[R1, #+0]
??measure_2:
        LDR.N    R0,??measure_0+0xC  ;; 0x40007104
        LDR      R0,[R0, #+0]
        CMP      R0,#+1
        BEQ.N    ??measure_2
        MOVS     R0,R4
          CFI FunCall _ZN3ADCILi6EE6deinitEv
        BL       _ZN3ADCILi6EE6deinitEv
        POP      {R4,PC}          ;; return
        Nop      
        DATA
??measure_0:
        DATA32
        DC32     0x40007100
        DC32     0x40007000
        DC32     0x40007004
        DC32     0x40007104
          CFI EndBlock cfiBlock27

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN3ADCILi6EE20setConvertionEND_IRQEh
          CFI Block cfiBlock28 Using cfiCommon0
          CFI Function _ZN3ADCILi6EE20setConvertionEND_IRQEh
        THUMB
// __interwork __softfp void ADC<6>::setConvertionEND_IRQ(uint8_t)
_ZN3ADCILi6EE20setConvertionEND_IRQEh:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R0,#-1
        LDR.N    R1,??setConvertionEND_IRQ_0  ;; 0x40007308
        STR      R0,[R1, #+0]
        MOVS     R0,#+2
        LDR.N    R1,??setConvertionEND_IRQ_0+0x4  ;; 0x40007300
        STR      R0,[R1, #+0]
        MOVS     R0,#+1
        LDR.N    R1,??setConvertionEND_IRQ_0+0x8  ;; 0x40007304
        STR      R0,[R1, #+0]
        MOVS     R0,#+0
        LDR.N    R1,??setConvertionEND_IRQ_0+0xC  ;; 0x40007100
        STR      R0,[R1, #+0]
        MOVS     R0,#+0
        LDR.N    R1,??setConvertionEND_IRQ_0+0x10  ;; 0x40007104
        STR      R0,[R1, #+0]
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,#+7
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej
        MOVS     R0,#+7
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type
        MOVS     R0,#+7
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type
        POP      {R0,R4,R5,PC}    ;; return
        Nop      
        DATA
??setConvertionEND_IRQ_0:
        DATA32
        DC32     0x40007308
        DC32     0x40007300
        DC32     0x40007304
        DC32     0x40007100
        DC32     0x40007104
          CFI EndBlock cfiBlock28

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
//    41 bytes in section .bss
//     4 bytes in section .init_array
// 1'400 bytes in section .text
// 
// 1'060 bytes of CODE memory (+ 344 bytes shared)
//    41 bytes of DATA memory
//
//Errors: none
//Warnings: none
