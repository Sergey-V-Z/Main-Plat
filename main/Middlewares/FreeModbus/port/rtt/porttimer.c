/*
 * FreeModbus Libary: RT-Thread Port
 * Copyright (C) 2013 Armink <armink.ztl@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.60 2013/08/13 15:07:05 Armink $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/
extern TIM_HandleTypeDef htim2;
#define TIMER htim2
uint16_t timeout = 0;
uint16_t downcounter = 0;
 

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit(USHORT usTim1Timerout50us)
{
  TIM_MasterConfigTypeDef sMasterConfig;
 
  TIMER.Instance = TIM2;
  TIMER.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 1000000) - 1;
  TIMER.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIMER.Init.Period = 50 - 1;
  
  timeout = usTim1Timerout50us;
  
  if (HAL_TIM_Base_Init(&TIMER) != HAL_OK)
  {
    return FALSE;
  }
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&TIMER, &sMasterConfig) != HAL_OK)
  {
    return FALSE;
  }
  
  return TRUE;
}

void vMBPortTimersEnable()
{
  /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
  downcounter = timeout;
  HAL_TIM_Base_Start_IT(&TIMER);
}

void vMBPortTimersDisable()
{
  /* Disable any pending timers. */
  HAL_TIM_Base_Stop_IT(&TIMER);
}

//void prvvTIMERExpiredISR(void)
//{
//    (void) pxMBPortCBTimerExpired();
//}

//static void timer_timeout_ind(void* parameter)
//{
//    prvvTIMERExpiredISR();
//}
