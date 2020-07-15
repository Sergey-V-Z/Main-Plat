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
 * File: $Id: portserial_m.c,v 1.60 2013/08/13 15:07:05 Armink add Master Functions $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "main.h"

#if MB_MASTER_RTU_ENABLED > 0 || MB_MASTER_ASCII_ENABLED > 0
/* ----------------------- Static variables ---------------------------------*/
extern UART_HandleTypeDef huart2;
UART_HandleTypeDef *serial_m = &huart2;
/* ----------------------- Defines ------------------------------------------*/
/* serial_m transmit event */
#define EVENT_SERIAL_TRANS_START    (1<<0)

/* ----------------------- static functions ---------------------------------*/


/* ----------------------- Start implementation -----------------------------*/
BOOL xMBMasterPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity)
{
    /**
     * set 485 mode receive and transmit control IO
     * @note MODBUS_MASTER_RT_CONTROL_PIN_INDEX need be defined by user
     */

    /* set serial_m configure parameter */
    serial_m->Instance = USART2;
    serial_m->Init.BaudRate = ulBaudRate;
    serial_m->Init.StopBits = UART_STOPBITS_1;
  
    switch(eParity){
    case MB_PAR_NONE: {
        serial_m->Init.WordLength = UART_WORDLENGTH_8B;
        serial_m->Init.Parity = UART_PARITY_NONE;
        break;
    }
    case MB_PAR_ODD: {
        serial_m->Init.WordLength = UART_WORDLENGTH_9B;
        serial_m->Init.Parity = UART_PARITY_ODD;
        break;
    }
    case MB_PAR_EVEN: {
        serial_m->Init.WordLength = UART_WORDLENGTH_9B;
        serial_m->Init.Parity = UART_PARITY_EVEN;
        break;
    }
    }
    /* set serial_m configure */
    if (HAL_UART_Init(serial_m) != HAL_OK)
    {
      Error_Handler();
    }

    return TRUE;
}

void vMBMasterPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
    if (xRxEnable) {     
      /* enable RX interrupt */      
      __HAL_UART_ENABLE_IT(serial_m, UART_IT_RXNE);
      /* switch 485 to receive mode */
      HAL_GPIO_WritePin(DE_M_GPIO_Port, DE_M_Pin, GPIO_PIN_RESET);
    } else {
      /* switch 485 to transmit mode */ 
      HAL_GPIO_WritePin(DE_M_GPIO_Port, DE_M_Pin, GPIO_PIN_SET);
      /* disable RX interrupt */      
        __HAL_UART_DISABLE_IT(serial_m, UART_IT_RXNE);
    }
    
    if (xTxEnable) { 
      /* start serial_m transmit */
      __HAL_UART_ENABLE_IT(serial_m, UART_IT_TXE);
    } else {
      /* stop serial_m transmit */
      __HAL_UART_DISABLE_IT(serial_m, UART_IT_TXE);
    } 

}

void vMBMasterPortClose(void)
{
    //serial_m->parent.close(&(serial_m->parent));
}

BOOL xMBMasterPortSerialPutByte(CHAR ucByte)
{
  HAL_StatusTypeDef s = HAL_UART_Transmit(serial_m, (uint8_t*)&ucByte, 1, 10);
//    serial_m->parent.write(&(serial_m->parent), 0, &ucByte, 1);
    return TRUE;
}

BOOL xMBMasterPortSerialGetByte(CHAR * pucByte)
{
  *pucByte = (uint8_t)(serial_m->Instance->DR & (uint8_t)0x00FF);
//    serial_m->parent.read(&(serial_m->parent), 0, pucByte, 1);
    return TRUE;
}

/* 
 * Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
//void prvvUARTTxReadyISR(void)
//{
//    pxMBMasterFrameCBTransmitterEmpty();
//}

/* 
 * Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
//void prvvUARTRxISR(void)
//{
//    pxMBMasterFrameCBByteReceived();
//}

///**
// * Software simulation serial_m transmit IRQ handler.
// *
// * @param parameter parameter
// */
//static void serial_m_soft_trans_irq(void* parameter) {
//    rt_uint32_t recved_event;
//    while (1)
//    {
//        /* waiting for serial_m transmit start */
//        rt_event_recv(&event_serial_m, EVENT_SERIAL_TRANS_START, RT_EVENT_FLAG_OR,
//                RT_WAITING_FOREVER, &recved_event);
//        /* execute modbus callback */
//        prvvUARTTxReadyISR();
//    }
//}

///**
// * This function is serial_m receive callback function
// *
// * @param dev the device of serial_m
// * @param size the data size that receive
// *
// * @return return RT_EOK
// */
//static rt_err_t serial_m_rx_ind(rt_device_t dev, rt_size_t size) {
//    prvvUARTRxISR();
//    return RT_EOK;
//}

#endif
