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
 * File: $Id: portserial.c,v 1.60 2013/08/13 15:07:05 Armink $
 */

#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
#include "main.h"

/* ----------------------- Static variables ---------------------------------*/
extern UART_HandleTypeDef huart4;
UART_HandleTypeDef *serial = &huart4;

/* ----------------------- Defines ------------------------------------------*/
/* serial transmit event */
#define EVENT_SERIAL_TRANS_START    (1<<0)

/* ----------------------- static functions ---------------------------------*/
//static void prvvUARTTxReadyISR(void);
//static void prvvUARTRxISR(void);
//static rt_err_t serial_rx_ind(rt_device_t dev, rt_size_t size);
//static void serial_soft_trans_irq(void* parameter);

/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortSerialInit(UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits,
        eMBParity eParity)
{
    /**
     * set 485 mode receive and transmit control IO
     * @note MODBUS_SLAVE_RT_CONTROL_PIN_INDEX need be defined by user
     */
    /* set serial configure parameter */
    serial->Instance = UART4;
    serial->Init.BaudRate = ulBaudRate;
    serial->Init.StopBits = UART_STOPBITS_1;
  
    switch(eParity){
    case MB_PAR_NONE: {
        serial->Init.WordLength = UART_WORDLENGTH_8B;
        serial->Init.Parity = UART_PARITY_NONE;
        break;
    }
    case MB_PAR_ODD: {
        serial->Init.WordLength = UART_WORDLENGTH_9B;
        serial->Init.Parity = UART_PARITY_ODD;
        break;
    }
    case MB_PAR_EVEN: {
        serial->Init.WordLength = UART_WORDLENGTH_9B;
        serial->Init.Parity = UART_PARITY_EVEN;
        break;
    }
    }
    /* set serial configure */
    if (HAL_UART_Init(serial) != HAL_OK)
    {
      Error_Handler();
    }
    
    return TRUE;
}

void vMBPortSerialEnable(BOOL xRxEnable, BOOL xTxEnable)
{
    if (xRxEnable) {     
      /* enable RX interrupt */      
      __HAL_UART_ENABLE_IT(serial, UART_IT_RXNE);
      /* switch 485 to receive mode */
      HAL_GPIO_WritePin(RS485_1_Rs_GPIO_Port, RS485_1_Rs_Pin, GPIO_PIN_RESET);
    } else {
      /* switch 485 to transmit mode */ 
      HAL_GPIO_WritePin(RS485_1_Rs_GPIO_Port, RS485_1_Rs_Pin, GPIO_PIN_SET);
      /* disable RX interrupt */      
        __HAL_UART_DISABLE_IT(serial, UART_IT_RXNE);
    }
    
    if (xTxEnable) { 
      /* start serial transmit */
      __HAL_UART_ENABLE_IT(serial, UART_IT_TXE);
    } else {
      /* stop serial transmit */
      __HAL_UART_DISABLE_IT(serial, UART_IT_TXE);
    } 

}

void vMBPortClose(void)
{

}

BOOL xMBPortSerialPutByte(CHAR ucByte)
{
  HAL_StatusTypeDef s = HAL_UART_Transmit(serial, (uint8_t*)&ucByte, 1, 10);
    return TRUE;
}

BOOL xMBPortSerialGetByte(CHAR * pucByte)
{
  *pucByte = (uint8_t)(serial->Instance->DR & (uint8_t)0x00FF);
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
//    pxMBFrameCBTransmitterEmpty();
//}

/* 
 * Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
//void prvvUARTRxISR(void)
//{
//    pxMBFrameCBByteReceived();
//}

///**
// * Software simulation serial transmit IRQ handler.
// *
// * @param parameter parameter
// */
//static void serial_soft_trans_irq(void* parameter) {
//    rt_uint32_t recved_event;
//    while (1)
//    {
//        /* waiting for serial transmit start */
//        rt_event_recv(&event_serial, EVENT_SERIAL_TRANS_START, RT_EVENT_FLAG_OR,
//                RT_WAITING_FOREVER, &recved_event);
//        /* execute modbus callback */
//        prvvUARTTxReadyISR();
//    }
//}

///**
// * This function is serial receive callback function
// *
// * @param dev the device of serial
// * @param size the data size that receive
// *
// * @return return RT_EOK
// */
//static rt_err_t serial_rx_ind(rt_device_t dev, rt_size_t size) {
//    prvvUARTRxISR();
//    return RT_EOK;
//}
