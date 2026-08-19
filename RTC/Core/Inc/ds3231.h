#ifndef DS3231_H_
#define DS3231_H_

#include "main.h"
#include <stdint.h>

#define DS3231_ADDRESS      (0x68 << 1)

typedef enum
{
    DS3231_OK = 0,
    DS3231_ERROR
} DS3231_StatusTypeDef;

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DS3231_TimeTypeDef;

DS3231_StatusTypeDef DS3231_Init(I2C_HandleTypeDef *hi2c);
DS3231_StatusTypeDef DS3231_Detect(void);
DS3231_StatusTypeDef DS3231_SetTime(DS3231_TimeTypeDef *time);
DS3231_StatusTypeDef DS3231_GetTime(DS3231_TimeTypeDef *time);

#endif
