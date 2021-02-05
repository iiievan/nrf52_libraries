///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        05/Feb/2021  12:20:14
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\pwm\led_driver.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EWB7A3.tmp
//        (E:\cpp\nrf52_libraries\pwm\led_driver.cpp -D NRF52840_XXAA -D
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
//    List file    =  E:\cpp\nrf52_libraries\main\List\led_driver.s
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

        EXTERN _ZN10nrf_hw_pwm10write_chnlEhjb
        EXTERN _ZN10nrf_hw_pwm11get_led_numEj
        EXTERN _ZN10nrf_hw_pwm12set_chrg_barEs
        EXTERN _ZN10nrf_hw_pwm4stopEh
        EXTERN _ZN10nrf_hw_pwm7add_pinEj
        EXTERN _ZN10nrf_hw_pwmC2Etjjj
        EXTERN _ZN10nrf_hw_pwmC2Ev
        EXTERN _ZNK5Timer6get_msEv
        EXTERN __aeabi_d2iz
        EXTERN __aeabi_d2uiz
        EXTERN __aeabi_ui2d
        EXTERN round
        EXTERN sys_timer

        PUBLIC _Z18led_drivers_handlev
        PUBLIC _Z3nodIiET_S0_S0_
        PUBLIC _ZN10led_driver10_fade_downEv
        PUBLIC _ZN10led_driver10bright_setEj
        PUBLIC _ZN10led_driver12_need_finishEv
        PUBLIC _ZN10led_driver12set_fadetimeEj
        PUBLIC _ZN10led_driver13go_power_downEv
        PUBLIC _ZN10led_driver3runEi
        PUBLIC _ZN10led_driver3runEv
        PUBLIC _ZN10led_driver5_fadeEv
        PUBLIC _ZN10led_driver5_stopEv
        PUBLIC _ZN10led_driver6handleEv
        PUBLIC _ZN10led_driver6run_upEv
        PUBLIC _ZN10led_driver8_fade_upEv
        PUBLIC _ZN10led_driver8light_upEv
        PUBLIC _ZN10led_driver8run_downEv
        PUBLIC _ZN10led_driver8turn_offEv
        PUBLIC _ZN10led_driverC1EjP5Timertj
        PUBLIC _ZN10led_driverC1EjjjtP5Timertj
        PUBLIC _ZN10led_driverC2EjP5Timertj
        PUBLIC _ZN10led_driverC2EjjjtP5Timertj
        PUBLIC bl_btn_led
        PUBLIC btn_pr_led
        PUBLIC charge_bar
        PUBLIC green_led
        PUBLIC kb_led
        PUBLIC led_2_port_list
        PUBLIC led_list
        PUBLIC red_led
        
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
        
// E:\cpp\nrf52_libraries\pwm\led_driver.cpp
//    1 #include "led_driver.h"
//    2 #include "board.h"
//    3 
//    4 #ifdef _AUDIOGUDE_V2_BOARD

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//    5 uint32_t led_2_port_list[LEDS_NUM] = 
led_2_port_list:
        DATA32
        DC32 7, 5, 26, 11, 25, 8, 27, 6
//    6 {
//    7     LED_SYS_RED_PIN,    // P0.07 LED_SYS_RED 
//    8     LED_SYS_GREEN_PIN,  // P0.05 LED_SYS_GREEN
//    9     LED_BL_BTN_PIN,     // P0.26 LED_BL_BTN 
//   10     LED_BTN_PR_PIN,     // P0.11 LED_BTN_PR  
//   11     LED_KB_PIN,         // P0.25 LED_KB
//   12     LED_BAT_1_PIN,      // P0.08 LED_BAT_1 
//   13     LED_BAT_2_PIN,      // P0.27 LED_BAT_2
//   14     LED_BAT_3_PIN       // P0.06 LED_BAT_3 
//   15 };
//   16 
//   17 // должен быть создан до того как будут использован в производных классах ниже.
//   18 // иначе порушится вся карта пинов и каналов. Т.к. каждый led_driver является производным
//   19 // при вызове своего конструктора он сначала вызовет конструктор по умолчанию hw_pwm() - который бессмысленен чуть менее чем полностью)

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//   20 led_driver    charge_bar  ( led_2_port_list[LED_BAT_1],
charge_bar:
        DS8 56
//   21                             led_2_port_list[LED_BAT_2],
//   22                             led_2_port_list[LED_BAT_3], 128, &sys_timer);  
//   23 

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//   24 led_driver    red_led     ( led_2_port_list[LED_SYS_RED],   &sys_timer, MAX_PWM_VALUE, LED_SHORT_BLINK_MS );
red_led:
        DS8 56

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//   25 led_driver    green_led   ( led_2_port_list[LED_SYS_GREEN], &sys_timer, MAX_PWM_VALUE, LED_SHORT_BLINK_MS );
green_led:
        DS8 56

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//   26 led_driver    bl_btn_led  ( led_2_port_list[LED_BL_BTN],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
bl_btn_led:
        DS8 56

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//   27 led_driver    btn_pr_led  ( led_2_port_list[LED_BTN_PR],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
btn_pr_led:
        DS8 56

        SECTION `.bss`:DATA:REORDER:NOROOT(3)
        DATA
//   28 led_driver    kb_led      ( led_2_port_list[LED_KB],        &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
kb_led:
        DS8 56
//   29 
//   30 

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//   31 led_driver* led_list[LEDS_NUM] =
led_list:
        DATA32
        DC32 red_led, green_led, bl_btn_led, btn_pr_led, kb_led, charge_bar
        DC32 0x0, 0x0
