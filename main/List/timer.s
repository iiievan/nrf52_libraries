///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        02/Feb/2021  18:20:24
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\timer\timer.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EWAF0A.tmp
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
//        E:\cpp\nrf52_libraries\timer\ -On --c++ --no_exceptions --no_rtti)
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

        PUBLIC TIMER0_IRQHandler
        PUBLIC TIMER1_IRQHandler
        PUBLIC TIMER2_IRQHandler
        PUBLIC TIMER3_IRQHandler
        PUBLIC TIMER4_IRQHandler
        PUBLIC _Z18sys_timer_callbackj
        PUBLIC _ZN5Timer17setCaptureCompareEhhb
        PUBLIC _ZN5Timer4initEjjb
        PUBLIC _ZN5Timer5onIRQEv
        PUBLIC _ZN5Timer5pauseEv
        PUBLIC _ZN5Timer6get_usEv
        PUBLIC _ZN5Timer6resumeEv
        PUBLIC _ZN5Timer6setIRQEhh
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
        LDR.W    R0,??DataTable7
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
        LDR.W    R1,??DataTable7_1  ;; 0xe000e100
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
        LDR.N    R1,??DataTable7_2  ;; 0xe000e280
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
        LDR.N    R3,??DataTable7_3  ;; 0xe000ed18
        MOVS     R4,R0
        SXTB     R4,R4            ;; SignExt  R4,R4,#+24,#+24
        ANDS     R4,R4,#0xF
        ADD      R3,R3,R4
        STRB     R2,[R3, #-4]
        B.N      ??NVIC_SetPriority_1
??NVIC_SetPriority_0:
        LSLS     R2,R1,#+5
        LDR.N    R3,??DataTable7_4  ;; 0xe000e400
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
//    4 Timer::Timer(uint8_t tmr_num)
//    5 {
_ZN5TimerC1Eh:
        MOVS     R2,#+0
        STR      R2,[R0, #+8]
        MOVS     R2,#+0
        MOVS     R3,#+0
        STRD     R2,R3,[R0, #+16]
        MOVS     R2,#+1
        STRB     R2,[R0, #+24]
//    6     switch(tmr_num)
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
//    7     {        
//    8         case 0:
//    9             _TIMER = NRF_TIMER0;
??Timer_0:
        LDR.N    R2,??DataTable7_5  ;; 0x40008000
        STR      R2,[R0, #+0]
//   10             _IRQn = TIMER0_IRQn;
        MOVS     R2,#+8
        STRB     R2,[R0, #+4]
//   11             break;
        B.N      ??Timer_6
//   12         case 1:
//   13             _TIMER = NRF_TIMER1;
??Timer_2:
        LDR.N    R2,??DataTable7_6  ;; 0x40009000
        STR      R2,[R0, #+0]
//   14             _IRQn = TIMER1_IRQn;
        MOVS     R2,#+9
        STRB     R2,[R0, #+4]
//   15             break;
        B.N      ??Timer_6
//   16         case 2:
//   17             _TIMER = NRF_TIMER2;
??Timer_1:
        LDR.N    R2,??DataTable7_7  ;; 0x4000a000
        STR      R2,[R0, #+0]
//   18             _IRQn = TIMER2_IRQn;
        MOVS     R2,#+10
        STRB     R2,[R0, #+4]
//   19             break;
        B.N      ??Timer_6
//   20         case 3:
//   21             _TIMER = NRF_TIMER3;
??Timer_4:
        LDR.N    R2,??DataTable7_8  ;; 0x4001a000
        STR      R2,[R0, #+0]
//   22             _IRQn = TIMER3_IRQn;
        MOVS     R2,#+26
        STRB     R2,[R0, #+4]
//   23             break;
        B.N      ??Timer_6
//   24         case 4:
//   25             _TIMER = NRF_TIMER4;
??Timer_3:
        LDR.N    R2,??DataTable7_9  ;; 0x4001b000
        STR      R2,[R0, #+0]
//   26             _IRQn = TIMER4_IRQn;
        MOVS     R2,#+27
        STRB     R2,[R0, #+4]
//   27             break;
        B.N      ??Timer_6
//   28         default:
//   29              _TIMER = nullptr;
??Timer_5:
        MOVS     R2,#+0
        STR      R2,[R0, #+0]
//   30             break;
//   31     }
//   32 }
??Timer_6:
        BX       LR               ;; return
          CFI EndBlock cfiBlock5
//   33 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN5Timer4initEjjb
        THUMB
//   34 void    Timer::init(uint32_t presc, uint32_t compare_val, bool circulary)
//   35 {
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
//   36     _TIMER->MODE = TIMER_MODE_MODE_Timer << TIMER_MODE_MODE_Pos;
        MOVS     R0,#+0
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+1284]
//   37     _TIMER->BITMODE = TIMER_BITMODE_BITMODE_24Bit << TIMER_BITMODE_BITMODE_Pos;
        MOVS     R0,#+2
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+1288]
//   38 
//   39     _TIMER->PRESCALER = presc << TIMER_PRESCALER_PRESCALER_Pos;
        LDR      R0,[R4, #+0]
        STR      R5,[R0, #+1296]
//   40     setCaptureCompare(0, compare_val, circulary);
        MOVS     R3,R7
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MOVS     R2,R6
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R1,#+0
        MOVS     R0,R4
          CFI FunCall _ZN5Timer17setCaptureCompareEhhb
        BL       _ZN5Timer17setCaptureCompareEhhb
//   41 
//   42     resume();
        MOVS     R0,R4
          CFI FunCall _ZN5Timer6resumeEv
        BL       _ZN5Timer6resumeEv
//   43 }
        POP      {R0,R4-R7,PC}    ;; return
          CFI EndBlock cfiBlock6
//   44 
//   45  // cc_num:0..5, priority 0..7

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function _ZN5Timer6setIRQEhh
        THUMB
//   46 void Timer::setIRQ(uint8_t cc_num, uint8_t priority)  
//   47 { 
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
//   48     switch(cc_num)
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
//   49     {
//   50         case 0:
//   51             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE0_Enabled << TIMER_INTENSET_COMPARE0_Pos;
??setIRQ_0:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x10000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   52             break;
        B.N      ??setIRQ_7
//   53         case 1:
//   54             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE1_Enabled << TIMER_INTENSET_COMPARE1_Pos;
??setIRQ_2:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x20000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   55             break;
        B.N      ??setIRQ_7
//   56         case 2:
//   57             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE2_Enabled << TIMER_INTENSET_COMPARE2_Pos;
??setIRQ_1:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x40000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   58             break;
        B.N      ??setIRQ_7
//   59         case 3:
//   60             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE3_Enabled << TIMER_INTENSET_COMPARE3_Pos;
??setIRQ_4:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x80000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   61             break;
        B.N      ??setIRQ_7
//   62         case 4:
//   63             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE4_Enabled << TIMER_INTENSET_COMPARE4_Pos;
??setIRQ_3:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x100000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   64             break;
        B.N      ??setIRQ_7
//   65         case 5:
//   66             _TIMER->INTENSET |= TIMER_INTENSET_COMPARE5_Enabled << TIMER_INTENSET_COMPARE5_Pos;
??setIRQ_5:
        LDR      R0,[R4, #+0]
        LDR      R0,[R0, #+772]
        ORRS     R0,R0,#0x200000
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+772]
//   67             break;
        B.N      ??setIRQ_7
//   68         default:
//   69             break;
//   70     }
//   71 
//   72     NVIC_SetPriority(_IRQn, priority);
??setIRQ_6:
??setIRQ_7:
        MOVS     R1,R6
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        LDRSB    R0,[R4, #+4]
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece916NVIC_SetPriorityE9IRQn_Typej
//   73     NVIC_ClearPendingIRQ(_IRQn);
        LDRSB    R0,[R4, #+4]
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece920NVIC_ClearPendingIRQE9IRQn_Type
//   74     NVIC_EnableIRQ(_IRQn);
        LDRSB    R0,[R4, #+4]
          CFI FunCall _ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type
        BL       _ZN30_INTERNAL_9_timer_cpp_4e19ece914NVIC_EnableIRQE9IRQn_Type
//   75 }
        POP      {R4-R6,PC}       ;; return
          CFI EndBlock cfiBlock7
//   76 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _ZN5Timer17setCaptureCompareEhhb
          CFI NoCalls
        THUMB
//   77 void Timer::setCaptureCompare(uint8_t cc_num, uint8_t value, bool circulary)  
//   78 { 
_ZN5Timer17setCaptureCompareEhhb:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//   79     switch(cc_num)
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
//   80     {
//   81         case 0:
//   82             _TIMER->CC[0] = value;
??setCaptureCompare_0:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1344]
//   83             break;
        B.N      ??setCaptureCompare_7
//   84         case 1:
//   85             _TIMER->CC[1] = value;
??setCaptureCompare_2:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1348]
//   86             break;
        B.N      ??setCaptureCompare_7
//   87         case 2:
//   88             _TIMER->CC[2] = value;
??setCaptureCompare_1:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1352]
//   89             break;
        B.N      ??setCaptureCompare_7
//   90         case 3:
//   91             _TIMER->CC[3] = value;
??setCaptureCompare_4:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1356]
//   92             break;
        B.N      ??setCaptureCompare_7
//   93         case 4:
//   94             _TIMER->CC[4] = value;
??setCaptureCompare_3:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1360]
//   95             break;
        B.N      ??setCaptureCompare_7
//   96         case 5:
//   97             _TIMER->CC[5] = value;
??setCaptureCompare_5:
        MOVS     R4,R2
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+1364]
//   98             break;
        B.N      ??setCaptureCompare_7
//   99         default:
//  100             break;
//  101     }
//  102 
//  103     if(circulary)
??setCaptureCompare_6:
??setCaptureCompare_7:
        MOVS     R4,R3
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        CMP      R4,#+0
        BEQ.N    ??setCaptureCompare_8
//  104     {
//  105         switch(cc_num)
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
//  106         {
//  107             case 0:
//  108                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
??setCaptureCompare_9:
        MOVS     R4,#+1
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  109                 break;
        B.N      ??setCaptureCompare_8
//  110             case 1:
//  111                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE1_CLEAR_Enabled << TIMER_SHORTS_COMPARE1_CLEAR_Pos;
??setCaptureCompare_11:
        MOVS     R4,#+2
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  112                 break;
        B.N      ??setCaptureCompare_8
//  113             case 2:
//  114                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE2_CLEAR_Enabled << TIMER_SHORTS_COMPARE2_CLEAR_Pos;
??setCaptureCompare_10:
        MOVS     R4,#+4
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  115                 break;
        B.N      ??setCaptureCompare_8
//  116             case 3:
//  117                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE3_CLEAR_Enabled << TIMER_SHORTS_COMPARE3_CLEAR_Pos;
??setCaptureCompare_13:
        MOVS     R4,#+8
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  118                 break;
        B.N      ??setCaptureCompare_8
//  119             case 4:
//  120                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE4_CLEAR_Enabled << TIMER_SHORTS_COMPARE4_CLEAR_Pos;
??setCaptureCompare_12:
        MOVS     R4,#+16
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  121                 break;
        B.N      ??setCaptureCompare_8
//  122             case 5:
//  123                  _TIMER->SHORTS = TIMER_SHORTS_COMPARE5_CLEAR_Enabled << TIMER_SHORTS_COMPARE5_CLEAR_Pos;
??setCaptureCompare_14:
        MOVS     R4,#+32
        LDR      R5,[R0, #+0]
        STR      R4,[R5, #+512]
//  124                 break;
        B.N      ??setCaptureCompare_8
//  125             default:
//  126                 break;
//  127         }      
//  128     }
//  129    
//  130 }
??setCaptureCompare_15:
??setCaptureCompare_8:
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock8
//  131 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function _ZN5Timer9incrementEj
          CFI NoCalls
        THUMB
//  132 void   Timer::increment(uint32_t dT)
//  133 {
_ZN5Timer9incrementEj:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
//  134     __disable_interrupt();
        CPSID    I
//  135 
//  136     _time += dT;
        LDRD     R4,R5,[R0, #+16]
        MOVS     R2,R1
        MOVS     R3,#+0
        ADDS     R2,R4,R2
        ADCS     R3,R5,R3
        STRD     R2,R3,[R0, #+16]
//  137 
//  138     __enable_interrupt();  
        CPSIE    I
//  139 }
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock9
//  140 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function _ZNK5Timer6get_msEv
          CFI NoCalls
        THUMB
//  141 uint64_t   Timer::get_ms(void) const
//  142 {
_ZNK5Timer6get_msEv:
        MOVS     R2,R0
//  143     uint64_t res;
//  144     
//  145     __disable_interrupt();
        CPSID    I
//  146     res = _time;
        LDRD     R0,R1,[R2, #+16]
//  147     __enable_interrupt();
        CPSIE    I
//  148     
//  149     return res; 
        BX       LR               ;; return
//  150 }
          CFI EndBlock cfiBlock10
//  151 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function _ZN5Timer6get_usEv
          CFI NoCalls
        THUMB
//  152 uint64_t   Timer::get_us(void)
//  153 {
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
//  154     uint64_t res;
//  155 
//  156     __disable_interrupt();
        CPSID    I
//  157 
//  158     _TIMER->TASKS_CAPTURE[0] = 0;
        MOVS     R0,#+0
        LDR      R1,[R2, #+0]
        STR      R0,[R1, #+64]
//  159     _TIMER->TASKS_CAPTURE[0] = 1;
        MOVS     R0,#+1
        LDR      R1,[R2, #+0]
        STR      R0,[R1, #+64]
//  160 
//  161     res = (uint64_t)_TIMER->CC[0];
        LDR      R0,[R2, #+0]
        LDR      R0,[R0, #+1344]
        MOVS     R1,#+0
//  162 
//  163     __enable_interrupt();
        CPSIE    I
//  164 
//  165     res += _time * 1000;
        LDRD     R4,R5,[R2, #+16]
        MOV      R6,#+1000
        MOVS     R7,#+0
        UMULL    R8,R9,R6,R4
        MLA      R9,R6,R5,R9
        MLA      R9,R7,R4,R9
        ADDS     R0,R0,R8
        ADCS     R1,R1,R9
//  166 
//  167     return res;  
        POP      {R4-R9}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI R6 SameValue
          CFI R7 SameValue
          CFI R8 SameValue
          CFI R9 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
//  168 }
          CFI EndBlock cfiBlock11
//  169 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function _ZN5Timer5pauseEv
          CFI NoCalls
        THUMB
//  170 void   Timer::pause()
//  171 {
//  172     _TIMER->TASKS_STOP = 1;
_ZN5Timer5pauseEv:
        MOVS     R1,#+1
        LDR      R2,[R0, #+0]
        STR      R1,[R2, #+4]
//  173     _TIMER->TASKS_SHUTDOWN = 1;
        MOVS     R1,#+1
        LDR      R2,[R0, #+0]
        STR      R1,[R2, #+16]
//  174 
//  175     _is_paused = true;
        MOVS     R1,#+1
        STRB     R1,[R0, #+24]
//  176 }
        BX       LR               ;; return
          CFI EndBlock cfiBlock12
//  177 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function _ZN5Timer6resumeEv
          CFI NoCalls
        THUMB
//  178 void   Timer::resume()
//  179 {
//  180     if(_is_paused)
_ZN5Timer6resumeEv:
        LDRB     R1,[R0, #+24]
        CMP      R1,#+0
        BEQ.N    ??resume_0
//  181     {
//  182         _TIMER->TASKS_START = 1;
        MOVS     R1,#+1
        LDR      R2,[R0, #+0]
        STR      R1,[R2, #+0]
//  183         _is_paused = false;
        MOVS     R1,#+0
        STRB     R1,[R0, #+24]
//  184     }
//  185 }
??resume_0:
        BX       LR               ;; return
          CFI EndBlock cfiBlock13
//  186 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock14 Using cfiCommon0
          CFI Function _ZN5Timer5onIRQEv
        THUMB
//  187 void   Timer::onIRQ()
//  188 {
_ZN5Timer5onIRQEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  189     _TIMER->EVENTS_COMPARE[0] = 0;
        MOVS     R0,#+0
        LDR      R1,[R4, #+0]
        STR      R0,[R1, #+320]
//  190 
//  191     if (_on_irq_callback)
        LDR      R0,[R4, #+8]
        CMP      R0,#+0
        BEQ.N    ??onIRQ_0
//  192     {
//  193         _on_irq_callback(1);
        MOVS     R0,#+1
        LDR      R1,[R4, #+8]
          CFI FunCall
        BLX      R1
//  194     }
//  195 }
??onIRQ_0:
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock14
//  196 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock15 Using cfiCommon0
          CFI Function _Z18sys_timer_callbackj
        THUMB
//  197 void sys_timer_callback(uint32_t value)
//  198 {
_Z18sys_timer_callbackj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
//  199     static uint8_t activeLeds = 0;
//  200     
//  201     sys_timer.increment(value);
        MOVS     R1,R4
        LDR.N    R0,??DataTable7
          CFI FunCall _ZN5Timer9incrementEj
        BL       _ZN5Timer9incrementEj
//  202     
//  203     activeLeds = led_drivers_handle();
        LDR.N    R5,??DataTable7_10
          CFI FunCall _Z18led_drivers_handlev
        BL       _Z18led_drivers_handlev
        STRB     R0,[R5, #+0]
//  204     
//  205     UNUSED(activeLeds);
        LDRB     R0,[R5, #+0]
        STRB     R0,[R5, #+0]
//  206 }
        POP      {R0,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock15
//  207 

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//  208 Timer sys_timer(0);
sys_timer:
        DS8 32
//  209 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock16 Using cfiCommon0
          CFI Function TIMER0_IRQHandler
        THUMB
//  210 extern "C" void TIMER0_IRQHandler(){ sys_timer.onIRQ(); }
TIMER0_IRQHandler:
        PUSH     {R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI CFA R13+8
        LDR.N    R0,??DataTable7
          CFI FunCall _ZN5Timer5onIRQEv
        BL       _ZN5Timer5onIRQEv
        POP      {R0,PC}          ;; return
          CFI EndBlock cfiBlock16

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7:
        DATA32
        DC32     sys_timer

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_1:
        DATA32
        DC32     0xe000e100

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_2:
        DATA32
        DC32     0xe000e280

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_3:
        DATA32
        DC32     0xe000ed18

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_4:
        DATA32
        DC32     0xe000e400

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_5:
        DATA32
        DC32     0x40008000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_6:
        DATA32
        DC32     0x40009000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_7:
        DATA32
        DC32     0x4000a000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_8:
        DATA32
        DC32     0x4001a000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_9:
        DATA32
        DC32     0x4001b000

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable7_10:
        DATA32
        DC32     `sys_timer_callback(uint32_t)::activeLeds`

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock17 Using cfiCommon0
          CFI Function TIMER1_IRQHandler
          CFI NoCalls
        THUMB
//  211 extern "C" void TIMER1_IRQHandler(){ return; }
TIMER1_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock17

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock18 Using cfiCommon0
          CFI Function TIMER2_IRQHandler
          CFI NoCalls
        THUMB
//  212 extern "C" void TIMER2_IRQHandler(){ return; }
TIMER2_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock18

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock19 Using cfiCommon0
          CFI Function TIMER3_IRQHandler
          CFI NoCalls
        THUMB
//  213 extern "C" void TIMER3_IRQHandler(){ return; }
TIMER3_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock19

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock20 Using cfiCommon0
          CFI Function TIMER4_IRQHandler
          CFI NoCalls
        THUMB
//  214 extern "C" void TIMER4_IRQHandler(){ return; }
TIMER4_IRQHandler:
        BX       LR               ;; return
          CFI EndBlock cfiBlock20

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
//  33 bytes in section .bss
//   4 bytes in section .init_array
// 892 bytes in section .text
// 
// 896 bytes of CODE memory
//  33 bytes of DATA memory
//
//Errors: none
//Warnings: none
