#include "ds3231.h"

static I2C_HandleTypeDef *ds3231_hi2c;

static uint8_t Dec_To_BCD(uint8_t value)
{
    return ((value / 10) << 4) | (value % 10);
}

static uint8_t BCD_To_Dec(uint8_t value)
{
    return ((value >> 4) * 10) + (value & 0x0F);
}

DS3231_StatusTypeDef DS3231_Init(I2C_HandleTypeDef *hi2c)
{
    ds3231_hi2c = hi2c;

    return DS3231_Detect();
}

DS3231_StatusTypeDef DS3231_Detect(void)
{
    if (ds3231_hi2c == NULL)
    {
        return DS3231_ERROR;
    }

    if (HAL_I2C_IsDeviceReady(ds3231_hi2c,
                              DS3231_ADDRESS,
                              3,
                              100) == HAL_OK)
    {
        return DS3231_OK;
    }

    return DS3231_ERROR;
}

DS3231_StatusTypeDef DS3231_SetTime(DS3231_TimeTypeDef *time)
{
    uint8_t data[7];

    if (ds3231_hi2c == NULL)
    {
        return DS3231_ERROR;
    }

    data[0] = Dec_To_BCD(time->seconds);
    data[1] = Dec_To_BCD(time->minutes);
    data[2] = Dec_To_BCD(time->hours);   // 24-hour format
    data[3] = Dec_To_BCD(time->day);
    data[4] = Dec_To_BCD(time->date);
    data[5] = Dec_To_BCD(time->month);
    data[6] = Dec_To_BCD(time->year);

    if (HAL_I2C_Mem_Write(ds3231_hi2c,
                          DS3231_ADDRESS,
                          0x00,
                          I2C_MEMADD_SIZE_8BIT,
                          data,
                          7,
                          100) == HAL_OK)
    {
        return DS3231_OK;
    }

    return DS3231_ERROR;
}

DS3231_StatusTypeDef DS3231_GetTime(DS3231_TimeTypeDef *time)
{
    uint8_t data[7];

    if (ds3231_hi2c == NULL)
    {
        return DS3231_ERROR;
    }

    if (HAL_I2C_Mem_Read(ds3231_hi2c,
                         DS3231_ADDRESS,
                         0x00,
                         I2C_MEMADD_SIZE_8BIT,
                         data,
                         7,
                         100) != HAL_OK)
    {
        return DS3231_ERROR;
    }

    time->seconds = BCD_To_Dec(data[0] & 0x7F);
    time->minutes = BCD_To_Dec(data[1] & 0x7F);
    time->hours   = BCD_To_Dec(data[2] & 0x3F);
    time->day     = BCD_To_Dec(data[3] & 0x07);
    time->date    = BCD_To_Dec(data[4] & 0x3F);
    time->month   = BCD_To_Dec(data[5] & 0x1F);
    time->year    = BCD_To_Dec(data[6]);

    return DS3231_OK;
}