//   32 { 
//   33     &red_led,
//   34     &green_led,
//   35     &bl_btn_led,
//   36     &btn_pr_led,
//   37     &kb_led,
//   38     &charge_bar,    // по сути это LED_BAT_1..3 входят в модуль чардж бара.
//   39     NULL,    
//   40     NULL
//   41 };
//   42 #endif //_AUDIOGUDE_V2_BOARD
//   43 
//   44 #ifdef _AUDIOGUDE_V3_BOARD
//   45 uint32_t led_2_port_list[LEDS_NUM] = 
//   46 {
//   47     LED_SYS_GREEN_PIN,  // P0.07 LED_SYS_GREEN 
//   48     LED_BL_BTN_PIN,     // P0.26 LED_BL_BTN 
//   49     LED_BTN_PR_PIN,     // P0.11 LED_BTN_PR  
//   50     LED_KB_PIN,         // P0.25 LED_KB
//   51     LED_BAT_1_PIN,      // P0.08 LED_BAT_1 
//   52     LED_BAT_2_PIN,      // P0.06 LED_BAT_2
//   53     LED_BAT_3_PIN,      // P0.04 LED_BAT_3 
//   54     LED_BAT_4_PIN,      // P0.27 LED_BAT_4
//   55     LED_BAT_5_PIN       // P0.05 LED_BAT_5 
//   56 };
//   57 
//   58 
//   59 led_driver    green_led   ( led_2_port_list[LED_SYS_GREEN], &sys_timer, MAX_PWM_VALUE, LED_SHORT_BLINK_MS );
//   60 led_driver    bl_btn_led  ( led_2_port_list[LED_BL_BTN],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   61 led_driver    btn_pr_led  ( led_2_port_list[LED_BTN_PR],    &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   62 led_driver    kb_led      ( led_2_port_list[LED_KB],        &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   63 led_driver    charge_led_1( led_2_port_list[LED_BAT_1],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   64 led_driver    charge_led_2( led_2_port_list[LED_BAT_2],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   65 led_driver    charge_led_3( led_2_port_list[LED_BAT_3],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   66 led_driver    charge_led_4( led_2_port_list[LED_BAT_4],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   67 led_driver    charge_led_5( led_2_port_list[LED_BAT_5],     &sys_timer, MAX_PWM_VALUE, LED_FAST_BLINK_MS );
//   68 
//   69 led_driver* led_list[LEDS_NUM] =
//   70 { 
//   71     &green_led,
//   72     &bl_btn_led,
//   73     &btn_pr_led,
//   74     &kb_led,
//   75     &charge_led_1,
//   76     &charge_led_2,    
//   77     &charge_led_3,
//   78     &charge_led_4,   
//   79     &charge_led_5
//   80 };
//   81 #endif
//   82 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function _ZN10led_driverC2EjP5Timertj
        THUMB
