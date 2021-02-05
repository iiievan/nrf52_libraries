///////////////////////////////////////////////////////////////////////////////
//
// IAR ANSI C/C++ Compiler V8.40.1.212/W32 for ARM        05/Feb/2021  12:20:14
// Copyright 1999-2019 IAR Systems AB.
//
//    Cpu mode     =  
//    Endian       =  little
//    Source file  =  E:\cpp\nrf52_libraries\pwm\nrf_hw_pwm.cpp
//    Command line =
//        -f C:\Users\IF385~1.SHO\AppData\Local\Temp\EWB7A2.tmp
//        (E:\cpp\nrf52_libraries\pwm\nrf_hw_pwm.cpp -D NRF52840_XXAA -D
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
//    List file    =  E:\cpp\nrf52_libraries\main\List\nrf_hw_pwm.s
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

        EXTERN __aeabi_memset
        EXTERN led_2_port_list

        PUBLIC _ZN10nrf_hw_pwm10_pin_2_ledEj
        PUBLIC _ZN10nrf_hw_pwm10remove_pinEh
        PUBLIC _ZN10nrf_hw_pwm10write_chnlEhjb
        PUBLIC _ZN10nrf_hw_pwm11_is_enabledEh
        PUBLIC _ZN10nrf_hw_pwm11get_channelEj
        PUBLIC _ZN10nrf_hw_pwm11get_led_numEj
        PUBLIC _ZN10nrf_hw_pwm11get_pwm_numEj
        PUBLIC _ZN10nrf_hw_pwm12set_chrg_barEs
        PUBLIC _ZN10nrf_hw_pwm13_run_sequenceEh
        PUBLIC _ZN10nrf_hw_pwm13set_clock_divEh
        PUBLIC _ZN10nrf_hw_pwm13set_max_valueEhj
        PUBLIC _ZN10nrf_hw_pwm14_led_2_channelEh
        PUBLIC _ZN10nrf_hw_pwm19_old_chrg_bar_stateE
        PUBLIC _ZN10nrf_hw_pwm19_pin_allocation_mapE
        PUBLIC _ZN10nrf_hw_pwm4stopEh
        PUBLIC _ZN10nrf_hw_pwm5startEh
        PUBLIC _ZN10nrf_hw_pwm6_seq_0E
        PUBLIC _ZN10nrf_hw_pwm6_setupEh
        PUBLIC _ZN10nrf_hw_pwm7add_pinEj
        PUBLIC _ZN10nrf_hw_pwm8_pwm_devE
        PUBLIC _ZN10nrf_hw_pwm8read_pinEj
        PUBLIC _ZN10nrf_hw_pwm9read_chnlEh
        PUBLIC _ZN10nrf_hw_pwmC1Et
        PUBLIC _ZN10nrf_hw_pwmC1Etjjj
        PUBLIC _ZN10nrf_hw_pwmC1Ev
        PUBLIC _ZN10nrf_hw_pwmC2Et
        PUBLIC _ZN10nrf_hw_pwmC2Etjjj
        PUBLIC _ZN10nrf_hw_pwmC2Ev
        
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
        
// E:\cpp\nrf52_libraries\pwm\nrf_hw_pwm.cpp
//    1 #include "nrf_hw_pwm.h"
//    2 

        SECTION `.data`:DATA:REORDER:NOROOT(2)
        DATA
//    3 NRF_PWM_Type* nrf_hw_pwm::_pwm_dev[] =
_ZN10nrf_hw_pwm8_pwm_devE:
        DATA32
        DC32 0x4001'c000, 0x4002'1000, 0x4002'2000, 0x4002'd000
//    4 {
//    5     NRF_PWM0,
//    6     NRF_PWM1,
//    7     NRF_PWM2,
//    8     NRF_PWM3
//    9 };
//   10 

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   11 uint16_t  nrf_hw_pwm::_seq_0[HWPWM_MODULE_NUM][MAX_CHANNELS]      = {0};
_ZN10nrf_hw_pwm6_seq_0E:
        DS8 32

        SECTION `.bss`:DATA:REORDER:NOROOT(2)
        DATA
//   12  int16_t  nrf_hw_pwm::_pin_allocation_map[LEDS_NUM][INFO_MAP_NUM] = {0};  // карта соответствия led pin chnl pwm
_ZN10nrf_hw_pwm19_pin_allocation_mapE:
        DS8 48

        SECTION `.data`:DATA:REORDER:NOROOT(1)
        DATA
//   13  int16_t  nrf_hw_pwm::_old_chrg_bar_state                         = SHTDWN;
_ZN10nrf_hw_pwm19_old_chrg_bar_stateE:
        DATA16
        DC16 -1
//   14 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock0 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwmC2Ev
        THUMB
// __code __interwork __softfp nrf_hw_pwm::subobject nrf_hw_pwm()
_ZN10nrf_hw_pwmC2Ev:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwmC1Ev
        BL       _ZN10nrf_hw_pwmC1Ev
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock0

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock1 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwmC2Et
        THUMB
