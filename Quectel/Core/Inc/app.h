#ifndef APP_H
#define APP_H

#include "main.h"
#include "cmsis_os2.h"
#include <stdint.h>

/* Modem state for Live Expressions/debugging */
typedef enum
{
    MODEM_STATE_IDLE = 0,
    MODEM_STATE_SEND_COMMAND,
    MODEM_STATE_WAIT_RESPONSE,
    MODEM_STATE_RESPONSE_OK,
    MODEM_STATE_RESPONSE_ERROR,
    MODEM_STATE_TIMEOUT
} modem_state_t;

/* Main app function */
void start_module(void);

/* FreeRTOS modem task */
void modem_task(void *argument);

#endif
