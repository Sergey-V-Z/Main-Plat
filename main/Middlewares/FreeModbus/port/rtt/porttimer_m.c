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
 * File: $Id: porttimer_m.c,v 1.60 2013/08/13 15:07:05 Armink add Master Functions$
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mb_m.h"
#include "mbport.h"

#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
/* ----------------------- Variables ----------------------------------------*/
extern TIM_HandleTypeDef htim5;
#define TIMER htim5
#define TIM TIM5
uint16_t timeout_m = 0;
uint16_t downcounter_m;

/* ----------------------- static functions ---------------------------------*/
//static void prvvTIMERExpiredISR(void);

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBMasterPortTimersInit(USHORT usTimeOut50us)
{
//    /* backup T35 ticks */
//    usT35TimeOut50us = usTimeOut50us;

//    rt_timer_init(&timer, "master timer",
//                   timer_timeout_m_ind, /* bind timeout_m callback function */
//                   RT_NULL,
//                   (50 * usT35TimeOut50us) / (1000 * 1000 / RT_TICK_PER_SECOND) + 1,
//                   RT_TIMER_FLAG_ONE_SHOT); /* one shot */
   
  TIM_MasterConfigTypeDef sMasterConfig;
 
  TIMER.Instance = TIM;
  TIMER.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 1000000) - 1;
  TIMER.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIMER.Init.Period = 50 - 1;
  
  timeout_m = usTimeOut50us;
  
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

void vMBMasterPortTimersT35Enable()
{
    //rt_tick_t timer_tick = (50 * usT35TimeOut50us) / (1000 * 1000 / RT_TICK_PER_SECOND);
    /* Enable the timer with the timeout_m passed to xMBPortTimersInit( ) */
    TIMER.Instance = TIM;
    TIMER.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 1000000) - 1;
    TIMER.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIMER.Init.Period = 50 - 1;
    
    if (HAL_TIM_Base_Init(&TIMER) != HAL_OK)
    {
      
    }

    downcounter_m = timeout_m;
    
    /* Set current timer mode, don't change it.*/
    vMBMasterSetCurTimerMode(MB_TMODE_T35);

    HAL_TIM_Base_Start_IT(&TIMER);
}

void vMBMasterPortTimersConvertDelayEnable()
{
    TIMER.Instance = TIM;
    TIMER.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 1000000) - 1;
    TIMER.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIMER.Init.Period = 1000 - 1;
    
    if (HAL_TIM_Base_Init(&TIMER) != HAL_OK)
    {}

    downcounter_m = MB_MASTER_DELAY_MS_CONVERT;

    /* Set current timer mode, don't change it.*/
    vMBMasterSetCurTimerMode(MB_TMODE_CONVERT_DELAY);

    HAL_TIM_Base_Start_IT(&TIMER);

}

void vMBMasterPortTimersRespondTimeoutEnable()
{

    TIMER.Instance = TIM;
    TIMER.Init.Prescaler = (HAL_RCC_GetPCLK1Freq() * 2 / 1000000) - 1;
    TIMER.Init.CounterMode = TIM_COUNTERMODE_UP;
    TIMER.Init.Period = 1000 - 1;
    
    if (HAL_TIM_Base_Init(&TIMER) != HAL_OK)
    {}

    downcounter_m = MB_MASTER_TIMEOUT_MS_RESPOND;

    /* Set current timer mode, don't change it.*/
    vMBMasterSetCurTimerMode(MB_TMODE_RESPOND_TIMEOUT);
      
    HAL_TIM_Base_Start_IT(&TIMER);  

}

void vMBMasterPortTimersDisable()
{
  /* Disable any pending timers. */
  HAL_TIM_Base_Stop_IT(&TIMER);
}

//void prvvTIMERExpiredISR(void)
//{
//    (void) pxMBMasterPortCBTimerExpired();
//}

//static void timer_timeout_m_ind(void* parameter)
//{
//    prvvTIMERExpiredISR();
//}

#endif
