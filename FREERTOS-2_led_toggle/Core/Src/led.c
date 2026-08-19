/*
 * led.c
 *
 *  Created on: May 8, 2026
 *      Author: Asmita Milind Bagad
 */


#include "led.h"
#include "main.h"
#include "cmsis_os2.h"

void LED1_Task(void)
{
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    osDelay(500);
  }
}

void LED2_Task(void)
{
  while (1)
  {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_9);
    osDelay(1000);
  }
}