// __code __interwork __softfp led_driver::subobject led_driver(uint32_t, Timer *, uint16_t, uint32_t)
_ZN10led_driverC2EjP5Timertj:
        PUSH     {R2-R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+16
        MOVS     R4,R0
        LDR      R0,[SP, #+16]
        STR      R0,[SP, #+0]
        UXTH     R3,R3            ;; ZeroExt  R3,R3,#+16,#+16
        MOVS     R0,R4
          CFI FunCall _ZN10led_driverC1EjP5Timertj
        BL       _ZN10led_driverC1EjP5Timertj
        POP      {R1,R2,R4,PC}    ;; return
          CFI EndBlock cfiBlock0

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function _ZN10led_driverC2EjjjtP5Timertj
        THUMB
// __code __interwork __softfp led_driver::subobject led_driver(uint32_t, uint32_t, uint32_t, uint16_t, Timer *, uint16_t, uint32_t)
_ZN10led_driverC2EjjjtP5Timertj:
        PUSH     {R0-R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+24
        MOVS     R4,R0
        LDR      R0,[SP, #+36]
        STR      R0,[SP, #+12]
        LDRH     R0,[SP, #+32]
        STR      R0,[SP, #+8]
        LDR      R0,[SP, #+28]
        STR      R0,[SP, #+4]
        LDRH     R0,[SP, #+24]
        STR      R0,[SP, #+0]
        MOVS     R0,R4
          CFI FunCall _ZN10led_driverC1EjjjtP5Timertj
        BL       _ZN10led_driverC1EjjjtP5Timertj
        ADD      SP,SP,#+16
          CFI CFA R13+8
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock1

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function __sti__routine
        THUMB
// static __intrinsic __interwork __softfp void __sti__routine()
__sti__routine:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        SUB      SP,SP,#+16
          CFI CFA R13+32
        LDR.W    R4,??DataTable2
        LDR.W    R5,??DataTable2_1
        MOV      R0,#+330
        STR      R0,[SP, #+12]
        MOVS     R0,#+255
        STR      R0,[SP, #+8]
        STR      R5,[SP, #+4]
        MOVS     R0,#+128
        STR      R0,[SP, #+0]
        LDR      R3,[R4, #+28]
        LDR      R2,[R4, #+24]
        LDR      R1,[R4, #+20]
        LDR.W    R0,??DataTable2_2
          CFI FunCall _ZN10led_driverC1EjjjtP5Timertj
        BL       _ZN10led_driverC1EjjjtP5Timertj
        MOV      R0,#+330
        STR      R0,[SP, #+0]
        MOVS     R3,#+255
        MOVS     R2,R5
        LDR      R1,[R4, #+0]
        LDR.W    R0,??DataTable2_3
          CFI FunCall _ZN10led_driverC1EjP5Timertj
        BL       _ZN10led_driverC1EjP5Timertj
        MOV      R0,#+330
        STR      R0,[SP, #+0]
        MOVS     R3,#+255
        MOVS     R2,R5
        LDR      R1,[R4, #+4]
        LDR.W    R0,??DataTable2_4
          CFI FunCall _ZN10led_driverC1EjP5Timertj
        BL       _ZN10led_driverC1EjP5Timertj
        MOV      R0,#+560
        STR      R0,[SP, #+0]
        MOVS     R3,#+255
        MOVS     R2,R5
        LDR      R1,[R4, #+8]
        LDR.W    R0,??DataTable2_5
          CFI FunCall _ZN10led_driverC1EjP5Timertj
        BL       _ZN10led_driverC1EjP5Timertj
        MOV      R0,#+560
        STR      R0,[SP, #+0]
        MOVS     R3,#+255
        MOVS     R2,R5
        LDR      R1,[R4, #+12]
        LDR.W    R0,??DataTable2_6
          CFI FunCall _ZN10led_driverC1EjP5Timertj
        BL       _ZN10led_driverC1EjP5Timertj
        MOV      R0,#+560
        STR      R0,[SP, #+0]
        MOVS     R3,#+255
        MOVS     R2,R5
        LDR      R1,[R4, #+16]
        LDR.W    R0,??DataTable2_7
          CFI FunCall _ZN10led_driverC1EjP5Timertj
        BL       _ZN10led_driverC1EjP5Timertj
        ADD      SP,SP,#+20
          CFI CFA R13+12
        POP      {R4,R5,PC}       ;; return
          CFI EndBlock cfiBlock2

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function _ZN10led_driverC1EjP5Timertj
        THUMB
//   83 led_driver::led_driver(uint32_t pin, Timer *pTmr, uint16_t max_val,  uint32_t f_time)
//   84 : pTimer(pTmr)
//   85 {
_ZN10led_driverC1EjP5Timertj:
        PUSH     {R4-R8,LR}
          CFI R14 Frame(CFA, -4)
          CFI R8 Frame(CFA, -8)
          CFI R7 Frame(CFA, -12)
          CFI R6 Frame(CFA, -16)
          CFI R5 Frame(CFA, -20)
          CFI R4 Frame(CFA, -24)
          CFI CFA R13+24
        MOVS     R4,R0
        MOVS     R5,R1
        MOV      R8,R2
        MOVS     R6,R3
        LDR      R7,[SP, #+24]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwmC2Ev
        BL       _ZN10nrf_hw_pwmC2Ev
        STR      R8,[R4, #+12]
//   86     if (max_val <= LED_BRIGHT_100)
        MOVS     R0,R6
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+256
        BGE.N    ??led_driver_0
//   87     _max_val  = max_val;
        STRH     R6,[R4, #+36]
        B.N      ??led_driver_1
//   88     else
//   89     _max_val = LED_BRIGHT_100;
??led_driver_0:
        MOVS     R0,#+255
        STRH     R0,[R4, #+36]
//   90     
//   91     _fade_time = f_time;
??led_driver_1:
        STR      R7,[R4, #+40]
//   92     
//   93     set_fadetime(f_time);
        MOVS     R1,R7
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver12set_fadetimeEj
        BL       _ZN10led_driver12set_fadetimeEj
//   94     
//   95     _timer    = pTimer->get_ms() - _tout;
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R4, #+32]
        MOVS     R3,#+0
        SUBS     R0,R0,R2
        SBCS     R1,R1,R3
        STRD     R0,R1,[R4, #+24]
//   96     
//   97     // добавляем пин, если еще не добавлен.
//   98     add_pin(pin);
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm7add_pinEj
        BL       _ZN10nrf_hw_pwm7add_pinEj
//   99 
//  100     _led = get_led_num(pin);
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm11get_led_numEj
        BL       _ZN10nrf_hw_pwm11get_led_numEj
        STRB     R0,[R4, #+44]
//  101 
//  102     _bright_val      = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//  103     _fade_dir = true;
        MOVS     R0,#+1
        STRB     R0,[R4, #+45]
//  104     _run      = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+16]
//  105     _run_up   = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+17]
//  106     _run_down = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+18]
//  107     
//  108     _num_of_rptions = -1;
        MOVS     R0,#-1
        STR      R0,[R4, #+20]
//  109 }
        MOVS     R0,R4
        POP      {R4-R8,PC}       ;; return
          CFI EndBlock cfiBlock3
//  110 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _ZN10led_driverC1EjjjtP5Timertj
        THUMB
//  111 led_driver::led_driver(uint32_t pin_1, 
//  112                        uint32_t pin_2, 
//  113                        uint32_t pin_3, 
//  114                        uint16_t clock_div, 
//  115                        Timer *pTmr,  
//  116                        uint16_t max_val,  
//  117                        uint32_t f_time) 
//  118 : nrf_hw_pwm(clock_div, pin_1, pin_2, pin_3),pTimer(pTmr) 
//  119 {
_ZN10led_driverC1EjjjtP5Timertj:
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
        MOV      R11,R1
        MOVS     R6,R2
        MOV      R10,R3
        LDR      R9,[SP, #+40]
        LDR      R8,[SP, #+44]
        LDR      R4,[SP, #+48]
        LDR      R7,[SP, #+52]
        STR      R10,[SP, #+0]
        MOVS     R3,R6
        MOV      R2,R11
        MOV      R1,R9
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R0,R5
          CFI FunCall _ZN10nrf_hw_pwmC2Etjjj
        BL       _ZN10nrf_hw_pwmC2Etjjj
        STR      R8,[R5, #+12]
//  120     if (max_val <= LED_BRIGHT_100)
        MOVS     R0,R4
        UXTH     R0,R0            ;; ZeroExt  R0,R0,#+16,#+16
        CMP      R0,#+256
        BGE.N    ??led_driver_2
//  121     _max_val  = max_val;
        STRH     R4,[R5, #+36]
        B.N      ??led_driver_3
//  122     else
//  123     _max_val = LED_BRIGHT_100;
??led_driver_2:
        MOVS     R0,#+255
        STRH     R0,[R5, #+36]
//  124     
//  125     _fade_time = f_time;
??led_driver_3:
        STR      R7,[R5, #+40]
//  126     
//  127     set_fadetime(f_time);
        MOVS     R1,R7
        MOVS     R0,R5
          CFI FunCall _ZN10led_driver12set_fadetimeEj
        BL       _ZN10led_driver12set_fadetimeEj
//  128     
//  129     _timer    = pTimer->get_ms() - _tout;
        LDR      R0,[R5, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R5, #+32]
        MOVS     R3,#+0
        SUBS     R0,R0,R2
        SBCS     R1,R1,R3
        STRD     R0,R1,[R5, #+24]
//  130     
//  131     _led = get_led_num(pin_2);       // пин 2 является управляющим сам по себе одним светодиодом - первым
        MOVS     R1,R6
        MOVS     R0,R5
          CFI FunCall _ZN10nrf_hw_pwm11get_led_numEj
        BL       _ZN10nrf_hw_pwm11get_led_numEj
        STRB     R0,[R5, #+44]
//  132 
//  133     _bright_val      = 0;
        MOVS     R0,#+0
        STR      R0,[R5, #+48]
//  134     _fade_dir = true;
        MOVS     R0,#+1
        STRB     R0,[R5, #+45]
//  135     _run      = false;
        MOVS     R0,#+0
        STRB     R0,[R5, #+16]
//  136     _run_up   = false;
        MOVS     R0,#+0
        STRB     R0,[R5, #+17]
//  137     _run_down = false;
        MOVS     R0,#+0
        STRB     R0,[R5, #+18]
//  138     
//  139     _num_of_rptions = -1; 
        MOVS     R0,#-1
        STR      R0,[R5, #+20]
//  140 
//  141     set_chrg_bar(SHTDWN);
        MOVS     R1,#-1
        MOVS     R0,R5
          CFI FunCall _ZN10nrf_hw_pwm12set_chrg_barEs
        BL       _ZN10nrf_hw_pwm12set_chrg_barEs
//  142 }
        MOVS     R0,R5
        POP      {R1,R4-R11,PC}   ;; return
          CFI EndBlock cfiBlock4
//  143 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _ZN10led_driver13go_power_downEv
        THUMB
//  144 void led_driver::go_power_down(void)
//  145 {  
_ZN10led_driver13go_power_downEv:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
//  146     for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
        MOVS     R5,#+0
??go_power_down_0:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+4
        BGE.N    ??go_power_down_1
//  147     { nrf_hw_pwm::stop(pwm); }
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm4stopEh
        BL       _ZN10nrf_hw_pwm4stopEh
        ADDS     R5,R5,#+1
        B.N      ??go_power_down_0
//  148 }
??go_power_down_1:
        POP      {R0,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock5
//  149 
//  150 // функция рассичтывает период между инкрементацией свечения светодиода и  
//  151 // шаг инкрементации, так чтобы уложиться во период времени за который 
//  152 // свечение светодиода поднимется(или опустится) на заданную величину.

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN10led_driver12set_fadetimeEj
        THUMB
//  153 void led_driver::set_fadetime(uint32_t f_time)
//  154 {       
_ZN10led_driver12set_fadetimeEj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
//  155    volatile int nod;
//  156   
//  157     // рассчитываем наибольший общий делитель
//  158     if( _max_val >= f_time)
        LDRH     R0,[R4, #+36]
        CMP      R0,R5
        BCC.N    ??set_fadetime_0
//  159     {
//  160           nod = ::nod<int>((int)f_time,(int)_max_val);
        LDRH     R1,[R4, #+36]
        MOVS     R0,R5
          CFI FunCall _Z3nodIiET_S0_S0_
        BL       _Z3nodIiET_S0_S0_
        STR      R0,[SP, #+0]
//  161         _tout = (uint32_t)nod;
        LDR      R0,[SP, #+0]
        STR      R0,[R4, #+32]
//  162         _step = (uint8_t)round((double)(_max_val/(f_time/nod)));
        LDR      R0,[SP, #+0]
        UDIV     R0,R5,R0
        LDRH     R1,[R4, #+36]
        UDIV     R0,R1,R0
          CFI FunCall __aeabi_ui2d
        BL       __aeabi_ui2d
          CFI FunCall round
        BL       round
          CFI FunCall __aeabi_d2iz
        BL       __aeabi_d2iz
        STRB     R0,[R4, #+38]
        B.N      ??set_fadetime_1
//  163     }
//  164     else
//  165     {
//  166           nod = ::nod<int>((int)f_time,(int)_max_val);
??set_fadetime_0:
        LDRH     R1,[R4, #+36]
        MOVS     R0,R5
          CFI FunCall _Z3nodIiET_S0_S0_
        BL       _Z3nodIiET_S0_S0_
        STR      R0,[SP, #+0]
//  167         _tout = (uint32_t)round((double)(f_time/(_max_val/nod)));
        LDRH     R0,[R4, #+36]
        LDR      R1,[SP, #+0]
        SDIV     R0,R0,R1
        UDIV     R0,R5,R0
          CFI FunCall __aeabi_ui2d
        BL       __aeabi_ui2d
          CFI FunCall round
        BL       round
          CFI FunCall __aeabi_d2uiz
        BL       __aeabi_d2uiz
        STR      R0,[R4, #+32]
//  168         _step = nod;
        LDR      R0,[SP, #+0]
        STRB     R0,[R4, #+38]
//  169     }
//  170 }
??set_fadetime_1:
        POP      {R0,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock6
//  171 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function _ZN10led_driver8light_upEv
        THUMB
//  172 void led_driver::light_up() 
//  173 {
_ZN10led_driver8light_upEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  174     __disable_interrupt();
        CPSID    I
//  175   
//  176     _stop();    
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver5_stopEv
        BL       _ZN10led_driver5_stopEv
//  177     write_chnl(_led, LIGHT_UP);
        MOVS     R3,#+0
        MOVS     R2,#+255
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  178     
//  179     __enable_interrupt();
        CPSIE    I
//  180 } 
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock7
//  181 
//  182 // погасить светодиод полностью

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _ZN10led_driver8turn_offEv
        THUMB
//  183 void led_driver::turn_off() 
//  184 {
_ZN10led_driver8turn_offEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  185     __disable_interrupt();
        CPSID    I
//  186   
//  187     _stop();
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver5_stopEv
        BL       _ZN10led_driver5_stopEv
//  188     write_chnl(_led, TURN_OFF); 
        MOVS     R3,#+0
        MOVS     R2,#+0
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  189     
//  190     __enable_interrupt();
        CPSIE    I
//  191 }
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock8
//  192 
//  193 // установить нужную яркость светодиода

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function _ZN10led_driver10bright_setEj
        THUMB
//  194 void led_driver::bright_set(uint32_t value) 
//  195 {   
_ZN10led_driver10bright_setEj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
//  196     __disable_interrupt();
        CPSID    I
//  197 
//  198     _stop(); 
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver5_stopEv
        BL       _ZN10led_driver5_stopEv
//  199     _bright_val = value;
        STR      R5,[R4, #+48]
//  200     write_chnl(_led, value);
        MOVS     R3,#+0
        MOVS     R2,R5
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  201     
//  202     __enable_interrupt();
        CPSIE    I
//  203 }
        POP      {R0,R4,R5,PC}    ;; return
          CFI EndBlock cfiBlock9
//  204 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function _ZN10led_driver3runEv
        THUMB
//  205 void led_driver::run(void)
//  206 { 
_ZN10led_driver3runEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  207     __disable_interrupt();
        CPSID    I
//  208   
//  209     if (!_need_finish())
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver12_need_finishEv
        BL       _ZN10led_driver12_need_finishEv
        CMP      R0,#+0
        BNE.N    ??run_0
//  210     {      
//  211       _run = true;
        MOVS     R0,#+1
        STRB     R0,[R4, #+16]
//  212       // запускаем на бесконечное количество вспышек
//  213       _num_of_rptions = -1;
        MOVS     R0,#-1
        STR      R0,[R4, #+20]
//  214     }
//  215     
//  216     __enable_interrupt();
??run_0:
        CPSIE    I
//  217 } 
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock10
//  218 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function _ZN10led_driver3runEi
          CFI NoCalls
        THUMB
//  219 void led_driver::run(int repetitions)
//  220 { 
//  221     __disable_interrupt();
_ZN10led_driver3runEi:
        CPSID    I
//  222     
//  223     // не запускаем драйвер если не 
//  224     // отработаны повторы с предыдущей команды запуска.
//  225     if (_num_of_rptions < 0)
        LDR      R2,[R0, #+20]
        CMP      R2,#+0
        BPL.N    ??run_1
//  226     {
//  227         _num_of_rptions = repetitions;
        STR      R1,[R0, #+20]
//  228     
//  229         _run = true;
        MOVS     R2,#+1
        STRB     R2,[R0, #+16]
//  230     }
//  231     
//  232     __enable_interrupt();
??run_1:
        CPSIE    I
//  233 }
        BX       LR               ;; return
          CFI EndBlock cfiBlock11
//  234 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function _ZN10led_driver6run_upEv
        THUMB
//  235 void led_driver::run_up(void)
//  236 { 
_ZN10led_driver6run_upEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  237     __disable_interrupt();
        CPSID    I
//  238   
//  239     // если не требуется завершения предыдущей команды
//  240     if (!_need_finish())
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver12_need_finishEv
        BL       _ZN10led_driver12_need_finishEv
        CMP      R0,#+0
        BNE.N    ??run_up_0
//  241     { 
//  242         if(_bright_val < _max_val)    
        LDR      R0,[R4, #+48]
        LDRH     R1,[R4, #+36]
        CMP      R0,R1
        BGE.N    ??run_up_0
//  243         _run_up = true;
        MOVS     R0,#+1
        STRB     R0,[R4, #+17]
//  244     }
//  245     
//  246     __enable_interrupt();
??run_up_0:
        CPSIE    I
//  247 } 
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock12
//  248 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function _ZN10led_driver8run_downEv
        THUMB
//  249 void led_driver::run_down(void)
//  250 { 
_ZN10led_driver8run_downEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  251     __disable_interrupt();
        CPSID    I
//  252     
//  253     // если не требуется завершения предыдущей команды
//  254     if (!_need_finish())
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver12_need_finishEv
        BL       _ZN10led_driver12_need_finishEv
        CMP      R0,#+0
        BNE.N    ??run_down_0
//  255     { 
//  256         // Закомментил: уменьшаем с текущего значения яркости
//  257         //_bright_val = _max_val;
//  258       if(_bright_val > 0)
        LDR      R0,[R4, #+48]
        CMP      R0,#+1
        BLT.N    ??run_down_0
//  259         _run_down = true;
        MOVS     R0,#+1
        STRB     R0,[R4, #+18]
//  260     }
//  261     
//  262     __enable_interrupt();
??run_down_0:
        CPSIE    I
//  263 } 
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock13
//  264 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock14 Using cfiCommon0
          CFI Function _ZN10led_driver5_stopEv
        THUMB
//  265 void led_driver::_stop(void)   
//  266 {  
_ZN10led_driver5_stopEv:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
//  267     _num_of_rptions = -1;
        MOVS     R0,#-1
        STR      R0,[R4, #+20]
//  268 
//  269     _run        = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+16]
//  270     _run_up     = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+17]
//  271     _run_down   = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+18]
//  272 
//  273     _timer   = pTimer->get_ms() - _tout;
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R4, #+32]
        MOVS     R3,#+0
        SUBS     R0,R0,R2
        SBCS     R1,R1,R3
        STRD     R0,R1,[R4, #+24]
//  274 
//  275     _bright_val     = 0;
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//  276     _fade_dir = true;
        MOVS     R0,#+1
        STRB     R0,[R4, #+45]
//  277     
//  278 }
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock14
//  279 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock15 Using cfiCommon0
          CFI Function _ZN10led_driver6handleEv
        THUMB
//  280 bool led_driver::handle(void) 
//  281 {  
_ZN10led_driver6handleEv:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
//  282      bool result = false;
        MOVS     R5,#+0
//  283 
//  284     if(_fade())
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver5_fadeEv
        BL       _ZN10led_driver5_fadeEv
        CMP      R0,#+0
        BEQ.N    ??handle_0
//  285         result = true;
        MOVS     R0,#+1
        MOVS     R5,R0
//  286     if(_fade_up())
??handle_0:
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver8_fade_upEv
        BL       _ZN10led_driver8_fade_upEv
        CMP      R0,#+0
        BEQ.N    ??handle_1
//  287         result = true;
        MOVS     R0,#+1
        MOVS     R5,R0
//  288     if(_fade_down())
??handle_1:
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver10_fade_downEv
        BL       _ZN10led_driver10_fade_downEv
        CMP      R0,#+0
        BEQ.N    ??handle_2
//  289         result = true;
        MOVS     R0,#+1
        MOVS     R5,R0
//  290 
//  291     return result;
??handle_2:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R1,R4,R5,PC}    ;; return
//  292 }
          CFI EndBlock cfiBlock15
//  293 
//  294 // размещается в прерывании.

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock16 Using cfiCommon0
          CFI Function _ZN10led_driver5_fadeEv
        THUMB
//  295 bool led_driver::_fade(void)   
//  296 {   
_ZN10led_driver5_fadeEv:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R4,R0
//  297     bool result = false;
        MOVS     R5,#+0
//  298 
//  299     if(_run)
        LDRB     R0,[R4, #+16]
        CMP      R0,#+0
        BEQ.N    ??_fade_0
//  300     {
//  301         result = true;
        MOVS     R0,#+1
        MOVS     R5,R0
//  302 
//  303         if (pTimer->get_ms() - _timer > (uint64_t)_tout)
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R4, #+32]
        MOVS     R3,#+0
        LDRD     R6,R7,[R4, #+24]
        SUBS     R0,R0,R6
        SBCS     R1,R1,R7
        CMP      R3,R1
        BHI.N    ??_fade_0
        BCC.N    ??_fade_1
        CMP      R2,R0
        BCS.N    ??_fade_0
//  304         {
//  305              if(_fade_dir)
??_fade_1:
        LDRB     R0,[R4, #+45]
        CMP      R0,#+0
        BEQ.N    ??_fade_2
//  306              {
//  307                  _bright_val += (int)_step;
        LDR      R0,[R4, #+48]
        LDRB     R1,[R4, #+38]
        ADDS     R0,R0,R1
        STR      R0,[R4, #+48]
//  308                  if(_bright_val < (int)_max_val )
        LDR      R0,[R4, #+48]
        LDRH     R1,[R4, #+36]
        CMP      R0,R1
        BGE.N    ??_fade_3
//  309                  { write_chnl(_led,_bright_val); }
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??_fade_4
//  310                  else
//  311                  { 
//  312                      _bright_val = (int)_max_val;
??_fade_3:
        LDRH     R0,[R4, #+36]
        STR      R0,[R4, #+48]
//  313                      write_chnl(_led,_bright_val);
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  314                      _fade_dir = !_fade_dir;
        LDRB     R0,[R4, #+45]
        CMP      R0,#+0
        BNE.N    ??_fade_5
        MOVS     R0,#+1
        B.N      ??_fade_6
??_fade_5:
        MOVS     R0,#+0
??_fade_6:
        STRB     R0,[R4, #+45]
        B.N      ??_fade_4
//  315                  }
//  316              }
//  317              else
//  318              { 
//  319                  _bright_val -= (int)_step;
??_fade_2:
        LDR      R1,[R4, #+48]
        LDRB     R0,[R4, #+38]
        SUBS     R1,R1,R0
        STR      R1,[R4, #+48]
//  320                  if(_bright_val > 0 )
        LDR      R0,[R4, #+48]
        CMP      R0,#+1
        BLT.N    ??_fade_7
//  321                  { write_chnl(_led,_bright_val); }
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??_fade_4
//  322                  else
//  323                  { 
//  324                      _bright_val = 0;
??_fade_7:
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//  325                      write_chnl(_led,_bright_val);
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  326                      _fade_dir = !_fade_dir;
        LDRB     R0,[R4, #+45]
        CMP      R0,#+0
        BNE.N    ??_fade_8
        MOVS     R0,#+1
        B.N      ??_fade_9
??_fade_8:
        MOVS     R0,#+0
??_fade_9:
        STRB     R0,[R4, #+45]
//  327   
//  328                      if(--_num_of_rptions == 0)
        LDR      R0,[R4, #+20]
        SUBS     R0,R0,#+1
        STR      R0,[R4, #+20]
        LDR      R0,[R4, #+20]
        CMP      R0,#+0
        BNE.N    ??_fade_4
//  329                      {   
//  330                         _stop();
        MOVS     R0,R4
          CFI FunCall _ZN10led_driver5_stopEv
        BL       _ZN10led_driver5_stopEv
//  331   
//  332                         return result;
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        B.N      ??_fade_10
//  333                      }
//  334                  }
//  335              }
//  336              
//  337              _timer = pTimer->get_ms();
??_fade_4:
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        STRD     R0,R1,[R4, #+24]
//  338         }
//  339     }
//  340 
//  341     return result;
??_fade_0:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
??_fade_10:
        POP      {R1,R4-R7,PC}    ;; return
//  342 }  
          CFI EndBlock cfiBlock16
//  343 
//  344 // размещается в прерывании.

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock17 Using cfiCommon0
          CFI Function _ZN10led_driver8_fade_upEv
        THUMB
//  345 bool led_driver::_fade_up(void)   
//  346 {   
_ZN10led_driver8_fade_upEv:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R4,R0
//  347     bool result = false;
        MOVS     R5,#+0
//  348 
//  349     if(_run_up)
        LDRB     R0,[R4, #+17]
        CMP      R0,#+0
        BEQ.N    ??_fade_up_0
//  350     {
//  351         result = true;
        MOVS     R0,#+1
        MOVS     R5,R0
//  352 
//  353         if (pTimer->get_ms() - _timer > (uint64_t)_tout)
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R4, #+32]
        MOVS     R3,#+0
        LDRD     R6,R7,[R4, #+24]
        SUBS     R0,R0,R6
        SBCS     R1,R1,R7
        CMP      R3,R1
        BHI.N    ??_fade_up_0
        BCC.N    ??_fade_up_1
        CMP      R2,R0
        BCS.N    ??_fade_up_0
//  354         {
//  355             _bright_val += (int)_step;
??_fade_up_1:
        LDR      R0,[R4, #+48]
        LDRB     R1,[R4, #+38]
        ADDS     R0,R0,R1
        STR      R0,[R4, #+48]
//  356 
//  357             if(_bright_val < (int)_max_val )
        LDR      R0,[R4, #+48]
        LDRH     R1,[R4, #+36]
        CMP      R0,R1
        BGE.N    ??_fade_up_2
//  358             { write_chnl(_led,_bright_val); }
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??_fade_up_3
//  359             else
//  360             { 
//  361                 _bright_val = (int)_max_val;
??_fade_up_2:
        LDRH     R0,[R4, #+36]
        STR      R0,[R4, #+48]
//  362                 write_chnl(_led,_bright_val);
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  363 
//  364                 _run_up = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+17]
//  365             }
//  366 
//  367             if(_run_up == false)
??_fade_up_3:
        LDRB     R0,[R4, #+17]
        CMP      R0,#+0
        BNE.N    ??_fade_up_4
//  368             { _timer   = pTimer->get_ms() - (uint64_t)_tout; }
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R4, #+32]
        MOVS     R3,#+0
        SUBS     R0,R0,R2
        SBCS     R1,R1,R3
        STRD     R0,R1,[R4, #+24]
        B.N      ??_fade_up_0
//  369             else
//  370             { _timer   = pTimer->get_ms(); }            
??_fade_up_4:
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        STRD     R0,R1,[R4, #+24]
//  371         }
//  372     }
//  373 
//  374     return result;
??_fade_up_0:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R1,R4-R7,PC}    ;; return
//  375 } 
          CFI EndBlock cfiBlock17
//  376 
//  377 // размещается в прерывании.

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock18 Using cfiCommon0
          CFI Function _ZN10led_driver10_fade_downEv
        THUMB
//  378 bool led_driver::_fade_down(void)   
//  379 {   
_ZN10led_driver10_fade_downEv:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R4,R0
//  380     bool result = false;
        MOVS     R5,#+0
//  381 
//  382     if(_run_down)
        LDRB     R0,[R4, #+18]
        CMP      R0,#+0
        BEQ.N    ??_fade_down_0
//  383     {
//  384         result = true;
        MOVS     R0,#+1
        MOVS     R5,R0
//  385 
//  386         if (pTimer->get_ms() - _timer > (uint64_t)_tout)
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R4, #+32]
        MOVS     R3,#+0
        LDRD     R6,R7,[R4, #+24]
        SUBS     R0,R0,R6
        SBCS     R1,R1,R7
        CMP      R3,R1
        BHI.N    ??_fade_down_0
        BCC.N    ??_fade_down_1
        CMP      R2,R0
        BCS.N    ??_fade_down_0
//  387         {
//  388             _bright_val -= (int)_step;
??_fade_down_1:
        LDR      R1,[R4, #+48]
        LDRB     R0,[R4, #+38]
        SUBS     R1,R1,R0
        STR      R1,[R4, #+48]
//  389 
//  390             if(_bright_val > 0 )
        LDR      R0,[R4, #+48]
        CMP      R0,#+1
        BLT.N    ??_fade_down_2
//  391             { write_chnl(_led,_bright_val); }
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??_fade_down_3
//  392             else
//  393             { 
//  394                 _bright_val = 0;
??_fade_down_2:
        MOVS     R0,#+0
        STR      R0,[R4, #+48]
//  395 
//  396                 write_chnl(_led,_bright_val); 
        MOVS     R3,#+0
        LDR      R2,[R4, #+48]
        LDRB     R1,[R4, #+44]
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  397 
//  398                 _run_down = false;
        MOVS     R0,#+0
        STRB     R0,[R4, #+18]
//  399             }
//  400              
//  401             if(_run_down == false)
??_fade_down_3:
        LDRB     R0,[R4, #+18]
        CMP      R0,#+0
        BNE.N    ??_fade_down_4
//  402             { _timer   = pTimer->get_ms() - (uint64_t)_tout; }
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        LDR      R2,[R4, #+32]
        MOVS     R3,#+0
        SUBS     R0,R0,R2
        SBCS     R1,R1,R3
        STRD     R0,R1,[R4, #+24]
        B.N      ??_fade_down_0
//  403             else
//  404             { _timer   = pTimer->get_ms(); } 
??_fade_down_4:
        LDR      R0,[R4, #+12]
          CFI FunCall _ZNK5Timer6get_msEv
        BL       _ZNK5Timer6get_msEv
        STRD     R0,R1,[R4, #+24]
//  405         }
//  406     }
//  407 
//  408     return result;
??_fade_down_0:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R1,R4-R7,PC}    ;; return
//  409 } 
          CFI EndBlock cfiBlock18
//  410 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock19 Using cfiCommon0
          CFI Function _ZN10led_driver12_need_finishEv
          CFI NoCalls
        THUMB
//  411 bool led_driver::_need_finish(void)
//  412 {
_ZN10led_driver12_need_finishEv:
        MOVS     R1,R0
//  413     if ( _num_of_rptions > 1)
        LDR      R0,[R1, #+20]
        CMP      R0,#+2
        BLT.N    ??_need_finish_0
//  414     { 
//  415         // драйвер запущен на несколько повторений или
//  416         // на бесконечное количество делаем это последним
//  417         _num_of_rptions = 1;
        MOVS     R0,#+1
        STR      R0,[R1, #+20]
//  418         return true;
        MOVS     R0,#+1
        B.N      ??_need_finish_1
//  419     } 
//  420     else
//  421     if ( _run_up || _run_down )
??_need_finish_0:
        LDRB     R0,[R1, #+17]
        CMP      R0,#+0
        BNE.N    ??_need_finish_2
        LDRB     R0,[R1, #+18]
        CMP      R0,#+0
        BEQ.N    ??_need_finish_3
//  422     {   
//  423         // даем завершиться восходящему или нисходящему градиенту
//  424         return true; 
??_need_finish_2:
        MOVS     R0,#+1
        B.N      ??_need_finish_1
//  425     }
//  426     else
//  427     if (_run &&( _num_of_rptions < 0))
??_need_finish_3:
        LDRB     R0,[R1, #+16]
        CMP      R0,#+0
        BEQ.N    ??_need_finish_4
        LDR      R0,[R1, #+20]
        CMP      R0,#+0
        BPL.N    ??_need_finish_4
//  428     {
//  429         // выключаем только по отдельному запуску turn_off() в цикле если запущен
//  430         // на бесконечный повтор
//  431         //turn_off();
//  432         return true;
        MOVS     R0,#+1
        B.N      ??_need_finish_1
//  433     }
//  434     else
//  435     { 
//  436         return false;
??_need_finish_4:
        MOVS     R0,#+0
??_need_finish_1:
        BX       LR               ;; return
//  437     }  
//  438 }
          CFI EndBlock cfiBlock19
//  439 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock20 Using cfiCommon0
          CFI Function _Z18led_drivers_handlev
        THUMB
//  440 uint8_t led_drivers_handle(void)
//  441 {
_Z18led_drivers_handlev:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
//  442     bool busy = false;
        MOVS     R4,#+0
//  443     uint8_t  result = 0;
        MOVS     R5,#+0
//  444     
//  445    //обработка драйверов светодиодов
//  446    for ( uint32_t i = 0; i < LEDS_NUM; i++)
        MOVS     R6,#+0
??led_drivers_handle_0:
        CMP      R6,#+8
        BCS.N    ??led_drivers_handle_1
//  447    { 
//  448       if(led_list[i] != NULL)
        LDR.N    R1,??DataTable2_8
        LDR      R0,[R1, R6, LSL #+2]
        CMP      R0,#+0
        BEQ.N    ??led_drivers_handle_2
//  449       { busy = led_list[i]->handle(); } 
        LDR      R0,[R1, R6, LSL #+2]
          CFI FunCall _ZN10led_driver6handleEv
        BL       _ZN10led_driver6handleEv
        MOVS     R4,R0
//  450        
//  451       // защелкиваем защелку       
//  452       if(busy)
??led_drivers_handle_2:
        MOVS     R0,R4
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??led_drivers_handle_3
//  453       { 
//  454           busy = false;
        MOVS     R0,#+0
        MOVS     R4,R0
//  455           result++;
        ADDS     R5,R5,#+1
//  456       }
//  457    }
??led_drivers_handle_3:
        ADDS     R6,R6,#+1
        B.N      ??led_drivers_handle_0
//  458 
//  459    // флажок нужен для того чтобы показать 
//  460    // сколько светодиодов сейчас обрабатываеться
//  461    return result;
??led_drivers_handle_1:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        POP      {R4-R6,PC}       ;; return
//  462 }
          CFI EndBlock cfiBlock20

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2:
        DATA32
        DC32     led_2_port_list

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_1:
        DATA32
        DC32     sys_timer

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_2:
        DATA32
        DC32     charge_bar

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_3:
        DATA32
        DC32     red_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_4:
        DATA32
        DC32     green_led

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
        DC32     btn_pr_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_7:
        DATA32
        DC32     kb_led

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable2_8:
        DATA32
        DC32     led_list

        SECTION `.text`:CODE:REORDER:NOROOT(1)
        SECTION_GROUP _Z3nodIiET_S0_S0_
          CFI Block cfiBlock21 Using cfiCommon0
          CFI Function _Z3nodIiET_S0_S0_
          CFI NoCalls
        THUMB
// __interwork __softfp int nod<int>(int, int)
_Z3nodIiET_S0_S0_:
??nod_0:
        CMP      R0,R1
        BEQ.N    ??nod_1
        CMP      R1,R0
        BGE.N    ??nod_2
        SUBS     R0,R0,R1
        B.N      ??nod_0
??nod_2:
        SUBS     R1,R1,R0
        B.N      ??nod_0
??nod_1:
        BX       LR               ;; return
          CFI EndBlock cfiBlock21

        SECTION `.init_array`:CODE:ROOT(2)
        SECTION_TYPE SHT_INIT_ARRAY, 0
        DATA
        DC32    RELOC_ARM_TARGET1 __sti__routine

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//  463 
// 
//   336 bytes in section .bss
//    64 bytes in section .data
//     4 bytes in section .init_array
// 1'586 bytes in section .text
// 
// 1'572 bytes of CODE memory (+ 18 bytes shared)
//   400 bytes of DATA memory
//
//Errors: none
//Warnings: none
