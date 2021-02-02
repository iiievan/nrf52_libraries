#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

#include <intrinsics.h>
#include <stdio.h>
#include "stdint.h"
#include "nrf.h"
#include "nrf_gpio.h"

typedef uint64_t  u64;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

//настройка загрузчик дл€ приемника или передатчика
//#define TRANSMITTER
#define RECEIVER
//#define RECEIVER_SD

//верси€ железа 0 - первое поколение 1- второе 2 - авто
#define HW_VERSION      2
#if HW_VERSION > 2
  #error "wrong hw_version!"
#endif

// ѕолезные макросы дл€ уточнени€ намерений в коде
#define PUBLIC  __IO
#define PRIVATE static
#define FORWARD static
#define _EXTERN extern

// ѕравило одного определени€
#ifdef __ALLOCATE_NOW__
  #define GLOBAL    PUBLIC
  #define _EQU(x)	=(x)
#else
  #define GLOBAL    _EXTERN
  #define _EQU(x)
#endif

// ¬ описании функции могут быть определены дополнительные коды ошибок (#define)
#define PROGRESS        1
#define OK              0
#define FAIL            -1

// —тандартные макросы:
#define BIT(bit)          (1UL << (bit))

#define SETBIT(Val,bit)   ((Val) |= BIT(bit))
#define CLRBIT(Val,bit)   ((Val) &= ~BIT(bit))
#define XORBIT(Val,bit)   ((Val) ^= BIT(bit))
#define TSTBIT(Val,bit)   ((Val) & BIT(bit))

typedef  void (*pFunction)(void);

#include "boot_tools.h"


/******************************************************************************

                        адреса прошивок во флеш

*******************************************************************************/
//адрес рабочей прошивки
#define PRORGAMM_START  0x0002000
//конец рабочей прошивки
#define PROGRAMM_END    0x001FFFE
//адрес по которому лежит контрольна€ сумма рабочей прошивки
#define CHECKSUM_ADR    0x001FFFE
//размер контрольной суммы в байтах
#define CHECKSUM_SIZE   2

//идентификатор передатчика раздающего прошивку
#define TRANSMITTER_UDTADE_ID           4095
#define TRANSMITTER_UDTADE_ID_SD        4094

//суммарна€ длинна пакета BLE
#define BLE_PACKET_LEN          39
//номер канала bluetooth
#define BLUETOOTH_CH_NUM        39
//размер пользовательских данных (данные прошивки)
#define PAYLOAD_DATA_SIZE       20
//размер заголовка с пользовательскими данными
#define HEADER_DATA_SIZE        4
//размер данных зарезервированных по стандарту BLE
#define BLE_RESERVERD_SIZE      15

typedef union
{
  __packed struct
  {
    u32   transmitter_id: 12;                   //уникальный id передатчика
    u32   receiver_id:1;                        //id прошивки - дл€ приемника или передатчика
    u32   flash_adr:19;                         //относительный адрес флеш, дл€ записи прошивки
  };
  u8  byte[HEADER_DATA_SIZE];
}TRFHeader;


typedef __packed struct {
  u8            ble_reserved[BLE_RESERVERD_SIZE];
  TRFHeader     header;
  u8            payload[PAYLOAD_DATA_SIZE];
  s8            RSSI;
}TRFData;

#endif