// __code __interwork __softfp nrf_hw_pwm::subobject nrf_hw_pwm(uint16_t)
_ZN10nrf_hw_pwmC2Et:
        PUSH     {R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R4,R0
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwmC1Et
        BL       _ZN10nrf_hw_pwmC1Et
        POP      {R4,PC}          ;; return
          CFI EndBlock cfiBlock1

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock2 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwmC2Etjjj
        THUMB
// __code __interwork __softfp nrf_hw_pwm::subobject nrf_hw_pwm(uint16_t, uint32_t, uint32_t, uint32_t)
_ZN10nrf_hw_pwmC2Etjjj:
        PUSH     {R2-R4,LR}
          CFI R14 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+16
        MOVS     R4,R0
        LDR      R0,[SP, #+16]
        STR      R0,[SP, #+0]
        UXTH     R1,R1            ;; ZeroExt  R1,R1,#+16,#+16
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwmC1Etjjj
        BL       _ZN10nrf_hw_pwmC1Etjjj
        POP      {R1,R2,R4,PC}    ;; return
          CFI EndBlock cfiBlock2

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock3 Using cfiCommon0
          CFI Function _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef524nrf_gpio_pin_port_decodeEPj
          CFI NoCalls
        THUMB
// static __interwork __softfp NRF_GPIO_Type *nrf_gpio_pin_port_decode(uint32_t *)
_ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef524nrf_gpio_pin_port_decodeEPj:
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
        LDR.W    R0,??DataTable17  ;; 0x50000300
??nrf_gpio_pin_port_decode_1:
        BX       LR               ;; return
          CFI EndBlock cfiBlock3

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock4 Using cfiCommon0
          CFI Function _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef512nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        THUMB
// static __interwork __softfp void nrf_gpio_cfg(uint32_t, nrf_gpio_pin_dir_t, nrf_gpio_pin_input_t, nrf_gpio_pin_pull_t, nrf_gpio_pin_drive_t, nrf_gpio_pin_sense_t)
_ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef512nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t:
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
          CFI FunCall _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef524nrf_gpio_pin_port_decodeEPj
        BL       _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef524nrf_gpio_pin_port_decodeEPj
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
          CFI EndBlock cfiBlock4

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock5 Using cfiCommon0
          CFI Function _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef519nrf_gpio_cfg_outputEj
        THUMB
// static __interwork __softfp void nrf_gpio_cfg_output(uint32_t)
_ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef519nrf_gpio_cfg_outputEj:
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
          CFI FunCall _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef512nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        BL       _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef512nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        POP      {R0,R1,R4,PC}    ;; return
          CFI EndBlock cfiBlock5

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock6 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwmC1Ev
          CFI NoCalls
        THUMB
//   15 nrf_hw_pwm::nrf_hw_pwm()
//   16 {     
//   17     // конструктор по умолчанию пустой, но он нужен
//   18     // потому что сюда заходит каждый раз при создании объекта led_driver
//   19 }
_ZN10nrf_hw_pwmC1Ev:
        BX       LR               ;; return
          CFI EndBlock cfiBlock6
//   20 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock7 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwmC1Et
        THUMB
//   21 nrf_hw_pwm::nrf_hw_pwm(uint16_t clock_div)
//   22 {       
_ZN10nrf_hw_pwmC1Et:
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
//   23     // инициализируем таблицу соответствия каналов
//   24     for (uint8_t k = 0; k < LEDS_NUM; k++)
        MOVS     R0,#+0
??nrf_hw_pwm_0:
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+8
        BGE.N    ??nrf_hw_pwm_1
//   25     {
//   26         _pin_allocation_map[k][PIN_NUM] = REMOVED;   // пин отсутствует
        MOVS     R1,#+6
        LDR.W    R2,??DataTable17_1
        MVNS     R3,#+2
        MOVS     R6,R0
        UXTB     R6,R6            ;; ZeroExt  R6,R6,#+24,#+24
        MULS     R6,R1,R6
        STRH     R3,[R2, R6]
//   27         _pin_allocation_map[k][CHN_NUM] = CHNL_NA;   // канала нет
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MULS     R3,R1,R3
        ADD      R3,R2,R3
        MVNS     R6,#+1
        STRH     R6,[R3, #+2]
//   28         _pin_allocation_map[k][PWM_NUM] = STATE_NA;  // номер модуля PWM неизвестен
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MUL      R1,R1,R3
        ADD      R1,R2,R1
        MOVS     R2,#-1
        STRH     R2,[R1, #+4]
//   29     }  
        ADDS     R0,R0,#+1
        B.N      ??nrf_hw_pwm_0
//   30     
//   31     // обнуляем таблицу значений PWM
//   32     memset(_seq_0, 0, MAX_CHANNELS);
??nrf_hw_pwm_1:
        MOVS     R7,#+4
        MOVS     R8,#+0
        LDR.W    R6,??DataTable17_2
        MOV      R2,R8
        MOVS     R1,R7
        MOVS     R0,R6
          CFI FunCall __aeabi_memset
        BL       __aeabi_memset
//   33     set_clock_div(clock_div);    
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm13set_clock_divEh
        BL       _ZN10nrf_hw_pwm13set_clock_divEh
//   34 
//   35     for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
        MOVS     R6,#+0
??nrf_hw_pwm_2:
        MOVS     R0,R6
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+4
        BGE.N    ??nrf_hw_pwm_3
//   36     {
//   37         set_max_value(pwm, (uint32_t)MAX_PWM_VALUE);
        MOVS     R2,#+255
        MOVS     R1,R6
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm13set_max_valueEhj
        BL       _ZN10nrf_hw_pwm13set_max_valueEhj
//   38         _setup(pwm);
        MOVS     R1,R6
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm6_setupEh
        BL       _ZN10nrf_hw_pwm6_setupEh
//   39     }
        ADDS     R6,R6,#+1
        B.N      ??nrf_hw_pwm_2
//   40 
//   41     // в данной конфигурации модуля чарджбара нет.
//   42     _chctrl_1 = REMOVED;
??nrf_hw_pwm_3:
        MVNS     R0,#+2
        STRH     R0,[R4, #+4]
//   43     _chctrl_2 = REMOVED;
        STRH     R0,[R4, #+6]
//   44     _chctrl_3 = REMOVED;
        STRH     R0,[R4, #+8]
//   45 }
        MOVS     R0,R4
        POP      {R4-R8,PC}       ;; return
          CFI EndBlock cfiBlock7
//   46 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock8 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwmC1Etjjj
        THUMB
//   47 nrf_hw_pwm::nrf_hw_pwm(uint16_t clock_div, uint32_t pin_1, uint32_t pin_2, uint32_t pin_3)
//   48 {       
_ZN10nrf_hw_pwmC1Etjjj:
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
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R7,R3
        LDR      R8,[SP, #+40]
//   49     // инициализируем таблицу соответствия каналов
//   50     for (uint8_t k = 0; k < LEDS_NUM; k++)
        MOVS     R0,#+0
??nrf_hw_pwm_4:
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+8
        BGE.N    ??nrf_hw_pwm_5
//   51     {
//   52         _pin_allocation_map[k][PIN_NUM] = REMOVED;   // пин отсутствует
        MOVS     R1,#+6
        LDR.W    R2,??DataTable17_1
        MVNS     R3,#+2
        MOV      R12,R0
        UXTB     R12,R12          ;; ZeroExt  R12,R12,#+24,#+24
        MUL      R12,R1,R12
        STRH     R3,[R2, R12]
//   53         _pin_allocation_map[k][CHN_NUM] = CHNL_NA;   // канала нет
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MULS     R3,R1,R3
        ADD      R3,R2,R3
        MVNS     R12,#+1
        STRH     R12,[R3, #+2]
//   54         _pin_allocation_map[k][PWM_NUM] = STATE_NA;  // номер модуля PWM неизвестен
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MUL      R1,R1,R3
        ADD      R1,R2,R1
        MOVS     R2,#-1
        STRH     R2,[R1, #+4]
//   55     }  
        ADDS     R0,R0,#+1
        B.N      ??nrf_hw_pwm_4
//   56     
//   57     // обнуляем таблицу значений PWM
//   58     memset(_seq_0, 0, MAX_CHANNELS);
??nrf_hw_pwm_5:
        MOVS     R9,#+4
        MOVS     R10,#+0
        LDR.W    R11,??DataTable17_2
        MOV      R2,R10
        MOV      R1,R9
        MOV      R0,R11
          CFI FunCall __aeabi_memset
        BL       __aeabi_memset
//   59     set_clock_div(clock_div);    
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm13set_clock_divEh
        BL       _ZN10nrf_hw_pwm13set_clock_divEh
//   60 
//   61     for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
        MOVS     R11,#+0
??nrf_hw_pwm_6:
        MOV      R0,R11
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+4
        BGE.N    ??nrf_hw_pwm_7
//   62     {
//   63         set_max_value(pwm, (uint32_t)MAX_PWM_VALUE);
        MOVS     R2,#+255
        MOV      R1,R11
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm13set_max_valueEhj
        BL       _ZN10nrf_hw_pwm13set_max_valueEhj
//   64         _setup(pwm);
        MOV      R1,R11
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm6_setupEh
        BL       _ZN10nrf_hw_pwm6_setupEh
//   65     }
        ADDS     R11,R11,#+1
        B.N      ??nrf_hw_pwm_6
//   66 
//   67     // Добавляем пины и светодиоды для модуля управляения чардж баром.
//   68     add_pin(pin_1);
??nrf_hw_pwm_7:
        MOVS     R1,R6
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm7add_pinEj
        BL       _ZN10nrf_hw_pwm7add_pinEj
//   69     add_pin(pin_2);
        MOVS     R1,R7
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm7add_pinEj
        BL       _ZN10nrf_hw_pwm7add_pinEj
//   70     add_pin(pin_3);
        MOV      R1,R8
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm7add_pinEj
        BL       _ZN10nrf_hw_pwm7add_pinEj
//   71 
//   72     _chctrl_1 = _pin_2_led(pin_1);
        MOVS     R1,R6
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[R4, #+4]
//   73     _chctrl_2 = _pin_2_led(pin_2);
        MOVS     R1,R7
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[R4, #+6]
//   74     _chctrl_3 = _pin_2_led(pin_3);
        MOV      R1,R8
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[R4, #+8]
//   75 }
        MOVS     R0,R4
        POP      {R1,R4-R11,PC}   ;; return
          CFI EndBlock cfiBlock8
//   76 
//   77 // оставлю на всякий случай на будущее, но в целом оперировать uint8_t разрядностью удобно
//   78 // при задании ШИМ.

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock9 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm13set_max_valueEhj
          CFI NoCalls
        THUMB
//   79 void nrf_hw_pwm::set_max_value(uint8_t pwm_index, uint32_t value)
//   80 {
_ZN10nrf_hw_pwm13set_max_valueEhj:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
//   81     _max_value = value;
        STRH     R2,[R0, #+0]
//   82 
//   83     _pwm_dev[pwm_index]->COUNTERTOP = value;
        LDR.W    R3,??DataTable17_3
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R3,[R3, R4, LSL #+2]
        STR      R2,[R3, #+1288]
//   84 }
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock9
//   85 
//   86 
//   87 // 1:2:4:8:16:32:64:128

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock10 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm13set_clock_divEh
          CFI NoCalls
        THUMB
//   88 void nrf_hw_pwm::set_clock_div(uint8_t div )
//   89 {
//   90     switch (div) {
_ZN10nrf_hw_pwm13set_clock_divEh:
        MOVS     R2,R1
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+1
        BEQ.N    ??set_clock_div_0
        CMP      R2,#+2
        BEQ.N    ??set_clock_div_1
        CMP      R2,#+4
        BEQ.N    ??set_clock_div_2
        CMP      R2,#+8
        BEQ.N    ??set_clock_div_3
        CMP      R2,#+16
        BEQ.N    ??set_clock_div_4
        CMP      R2,#+32
        BEQ.N    ??set_clock_div_5
        CMP      R2,#+64
        BEQ.N    ??set_clock_div_6
        CMP      R2,#+128
        BEQ.N    ??set_clock_div_7
        B.N      ??set_clock_div_8
//   91         case 1:
//   92             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_1;
??set_clock_div_0:
        MOVS     R2,#+0
        STRB     R2,[R0, #+2]
//   93             break;
        B.N      ??set_clock_div_9
//   94         case 2:
//   95             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_2;
??set_clock_div_1:
        MOVS     R2,#+1
        STRB     R2,[R0, #+2]
//   96             break;
        B.N      ??set_clock_div_9
//   97         case 4:
//   98             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_4;
??set_clock_div_2:
        MOVS     R2,#+2
        STRB     R2,[R0, #+2]
//   99             break;
        B.N      ??set_clock_div_9
//  100         case 8:
//  101             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_8;
??set_clock_div_3:
        MOVS     R2,#+3
        STRB     R2,[R0, #+2]
//  102             break;
        B.N      ??set_clock_div_9
//  103         case 16:
//  104             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_16;
??set_clock_div_4:
        MOVS     R2,#+4
        STRB     R2,[R0, #+2]
//  105             break;
        B.N      ??set_clock_div_9
//  106         case 32:
//  107             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_32;
??set_clock_div_5:
        MOVS     R2,#+5
        STRB     R2,[R0, #+2]
//  108             break;
        B.N      ??set_clock_div_9
//  109         case 64:
//  110             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_64;
??set_clock_div_6:
        MOVS     R2,#+6
        STRB     R2,[R0, #+2]
//  111             break;
        B.N      ??set_clock_div_9
//  112         case 128:
//  113             _clock_div = (uint8_t)PWM_PRESCALER_PRESCALER_DIV_128;
??set_clock_div_7:
        MOVS     R2,#+7
        STRB     R2,[R0, #+2]
//  114             break;
        B.N      ??set_clock_div_9
//  115         default:
//  116             // по умолчанию ставим 16МГц
//  117             _clock_div = PWM_PRESCALER_PRESCALER_DIV_1;
??set_clock_div_8:
        MOVS     R2,#+0
        STRB     R2,[R0, #+2]
//  118     }
//  119 }
??set_clock_div_9:
        BX       LR               ;; return
          CFI EndBlock cfiBlock10
//  120 
//  121 /**
//  122  * Add pin to this group.
//  123  * @param pin Pin to add
//  124  * @return true if add succeeded, or pin is already added
//  125  */

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock11 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm7add_pinEj
        THUMB
//  126 int8_t nrf_hw_pwm::add_pin(uint32_t pin)
//  127 {
_ZN10nrf_hw_pwm7add_pinEj:
        PUSH     {R1-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+32
        MOVS     R4,R0
        MOVS     R5,R1
//  128     volatile      int        ch = CHNL_NA;
        MVNS     R0,#+1
        STR      R0,[SP, #+4]
//  129     volatile  int16_t       led = _pin_2_led(pin);
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[SP, #+0]
//  130                int8_t pwm_index = STATE_NA;
        MOVS     R6,#-1
//  131 
//  132     if(led != REMOVED)
        LDRSH    R0,[SP, #+0]
        CMN      R0,#+3
        BEQ.N    ??add_pin_0
//  133     { return ALRDY_IS; } 
        MOVS     R0,#+0
        B.N      ??add_pin_1
//  134 
//  135     // find free slot which is not connected
//  136     for(uint8_t pwm = 0; pwm < HWPWM_MODULE_NUM; pwm++)
??add_pin_0:
        MOVS     R0,#+0
??add_pin_2:
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+4
        BGE.N    ??add_pin_3
//  137     {
//  138         for(int i = 0; i < MAX_CHANNELS; i++)
        MOVS     R1,#+0
??add_pin_4:
        CMP      R1,#+4
        BGE.N    ??add_pin_5
//  139         {
//  140             if ( _pwm_dev[pwm]->PSEL.OUT[i] & PWM_PSEL_OUT_CONNECT_Msk )
        LDR.W    R2,??DataTable17_3
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        LDR      R2,[R2, R3, LSL #+2]
        ADD      R2,R2,R1, LSL #+2
        LDR      R2,[R2, #+1376]
        CMP      R2,#+0
        BPL.N    ??add_pin_6
//  141             {
//  142                 ch = i;
        STR      R1,[SP, #+4]
//  143                 pwm_index = pwm;   // далее работаем с этим модулем PWM
        MOVS     R2,R0
        SXTB     R2,R2            ;; SignExt  R2,R2,#+24,#+24
        MOVS     R6,R2
//  144                 break;
        B.N      ??add_pin_5
//  145             }
//  146         }
??add_pin_6:
        ADDS     R1,R1,#+1
        B.N      ??add_pin_4
//  147             
//  148         if(ch >= 0)
??add_pin_5:
        LDR      R1,[SP, #+4]
        CMP      R1,#+0
        BPL.N    ??add_pin_3
//  149         { break; }        
//  150      }    
??add_pin_7:
        ADDS     R0,R0,#+1
        B.N      ??add_pin_2
//  151     
//  152     // не удалось выделить канал
//  153     if(ch < 0)
??add_pin_3:
        LDR      R0,[SP, #+4]
        CMP      R0,#+0
        BPL.N    ??add_pin_8
//  154     { return ch; } 
        LDR      R0,[SP, #+4]
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        B.N      ??add_pin_1
//  155 
//  156     // если все ок, добавляем канал в карту вместе с пином и номером PWM модуля.
//  157     for (uint8_t i = 0; i < LEDS_NUM; i++)
??add_pin_8:
        MOVS     R0,#+0
??add_pin_9:
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+8
        BGE.N    ??add_pin_10
//  158     {
//  159         if (led_2_port_list[i] == pin) 
        LDR.W    R1,??DataTable17_4
        MOVS     R2,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LDR      R1,[R1, R2, LSL #+2]
        CMP      R1,R5
        BNE.N    ??add_pin_11
//  160         {
//  161             _pin_allocation_map[i][PIN_NUM] = (uint8_t)pin;
        MOVS     R1,#+6
        LDR.W    R2,??DataTable17_1
        MOVS     R3,R5
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MOVS     R7,R0
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        MULS     R7,R1,R7
        STRH     R3,[R2, R7]
//  162             _pin_allocation_map[i][CHN_NUM] = (uint8_t)ch;
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MULS     R3,R1,R3
        ADD      R3,R2,R3
        LDR      R7,[SP, #+4]
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        STRH     R7,[R3, #+2]
//  163             _pin_allocation_map[i][PWM_NUM] = (uint8_t)pwm_index;
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        MUL      R1,R1,R3
        ADD      R1,R2,R1
        MOVS     R2,R6
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        STRH     R2,[R1, #+4]
//  164             break;
        B.N      ??add_pin_10
//  165         }
//  166     }
??add_pin_11:
        ADDS     R0,R0,#+1
        B.N      ??add_pin_9
//  167     
//  168     nrf_gpio_cfg_output(pin);
??add_pin_10:
        MOVS     R0,R5
          CFI FunCall _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef519nrf_gpio_cfg_outputEj
        BL       _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef519nrf_gpio_cfg_outputEj
//  169     led = _pin_2_led(pin);
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[SP, #+0]
//  170     
//  171     // Must disable before changing PSEL
//  172     if (_is_enabled(pwm_index))
        MOVS     R1,R6
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm11_is_enabledEh
        BL       _ZN10nrf_hw_pwm11_is_enabledEh
        CMP      R0,#+0
        BEQ.N    ??add_pin_12
//  173     {
//  174         _pwm_dev[pwm_index]->ENABLE = 0;
        LDR.W    R0,??DataTable17_3
        MOVS     R1,#+0
        MOVS     R2,R6
        SXTB     R2,R2            ;; SignExt  R2,R2,#+24,#+24
        LDR      R2,[R0, R2, LSL #+2]
        STR      R1,[R2, #+1280]
//  175         _pwm_dev[pwm_index]->PSEL.OUT[ch] = pin;
        MOVS     R1,R6
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        LDR      R1,[R0, R1, LSL #+2]
        LDR      R2,[SP, #+4]
        ADD      R1,R1,R2, LSL #+2
        STR      R5,[R1, #+1376]
//  176         _pwm_dev[pwm_index]->ENABLE = 1;
        MOVS     R1,#+1
        MOVS     R2,R6
        SXTB     R2,R2            ;; SignExt  R2,R2,#+24,#+24
        LDR      R0,[R0, R2, LSL #+2]
        STR      R1,[R0, #+1280]
        B.N      ??add_pin_13
//  177     }
//  178     else
//  179     {
//  180         _pwm_dev[pwm_index]->PSEL.OUT[ch] = pin;
??add_pin_12:
        LDR.W    R0,??DataTable17_3
        MOVS     R1,R6
        SXTB     R1,R1            ;; SignExt  R1,R1,#+24,#+24
        LDR      R0,[R0, R1, LSL #+2]
        LDR      R1,[SP, #+4]
        ADD      R0,R0,R1, LSL #+2
        STR      R5,[R0, #+1376]
//  181     }
//  182     
//  183     //обнуляем канал
//  184     write_chnl(led, 0);
??add_pin_13:
        MOVS     R3,#+0
        MOVS     R2,#+0
        LDRH     R0,[SP, #+0]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
//  185     
//  186     return STATE_OK;
        MOVS     R0,#+1
??add_pin_1:
        POP      {R1-R7,PC}       ;; return
//  187 }
          CFI EndBlock cfiBlock11
//  188 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock12 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm10remove_pinEh
        THUMB
//  189 int8_t nrf_hw_pwm::remove_pin(uint8_t led)
//  190 {
_ZN10nrf_hw_pwm10remove_pinEh:
        PUSH     {R3-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+24
        MOVS     R4,R0
        MOVS     R5,R1
//  191     int8_t pwm_index = STATE_NA;
        MOVS     R6,#-1
//  192   
//  193     // неправильный светодиод
//  194     if (led >= LEDS_NUM)
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+8
        BLT.N    ??remove_pin_0
//  195     { return REMOVED; }
        MVNS     R0,#+2
        B.N      ??remove_pin_1
//  196 
//  197     volatile int ch = (int)_led_2_channel(led);
??remove_pin_0:
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm14_led_2_channelEh
        BL       _ZN10nrf_hw_pwm14_led_2_channelEh
        STR      R0,[SP, #+0]
//  198 
//  199     // неверный канал
//  200     if (ch < 0)
        LDR      R0,[SP, #+0]
        CMP      R0,#+0
        BPL.N    ??remove_pin_2
//  201     return (int16_t)ch; 
        LDR      R0,[SP, #+0]
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        B.N      ??remove_pin_1
//  202 
//  203     pwm_index = _pin_allocation_map[led][PWM_NUM];
??remove_pin_2:
        LDR.W    R1,??DataTable17_1
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R0,#+6
        MULS     R2,R0,R2
        ADD      R0,R1,R2
        LDRH     R7,[R0, #+4]
//  204 
//  205     bool const en = _is_enabled(pwm_index);
        MOVS     R1,R7
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm11_is_enabledEh
        BL       _ZN10nrf_hw_pwm11_is_enabledEh
        MOVS     R1,R0
//  206 
//  207     // Must disable before changing PSEL
//  208     if (en) _pwm_dev[pwm_index]->ENABLE = 0;
        MOVS     R0,R1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??remove_pin_3
        MOVS     R0,#+0
        LDR.W    R2,??DataTable17_3
        MOVS     R3,R7
        SXTB     R3,R3            ;; SignExt  R3,R3,#+24,#+24
        LDR      R2,[R2, R3, LSL #+2]
        STR      R0,[R2, #+1280]
//  209     
//  210     _pwm_dev[pwm_index]->PSEL.OUT[ch] = PIN_DISCONNECTED;
??remove_pin_3:
        LDR.W    R2,??DataTable17_3
        MOVS     R0,R7
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        LDR      R0,[R2, R0, LSL #+2]
        LDR      R3,[SP, #+0]
        ADD      R0,R0,R3, LSL #+2
        MOVS     R3,#-1
        STR      R3,[R0, #+1376]
//  211     
//  212     _seq_0[pwm_index][ch] = 0;
        LDR.W    R0,??DataTable17_2
        MOVS     R3,R7
        SXTB     R3,R3            ;; SignExt  R3,R3,#+24,#+24
        ADD      R0,R0,R3, LSL #+3
        LDR      R3,[SP, #+0]
        MOVS     R6,#+0
        STRH     R6,[R0, R3, LSL #+1]
//  213     
//  214     if (en) _pwm_dev[pwm_index]->ENABLE = 1;
        MOVS     R0,R1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??remove_pin_4
        MOVS     R0,#+1
        MOVS     R3,R7
        SXTB     R3,R3            ;; SignExt  R3,R3,#+24,#+24
        LDR      R2,[R2, R3, LSL #+2]
        STR      R0,[R2, #+1280]
//  215     
//  216     return REMOVED;
??remove_pin_4:
        MVNS     R0,#+2
??remove_pin_1:
        POP      {R1,R4-R7,PC}    ;; return
//  217 }
          CFI EndBlock cfiBlock12
//  218 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock13 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm14_led_2_channelEh
          CFI NoCalls
        THUMB
//  219 int16_t nrf_hw_pwm::_led_2_channel(uint8_t led)
//  220 {
_ZN10nrf_hw_pwm14_led_2_channelEh:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
        MOVS     R2,R0
//  221     // нет такого светодиода
//  222     if(led >= LEDS_NUM)
        MOVS     R0,R1
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+8
        BLT.N    ??_led_2_channel_0
//  223     { return  REMOVED; }
        MVNS     R0,#+2
        B.N      ??_led_2_channel_1
//  224 
//  225     if ( _pin_allocation_map[led][CHN_NUM] != CHNL_NA)
??_led_2_channel_0:
        MOVS     R0,#+6
        LDR.W    R3,??DataTable17_1
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        MULS     R4,R0,R4
        ADD      R4,R3,R4
        LDRSH    R4,[R4, #+2]
        CMN      R4,#+2
        BEQ.N    ??_led_2_channel_2
//  226     {  return _pin_allocation_map[led][CHN_NUM]; } 
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MULS     R1,R0,R1
        ADD      R0,R3,R1
        LDRSH    R0,[R0, #+2]
        B.N      ??_led_2_channel_1
//  227     else
//  228     {  
//  229         // нет такого канала
//  230         return CHNL_NA; 
??_led_2_channel_2:
        MVNS     R0,#+1
??_led_2_channel_1:
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
//  231     }    
//  232 }
          CFI EndBlock cfiBlock13
//  233 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock14 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm10_pin_2_ledEj
          CFI NoCalls
        THUMB
//  234 int16_t nrf_hw_pwm::_pin_2_led(uint32_t pin)
//  235 {
_ZN10nrf_hw_pwm10_pin_2_ledEj:
        PUSH     {R4,R5}
          CFI R5 Frame(CFA, -4)
          CFI R4 Frame(CFA, -8)
          CFI CFA R13+8
        MOVS     R3,R0
//  236     for(uint8_t led = 0; led < LEDS_NUM; led++)
        MOVS     R0,#+0
??_pin_2_led_0:
        MOVS     R2,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        CMP      R2,#+8
        BGE.N    ??_pin_2_led_1
//  237     {
//  238         // такой пин уже есть, выходим из функции
//  239         if(_pin_allocation_map[led][PIN_NUM] == pin)
        LDR.W    R4,??DataTable17_1
        MOVS     R5,R0
        UXTB     R5,R5            ;; ZeroExt  R5,R5,#+24,#+24
        MOVS     R2,#+6
        MULS     R5,R2,R5
        LDRSH    R2,[R4, R5]
        CMP      R2,R1
        BNE.N    ??_pin_2_led_2
//  240         { return led; }
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        B.N      ??_pin_2_led_3
//  241     }
??_pin_2_led_2:
        ADDS     R0,R0,#+1
        B.N      ??_pin_2_led_0
//  242 
//  243     // нет такого пина
//  244     return REMOVED;  
??_pin_2_led_1:
        MVNS     R0,#+2
??_pin_2_led_3:
        POP      {R4,R5}
          CFI R4 SameValue
          CFI R5 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
//  245 }
          CFI EndBlock cfiBlock14
//  246 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock15 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm11_is_enabledEh
          CFI NoCalls
        THUMB
//  247 bool nrf_hw_pwm::_is_enabled (uint8_t  pwm_index)
//  248 {
//  249   return _pwm_dev[pwm_index]->ENABLE;
_ZN10nrf_hw_pwm11_is_enabledEh:
        LDR.W    R2,??DataTable17_3
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        LDR      R1,[R2, R1, LSL #+2]
        LDR      R1,[R1, #+1280]
        CMP      R1,#+0
        BEQ.N    ??_is_enabled_0
        MOVS     R0,#+1
        B.N      ??_is_enabled_1
??_is_enabled_0:
        MOVS     R0,#+0
??_is_enabled_1:
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        BX       LR               ;; return
//  250 }
          CFI EndBlock cfiBlock15
//  251 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock16 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm5startEh
          CFI NoCalls
        THUMB
//  252 void nrf_hw_pwm::start(uint8_t  pwm_index)
//  253 {
_ZN10nrf_hw_pwm5startEh:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
//  254     _pwm_dev[pwm_index]->ENABLE  = (PWM_ENABLE_ENABLE_Enabled << PWM_ENABLE_ENABLE_Pos);
        MOVS     R2,#+1
        LDR.W    R3,??DataTable17_3
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R3,[R3, R4, LSL #+2]
        STR      R2,[R3, #+1280]
//  255 }
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock16
//  256 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock17 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm4stopEh
        THUMB
//  257 void nrf_hw_pwm::stop(uint8_t  pwm_index)
//  258 { 
_ZN10nrf_hw_pwm4stopEh:
        PUSH     {R1-R7,LR}
          CFI R14 Frame(CFA, -4)
          CFI R7 Frame(CFA, -8)
          CFI R6 Frame(CFA, -12)
          CFI R5 Frame(CFA, -16)
          CFI R4 Frame(CFA, -20)
          CFI CFA R13+32
        MOVS     R4,R0
        MOVS     R5,R1
//  259     // переводим все ножки этого модуля в режим низкого энергопотребления
//  260     for (uint8_t i = 0; i < LEDS_NUM; i++)
        MOVS     R6,#+0
??stop_0:
        MOVS     R0,R6
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+8
        BGE.N    ??stop_1
//  261     {
//  262         if (_pin_allocation_map[i][PWM_NUM] == pwm_index) 
        LDR.W    R1,??DataTable17_1
        MOVS     R2,R6
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R0,#+6
        MULS     R2,R0,R2
        ADD      R0,R1,R2
        LDRSH    R0,[R0, #+4]
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        SXTH     R1,R1            ;; SignExt  R1,R1,#+16,#+16
        CMP      R0,R1
        BNE.N    ??stop_2
//  263         {          
//  264             nrf_gpio_cfg(led_2_port_list[i],
//  265                              NRF_GPIO_PIN_DIR_INPUT,
//  266                              NRF_GPIO_PIN_INPUT_DISCONNECT,
//  267                              NRF_GPIO_PIN_NOPULL,
//  268                              NRF_GPIO_PIN_S0S1,
//  269                              NRF_GPIO_PIN_NOSENSE);
        MOVS     R0,#+0
        STR      R0,[SP, #+4]
        MOVS     R0,#+0
        STR      R0,[SP, #+0]
        MOVS     R3,#+0
        MOVS     R2,#+1
        MOVS     R1,#+0
        LDR.W    R0,??DataTable17_4
        MOVS     R7,R6
        UXTB     R7,R7            ;; ZeroExt  R7,R7,#+24,#+24
        LDR      R0,[R0, R7, LSL #+2]
          CFI FunCall _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef512nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
        BL       _ZN36_INTERNAL_14_nrf_hw_pwm_cpp_e85aaef512nrf_gpio_cfgEj18nrf_gpio_pin_dir_t20nrf_gpio_pin_input_t19nrf_gpio_pin_pull_t20nrf_gpio_pin_drive_t20nrf_gpio_pin_sense_t
//  270         }
//  271     }
??stop_2:
        ADDS     R6,R6,#+1
        B.N      ??stop_0
//  272     
//  273     // останавливаем только если модуль был активирован, потому что
//  274     // иначе просто зависнет на while, поскольку TASKS_STOP не работает
//  275     // если модуль не активен.
//  276     if(_is_enabled(pwm_index))
??stop_1:
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm11_is_enabledEh
        BL       _ZN10nrf_hw_pwm11_is_enabledEh
        CMP      R0,#+0
        BEQ.N    ??stop_3
//  277     {
//  278         _pwm_dev[pwm_index]->TASKS_STOP = 1;
        LDR.W    R1,??DataTable17_3
        MOVS     R0,#+1
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LDR      R2,[R1, R2, LSL #+2]
        STR      R0,[R2, #+4]
//  279         
//  280         while(!_pwm_dev[pwm_index]->EVENTS_STOPPED);
??stop_4:
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        LDR      R0,[R1, R0, LSL #+2]
        LDR      R0,[R0, #+260]
        CMP      R0,#+0
        BEQ.N    ??stop_4
//  281     }
//  282             
//  283     for(uint8_t i = 0; i < MAX_CHANNELS; i++)
??stop_3:
        MOVS     R0,#+0
??stop_5:
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        CMP      R1,#+4
        BGE.N    ??stop_6
//  284     {
//  285         if(_pwm_dev[pwm_index]->PSEL.OUT[i] != PIN_DISCONNECTED)
        LDR.W    R1,??DataTable17_3
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LDR      R2,[R1, R2, LSL #+2]
        MOVS     R3,R0
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADD      R2,R2,R3, LSL #+2
        LDR      R2,[R2, #+1376]
        CMN      R2,#+1
        BEQ.N    ??stop_7
//  286         { _pwm_dev[pwm_index]->PSEL.OUT[i] = PIN_DISCONNECTED; }     
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LDR      R1,[R1, R2, LSL #+2]
        MOVS     R2,R0
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        ADD      R1,R1,R2, LSL #+2
        MOVS     R2,#-1
        STR      R2,[R1, #+1376]
//  287     }
??stop_7:
        ADDS     R0,R0,#+1
        B.N      ??stop_5
//  288     
//  289     // только после всего выключаем сам модуль, такие вот грабли.    
//  290     _pwm_dev[pwm_index]->ENABLE = 0;
??stop_6:
        MOVS     R0,#+0
        LDR.N    R1,??DataTable17_3
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        LDR      R1,[R1, R2, LSL #+2]
        STR      R0,[R1, #+1280]
//  291 }
        POP      {R0-R2,R4-R7,PC}  ;; return
          CFI EndBlock cfiBlock17
//  292 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock18 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm6_setupEh
          CFI NoCalls
        THUMB
//  293 void nrf_hw_pwm::_setup(uint8_t pwm_index)
//  294 {
_ZN10nrf_hw_pwm6_setupEh:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
//  295     // Initialize Registers
//  296     _pwm_dev[pwm_index]->MODE            = PWM_MODE_UPDOWN_UpAndDown;
        LDR.N    R2,??DataTable17_3
        MOVS     R3,#+1
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1284]
//  297     _pwm_dev[pwm_index]->PRESCALER       = (uint32_t)_clock_div;
        LDRB     R3,[R0, #+2]
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1292]
//  298     _pwm_dev[pwm_index]->DECODER         = (PWM_DECODER_LOAD_Individual << PWM_DECODER_LOAD_Pos) | 
//  299                                            (PWM_DECODER_MODE_RefreshCount << PWM_DECODER_MODE_Pos);
        MOVS     R3,#+2
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1296]
//  300     _pwm_dev[pwm_index]->LOOP            = (PWM_LOOP_CNT_Disabled << PWM_LOOP_CNT_Pos);
        MOVS     R3,#+0
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1300]
//  301     
//  302     _pwm_dev[pwm_index]->SEQ[0].PTR      = (uint32_t) &_seq_0[pwm_index];
        LDR.N    R3,??DataTable17_2
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        ADD      R3,R3,R4, LSL #+3
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1312]
//  303     _pwm_dev[pwm_index]->SEQ[0].CNT      = MAX_CHANNELS; // default mode is Individual --> count must be 4
        MOVS     R3,#+4
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1316]
//  304     _pwm_dev[pwm_index]->SEQ[0].REFRESH  = 0;
        MOVS     R3,#+0
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1320]
//  305     _pwm_dev[pwm_index]->SEQ[0].ENDDELAY = 0;
        MOVS     R3,#+0
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1324]
//  306     
//  307     _pwm_dev[pwm_index]->SEQ[1].PTR      = 0;
        MOVS     R3,#+0
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1344]
//  308     _pwm_dev[pwm_index]->SEQ[1].CNT      = 0;
        MOVS     R3,#+0
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1348]
//  309     _pwm_dev[pwm_index]->SEQ[1].REFRESH  = 0;
        MOVS     R3,#+0
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R4,[R2, R4, LSL #+2]
        STR      R3,[R4, #+1352]
//  310     _pwm_dev[pwm_index]->SEQ[1].ENDDELAY = 0;
        MOVS     R3,#+0
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R2,[R2, R4, LSL #+2]
        STR      R3,[R2, #+1356]
//  311 }   
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock18
//  312 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock19 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm13_run_sequenceEh
          CFI NoCalls
        THUMB
//  313 void nrf_hw_pwm::_run_sequence(uint8_t pwm_index)
//  314 {    
_ZN10nrf_hw_pwm13_run_sequenceEh:
        PUSH     {R4}
          CFI R4 Frame(CFA, -4)
          CFI CFA R13+4
//  315     // запускаем PWM
//  316     _pwm_dev[pwm_index]->TASKS_SEQSTART[0] = 1;
        MOVS     R2,#+1
        LDR.N    R3,??DataTable17_3
        MOVS     R4,R1
        UXTB     R4,R4            ;; ZeroExt  R4,R4,#+24,#+24
        LDR      R3,[R3, R4, LSL #+2]
        STR      R2,[R3, #+8]
//  317 }
        POP      {R4}
          CFI R4 SameValue
          CFI CFA R13+0
        BX       LR               ;; return
          CFI EndBlock cfiBlock19
//  318 
//  319 inline int8_t nrf_hw_pwm::write_chnl(uint8_t led, uint32_t value, bool inverted)
//  320 {
//  321     uint8_t pwm_index = STATE_NA;
//  322   
//  323     // неправильный светодиод
//  324     if (led >= LEDS_NUM)
//  325     { return REMOVED; }
//  326 
//  327     volatile int ch = (int)_led_2_channel(led);
//  328 
//  329     // неверный канал
//  330     if (ch < 0)
//  331     return (int16_t)ch;
//  332 
//  333     pwm_index = _pin_allocation_map[led][PWM_NUM];
//  334 
//  335     _seq_0[pwm_index][ch] = value | (inverted ? 0 : 1UL << 15);
//  336 
//  337     // Start PWM if not already
//  338     if (!_is_enabled(pwm_index))  
//  339     { start(pwm_index); }
//  340     
//  341     _run_sequence(pwm_index);    
//  342     
//  343     return STATE_OK;
//  344 }
//  345 
//  346 inline int8_t nrf_hw_pwm::write_pin(uint32_t pin, uint32_t value, bool inverted)
//  347 {
//  348     volatile int16_t led = _pin_2_led(pin); 
//  349     
//  350     if(led < ALRDY_IS)
//  351     { return REMOVED; }  
//  352     
//  353     write_chnl(led, value, inverted);
//  354     
//  355     return STATE_OK;
//  356 }
//  357 
//  358 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock20 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm8read_pinEj
        THUMB
//  359 int nrf_hw_pwm::read_pin(uint32_t pin)
//  360 {
_ZN10nrf_hw_pwm8read_pinEj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
//  361     volatile int16_t led = _pin_2_led(pin); 
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[SP, #+0]
//  362     
//  363     if(led < ALRDY_IS)
        LDRSH    R0,[SP, #+0]
        CMP      R0,#+0
        BPL.N    ??read_pin_0
//  364     { return REMOVED; }
        MVNS     R0,#+2
        B.N      ??read_pin_1
//  365         
//  366     return read_chnl(led);
??read_pin_0:
        LDRH     R0,[SP, #+0]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm9read_chnlEh
        BL       _ZN10nrf_hw_pwm9read_chnlEh
??read_pin_1:
        POP      {R1,R4,R5,PC}    ;; return
//  367 }
          CFI EndBlock cfiBlock20
//  368 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock21 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm9read_chnlEh
        THUMB
//  369 int nrf_hw_pwm::read_chnl(uint8_t led)
//  370 {
_ZN10nrf_hw_pwm9read_chnlEh:
        PUSH     {R2-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+24
        MOVS     R4,R0
        MOVS     R5,R1
//  371     int8_t pwm_index = STATE_NA;
        MOVS     R6,#-1
//  372     
//  373     // неправильный светодиод
//  374     if (led >= LEDS_NUM)
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+8
        BLT.N    ??read_chnl_0
//  375     { return REMOVED; }
        MVNS     R0,#+2
        B.N      ??read_chnl_1
//  376 
//  377     volatile int ch = (int)_led_2_channel(led);
??read_chnl_0:
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm14_led_2_channelEh
        BL       _ZN10nrf_hw_pwm14_led_2_channelEh
        STR      R0,[SP, #+0]
//  378 
//  379     // неверный канал
//  380     if (ch < 0)
        LDR      R0,[SP, #+0]
        CMP      R0,#+0
        BPL.N    ??read_chnl_2
//  381     return (int16_t)ch;
        MOV      R0,SP
        LDR      R0,[R0, #+0]
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        B.N      ??read_chnl_1
//  382 
//  383     pwm_index = _pin_allocation_map[led][PWM_NUM];
??read_chnl_2:
        LDR.N    R1,??DataTable17_1
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R0,#+6
        MULS     R2,R0,R2
        ADD      R0,R1,R2
        LDRH     R0,[R0, #+4]
//  384 
//  385     return (_seq_0[pwm_index][ch] & 0x7FFF);
        LDR.N    R1,??DataTable17_2
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        ADD      R0,R1,R0, LSL #+3
        LDR      R1,[SP, #+0]
        LDRH     R0,[R0, R1, LSL #+1]
        LSLS     R0,R0,#+17       ;; ZeroExtS R0,R0,#+17,#+17
        LSRS     R0,R0,#+17
??read_chnl_1:
        POP      {R1,R2,R4-R6,PC}  ;; return
//  386 }
          CFI EndBlock cfiBlock21
//  387 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock22 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm11get_channelEj
        THUMB
//  388 int nrf_hw_pwm::get_channel(uint32_t pin)
//  389 {
_ZN10nrf_hw_pwm11get_channelEj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
//  390     volatile int16_t led = _pin_2_led(pin); 
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[SP, #+0]
//  391     
//  392     if(led < ALRDY_IS)
        LDRSH    R0,[SP, #+0]
        CMP      R0,#+0
        BPL.N    ??get_channel_0
//  393     { return REMOVED; }  
        MVNS     R0,#+2
        B.N      ??get_channel_1
//  394     
//  395     return _pin_allocation_map[led][CHN_NUM];
??get_channel_0:
        LDR.N    R0,??DataTable17_1
        LDRSH    R1,[SP, #+0]
        MOVS     R2,#+6
        SMULBB   R1,R1,R2
        ADD      R0,R0,R1
        LDRSH    R0,[R0, #+2]
??get_channel_1:
        POP      {R1,R4,R5,PC}    ;; return
//  396 }
          CFI EndBlock cfiBlock22
//  397 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock23 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm11get_pwm_numEj
        THUMB
//  398 int nrf_hw_pwm::get_pwm_num(uint32_t pin)
//  399 {
_ZN10nrf_hw_pwm11get_pwm_numEj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
//  400     volatile int16_t led = _pin_2_led(pin); 
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[SP, #+0]
//  401     
//  402     if(led < ALRDY_IS)
        LDRSH    R0,[SP, #+0]
        CMP      R0,#+0
        BPL.N    ??get_pwm_num_0
//  403     { return REMOVED; }  
        MVNS     R0,#+2
        B.N      ??get_pwm_num_1
//  404     
//  405     return _pin_allocation_map[led][PWM_NUM];
??get_pwm_num_0:
        LDR.N    R0,??DataTable17_1
        LDRSH    R1,[SP, #+0]
        MOVS     R2,#+6
        SMULBB   R1,R1,R2
        ADD      R0,R0,R1
        LDRSH    R0,[R0, #+4]
??get_pwm_num_1:
        POP      {R1,R4,R5,PC}    ;; return
//  406 }
          CFI EndBlock cfiBlock23
//  407 

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock24 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm11get_led_numEj
        THUMB
//  408 int nrf_hw_pwm::get_led_num(uint32_t pin)
//  409 {
_ZN10nrf_hw_pwm11get_led_numEj:
        PUSH     {R3-R5,LR}
          CFI R14 Frame(CFA, -4)
          CFI R5 Frame(CFA, -8)
          CFI R4 Frame(CFA, -12)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
//  410     volatile int16_t led = _pin_2_led(pin); 
        MOVS     R1,R5
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10_pin_2_ledEj
        BL       _ZN10nrf_hw_pwm10_pin_2_ledEj
        STRH     R0,[SP, #+0]
//  411     
//  412     if(led < ALRDY_IS)
        LDRSH    R0,[SP, #+0]
        CMP      R0,#+0
        BPL.N    ??get_led_num_0
//  413     { return REMOVED; }  
        MVNS     R0,#+2
        B.N      ??get_led_num_1
//  414     
//  415     return led;
??get_led_num_0:
        LDRSH    R0,[SP, #+0]
??get_led_num_1:
        POP      {R1,R4,R5,PC}    ;; return
//  416 }
          CFI EndBlock cfiBlock24

        SECTION `.text`:CODE:NOROOT(1)
          CFI Block cfiBlock25 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm12set_chrg_barEs
        THUMB
_ZN10nrf_hw_pwm12set_chrg_barEs:
        PUSH     {R4-R6,LR}
          CFI R14 Frame(CFA, -4)
          CFI R6 Frame(CFA, -8)
          CFI R5 Frame(CFA, -12)
          CFI R4 Frame(CFA, -16)
          CFI CFA R13+16
        MOVS     R4,R0
        MOVS     R5,R1
        MVNS     R0,#+2
        LDRSH    R1,[R4, #+4]
        CMP      R1,R0
        BEQ.N    ??set_chrg_bar_0
        LDRSH    R1,[R4, #+6]
        CMP      R1,R0
        BEQ.N    ??set_chrg_bar_0
        LDRSH    R0,[R4, #+8]
        CMN      R0,#+3
        BNE.N    ??set_chrg_bar_1
??set_chrg_bar_0:
        B.N      ??set_chrg_bar_2
??set_chrg_bar_1:
        LDR.N    R6,??DataTable17_5
        LDRSH    R0,[R6, #+0]
        MOVS     R1,R5
        SXTH     R1,R1            ;; SignExt  R1,R1,#+16,#+16
        CMP      R0,R1
        BEQ.W    ??set_chrg_bar_3
        MOVS     R0,R5
        SXTH     R0,R0            ;; SignExt  R0,R0,#+16,#+16
        CMP      R0,#+0
        BEQ.N    ??set_chrg_bar_4
        CMP      R0,#+2
        BEQ.N    ??set_chrg_bar_5
        BCC.N    ??set_chrg_bar_6
        CMP      R0,#+4
        BEQ.N    ??set_chrg_bar_7
        BCC.N    ??set_chrg_bar_8
        B.N      ??set_chrg_bar_9
??set_chrg_bar_4:
        MOVS     R3,#+1
        MOVS     R2,#+220
        LDRH     R0,[R4, #+6]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??set_chrg_bar_10
??set_chrg_bar_6:
        MOVS     R3,#+1
        MOVS     R2,#+220
        LDRH     R0,[R4, #+6]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+1
        MOVS     R2,#+220
        LDRH     R0,[R4, #+4]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??set_chrg_bar_10
??set_chrg_bar_5:
        MOVS     R3,#+1
        MOVS     R2,#+220
        LDRH     R0,[R4, #+6]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+1
        MOVS     R2,#+220
        LDRH     R0,[R4, #+4]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+0
        MOVS     R2,#+32
        LDRH     R0,[R4, #+8]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??set_chrg_bar_10
??set_chrg_bar_8:
        MOVS     R3,#+1
        MOVS     R2,#+220
        LDRH     R0,[R4, #+6]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+1
        MOVS     R2,#+0
        LDRH     R0,[R4, #+4]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+0
        MOVS     R2,#+32
        LDRH     R0,[R4, #+8]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??set_chrg_bar_10
??set_chrg_bar_7:
        MOVS     R3,#+0
        MOVS     R2,#+32
        LDRH     R0,[R4, #+6]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+0
        MOVS     R2,#+32
        LDRH     R0,[R4, #+4]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+0
        MOVS     R2,#+45
        LDRH     R0,[R4, #+8]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        B.N      ??set_chrg_bar_10
??set_chrg_bar_9:
        MOVS     R3,#+0
        MOVS     R2,#+0
        LDRH     R0,[R4, #+6]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+0
        MOVS     R2,#+0
        LDRH     R0,[R4, #+4]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
        MOVS     R3,#+0
        MOVS     R2,#+0
        LDRH     R0,[R4, #+8]
        MOVS     R1,R0
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm10write_chnlEhjb
        BL       _ZN10nrf_hw_pwm10write_chnlEhjb
??set_chrg_bar_10:
        STRH     R5,[R6, #+0]
??set_chrg_bar_3:
??set_chrg_bar_2:
        POP      {R4-R6,PC}       ;; return
          CFI EndBlock cfiBlock25

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable17:
        DATA32
        DC32     0x50000300

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable17_1:
        DATA32
        DC32     _ZN10nrf_hw_pwm19_pin_allocation_mapE

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable17_2:
        DATA32
        DC32     _ZN10nrf_hw_pwm6_seq_0E

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable17_3:
        DATA32
        DC32     _ZN10nrf_hw_pwm8_pwm_devE

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable17_4:
        DATA32
        DC32     led_2_port_list

        SECTION `.text`:CODE:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
??DataTable17_5:
        DATA32
        DC32     _ZN10nrf_hw_pwm19_old_chrg_bar_stateE

        SECTION `.text`:CODE:REORDER:NOROOT(2)
        SECTION_GROUP _ZN10nrf_hw_pwm10write_chnlEhjb
          CFI Block cfiBlock26 Using cfiCommon0
          CFI Function _ZN10nrf_hw_pwm10write_chnlEhjb
        THUMB
_ZN10nrf_hw_pwm10write_chnlEhjb:
        PUSH     {R3-R9,LR}
          CFI R14 Frame(CFA, -4)
          CFI R9 Frame(CFA, -8)
          CFI R8 Frame(CFA, -12)
          CFI R7 Frame(CFA, -16)
          CFI R6 Frame(CFA, -20)
          CFI R5 Frame(CFA, -24)
          CFI R4 Frame(CFA, -28)
          CFI CFA R13+32
        MOVS     R4,R0
        MOVS     R5,R1
        MOVS     R6,R2
        MOVS     R7,R3
        MOV      R8,#+255
        MOVS     R0,R5
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+8
        BLT.N    ??write_chnl_1
        MVNS     R0,#+2
        B.N      ??write_chnl_2
??write_chnl_1:
        MOVS     R1,R5
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm14_led_2_channelEh
        BL       _ZN10nrf_hw_pwm14_led_2_channelEh
        STR      R0,[SP, #+0]
        LDR      R0,[SP, #+0]
        CMP      R0,#+0
        BPL.N    ??write_chnl_3
        LDR      R0,[SP, #+0]
        SXTB     R0,R0            ;; SignExt  R0,R0,#+24,#+24
        B.N      ??write_chnl_2
??write_chnl_3:
        LDR.N    R1,??write_chnl_0
        MOVS     R2,R5
        UXTB     R2,R2            ;; ZeroExt  R2,R2,#+24,#+24
        MOVS     R0,#+6
        MULS     R2,R0,R2
        ADD      R0,R1,R2
        LDRH     R9,[R0, #+4]
        LDR      R1,[SP, #+0]
        MOVS     R0,R7
        UXTB     R0,R0            ;; ZeroExt  R0,R0,#+24,#+24
        CMP      R0,#+0
        BEQ.N    ??write_chnl_4
        MOVS     R0,#+0
        B.N      ??write_chnl_5
??write_chnl_4:
        MOV      R0,#+32768
??write_chnl_5:
        LDR.N    R2,??write_chnl_0+0x4
        MOV      R3,R9
        UXTB     R3,R3            ;; ZeroExt  R3,R3,#+24,#+24
        ADD      R2,R2,R3, LSL #+3
        ORRS     R0,R0,R6
        STRH     R0,[R2, R1, LSL #+1]
        MOV      R1,R9
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm11_is_enabledEh
        BL       _ZN10nrf_hw_pwm11_is_enabledEh
        CMP      R0,#+0
        BNE.N    ??write_chnl_6
        MOV      R1,R9
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm5startEh
        BL       _ZN10nrf_hw_pwm5startEh
??write_chnl_6:
        MOV      R1,R9
        UXTB     R1,R1            ;; ZeroExt  R1,R1,#+24,#+24
        MOVS     R0,R4
          CFI FunCall _ZN10nrf_hw_pwm13_run_sequenceEh
        BL       _ZN10nrf_hw_pwm13_run_sequenceEh
        MOVS     R0,#+1
??write_chnl_2:
        POP      {R1,R4-R9,PC}    ;; return
        Nop      
        DATA
??write_chnl_0:
        DATA32
        DC32     _ZN10nrf_hw_pwm19_pin_allocation_mapE
        DC32     _ZN10nrf_hw_pwm6_seq_0E
          CFI EndBlock cfiBlock26

        SECTION `.iar_vfe_header`:DATA:NOALLOC:NOROOT(2)
        SECTION_TYPE SHT_PROGBITS, 0
        DATA
        DC32 0

        END
//  417 
//  418 #ifdef THREE_PIN_CHARGE_BAR
//  419 void nrf_hw_pwm::set_chrg_bar(int16_t led_num)
//  420 {
//  421     // не управляем ни чем если пины удалены.
//  422     if (_chctrl_1 == REMOVED ||
//  423         _chctrl_2 == REMOVED || 
//  424         _chctrl_3 == REMOVED)
//  425     { return; }
//  426 
//  427     // чтобы не моргало.
//  428     if (_old_chrg_bar_state != led_num)
//  429     {
//  430         switch(led_num)
//  431         {
//  432             case CHARGE_LED_1:
//  433                 write_chnl(_chctrl_2, 220, true);
//  434                 break;
//  435     
//  436             case CHARGE_LED_2:
//  437                 write_chnl(_chctrl_2, 220, true);
//  438                 write_chnl(_chctrl_1, 220, true);
//  439                 break;
//  440     
//  441             case CHARGE_LED_3:
//  442                 write_chnl(_chctrl_2, 220, true);
//  443                 write_chnl(_chctrl_1, 220, true);
//  444                 write_chnl(_chctrl_3,        32);
//  445                 break;
//  446     
//  447             case CHARGE_LED_4:
//  448                 write_chnl(_chctrl_2, 220, true);
//  449                 write_chnl(_chctrl_1,   0, true);
//  450                 write_chnl(_chctrl_3,        32);
//  451                 break;
//  452     
//  453             case CHARGE_LED_5:
//  454                 write_chnl(_chctrl_2, 32);
//  455                 write_chnl(_chctrl_1, 32);
//  456                 write_chnl(_chctrl_3, 45);
//  457                 break;
//  458                 
//  459             case SHTDWN:
//  460             default:
//  461                 write_chnl(_chctrl_2, 0);
//  462                 write_chnl(_chctrl_1, 0);
//  463                 write_chnl(_chctrl_3, 0);
//  464                 break;
//  465         }
//  466     
//  467         _old_chrg_bar_state = led_num;
//  468 
//  469     }
//  470 }
//  471 #endif // THREE_PIN_CHARGE_BAR
//  472 
//  473 
//  474 
//  475 
// 
//    80 bytes in section .bss
//    18 bytes in section .data
// 2'530 bytes in section .text
// 
// 2'374 bytes of CODE memory (+ 156 bytes shared)
//    98 bytes of DATA memory
//
//Errors: none
//Warnings: none
