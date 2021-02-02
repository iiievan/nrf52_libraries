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

//��������� ��������� ��� ��������� ��� �����������
//#define TRANSMITTER
#define RECEIVER
//#define RECEIVER_SD

//������ ������ 0 - ������ ��������� 1- ������ 2 - ����
#define HW_VERSION      2
#if HW_VERSION > 2
  #error "wrong hw_version!"
#endif

// �������� ������� ��� ��������� ��������� � ����
#define PUBLIC  __IO
#define PRIVATE static
#define FORWARD static
#define _EXTERN extern

// ������� ������ �����������
#ifdef __ALLOCATE_NOW__
  #define GLOBAL    PUBLIC
  #define _EQU(x)	=(x)
#else
  #define GLOBAL    _EXTERN
  #define _EQU(x)
#endif

// � �������� ������� ����� ���� ���������� �������������� ���� ������ (#define)
#define PROGRESS        1
#define OK              0
#define FAIL            -1

// ����������� �������:
#define BIT(bit)          (1UL << (bit))

#define SETBIT(Val,bit)   ((Val) |= BIT(bit))
#define CLRBIT(Val,bit)   ((Val) &= ~BIT(bit))
#define XORBIT(Val,bit)   ((Val) ^= BIT(bit))
#define TSTBIT(Val,bit)   ((Val) & BIT(bit))

typedef  void (*pFunction)(void);

#include "boot_tools.h"


/******************************************************************************

                        ������ �������� �� ����

*******************************************************************************/
//����� ������� ��������
#define PRORGAMM_START  0x0002000
//����� ������� ��������
#define PROGRAMM_END    0x001FFFE
//����� �� �������� ����� ����������� ����� ������� ��������
#define CHECKSUM_ADR    0x001FFFE
//������ ����������� ����� � ������
#define CHECKSUM_SIZE   2

//������������� ����������� ���������� ��������
#define TRANSMITTER_UDTADE_ID           4095
#define TRANSMITTER_UDTADE_ID_SD        4094

//��������� ������ ������ BLE
#define BLE_PACKET_LEN          39
//����� ������ bluetooth
#define BLUETOOTH_CH_NUM        39
//������ ���������������� ������ (������ ��������)
#define PAYLOAD_DATA_SIZE       20
//������ ��������� � ����������������� �������
#define HEADER_DATA_SIZE        4
//������ ������ ����������������� �� ��������� BLE
#define BLE_RESERVERD_SIZE      15

typedef union
{
  __packed struct
  {
    u32   transmitter_id: 12;                   //���������� id �����������
    u32   receiver_id:1;                        //id �������� - ��� ��������� ��� �����������
    u32   flash_adr:19;                         //������������� ����� ����, ��� ������ ��������
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