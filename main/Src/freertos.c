/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
//#include "user_mb_app.h"
#include "mb.h"
//#include "mb_m.h"
#include "mbport.h"
#include "DescriptMotorControl.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//адреса регистров modbus
#define REG_HOLDING_START 0x0000 
#define REG_HOLDING_NREGS 8
#define REG_SETTINGS_START REG_HOLDING_START + REG_HOLDING_NREGS//0x0008 
#define REG_SETTINGS_NREGS 16
//#define RECEIV_INPUT_START REG_SETTINGS_START + REG_SETTINGS_NREGS//0x0018 
//#define RECEIV_INPUT_NREGS 8

// карта регистров настройки
#define REG_BaudRate_START        REG_SETTINGS_START
#define REG_Mode_START            REG_BaudRate_START + 2
#define REG_SlaveAddress_START    REG_Mode_START + 1
#define REG_Role_START            REG_SlaveAddress_START + 1
#define REG_WriteInEEPROM_START   15

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
extern SPI_HandleTypeDef hspi1;
//extern USHORT   usMRegHoldBuf[MB_MASTER_TOTAL_SLAVE_NUM][M_REG_HOLDING_NREGS];

int start = 0;

//static USHORT usRegHoldingStart = REG_HOLDING_START;
//static USHORT usRegHoldingBuf[REG_HOLDING_NREGS] = {0};

//static USHORT usRegSettingsStart = REG_SETTINGS_START;
//static USHORT usRegSettingsBuf[REG_SETTINGS_NREGS] = {0};


/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId ModBusTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartModBusTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of ModBusTask */
  osThreadDef(ModBusTask, StartModBusTask, osPriorityNormal, 0, 256);
  ModBusTaskHandle = osThreadCreate(osThread(ModBusTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    if (start)
    {

    }
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartModBusTask */
/**
* @brief Function implementing the ModBusTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartModBusTask */
void StartModBusTask(void const * argument)
{
  /* USER CODE BEGIN StartModBusTask */
  eMBErrorCode eStatus = eMBInit( MB_RTU, 11, 3, 115200, MB_PAR_NONE );
  eStatus = eMBEnable();

  /* Infinite loop */
  for(;;)
  {
    eStatus = eMBPoll();

    osDelay(1);
  }
  /* USER CODE END StartModBusTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/*description https://www.freemodbus.org/api/group__modbus__registers.html*/
//0x04
eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    if(usAddress == 0 ){}
    else{usAddress--;} 

    eMBErrorCode    eStatus = MB_ENOERR;
//    int             iRegIndex;

//    if( ( usAddress >= RECEIV_INPUT_START ) && ( usAddress + usNRegs >= RECEIV_INPUT_START + RECEIV_INPUT_NREGS ) )
//    {
//        iRegIndex = ( int )( usAddress - ReceivInputStart );
//		
//        osMutexWait(mutex_modbusHandle, 10);
//        while( usNRegs > 0 )
//        {
//			// проверить правилность упаковки байтов
//            *pucRegBuffer++ = ( unsigned char )( ReceivInputBuf[iRegIndex] >> 8 );
//            *pucRegBuffer++ = ( unsigned char )( ReceivInputBuf[iRegIndex] & 0xFF );
//            iRegIndex++;
//            usNRegs--;
//        }
//        osMutexRelease(mutex_modbusHandle);		
//	//HAL_GPIO_TogglePin(User_LED_GPIO_Port, User_LED_Pin);
//    }
//    else
    {
	//HAL_GPIO_TogglePin(User_LED_GPIO_Port, User_LED_Pin);
        eStatus = MB_ENOREG;			
    }

    return eStatus;
}
//0x03 0x06 0x10
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    uint8_t CMD[5] = {0};
    volatile HAL_StatusTypeDef status;

    if(usAddress == 0 ){}
    else{usAddress--;} 

    eMBErrorCode    eStatus = MB_ENOERR;

//    if(( (int)usAddress >= REG_HOLDING_START ) && ( usAddress + usNRegs <= REG_HOLDING_START + REG_HOLDING_NREGS ))
//    {
////      eStatus = mbCB_inputsReg(pucRegBuffer, usAddress, usNRegs, eMode);
//    }
//    // продумать чтение и запись сразу всех регистров
//    else if (( usAddress >= usRegSettingsStart ) && ( usAddress + usNRegs <= REG_SETTINGS_START + REG_SETTINGS_NREGS) ) // настройка регистров modbus
//    {
////    eStatus = mbCB_eeprom(pucRegBuffer, usAddress, usNRegs, eMode);
//    }
//    else
//    {
//      eStatus = MB_ENOREG;			
//    }

    // переключатель чтение запись
    switch (eMode)
    {
      case MB_REG_READ:
      {	
        break;
      }
      case MB_REG_WRITE:
      {	
        //переключатель по адресам регистра
        switch (usAddress)
        {
          case 0:
          {	
            // команды для отправки на мотор
            switch (*(pucRegBuffer+1))
            {
              case START:
              {	
                CMD[0] = START;
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_RESET);
                status = HAL_SPI_Transmit(&hspi1, CMD, 5, 100);
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_SET);

                break;
              }
              case STOP:
              {	
                CMD[0] = STOP;
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_RESET);
                status = HAL_SPI_Transmit(&hspi1, CMD, 5, 100);
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_SET);

                break;
              }
              case LEFT:
              {	
                CMD[0] = LEFT;
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_RESET);
                status = HAL_SPI_Transmit(&hspi1, CMD, 5, 100);
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_SET);

                break;
              }
              case RIGHT:
              {	
                CMD[0] = RIGHT;
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_RESET);
                status = HAL_SPI_Transmit(&hspi1, CMD, 5, 100);
                HAL_GPIO_WritePin(CS1_1_GPIO_Port, CS1_1_Pin, GPIO_PIN_SET);

                break;
              }
              default:
              {	

                break;
              }
            }
            break;
          }
          case 1:
          {	
            break;
          }
          default:
          {	
            eStatus = MB_ENOREG;
            break;
          }
        }

        break;
      }
      default:
      {	
        eStatus = MB_EINVAL;
        break;
      }
    }
    
    return eStatus;
}

// 0x01 0x0f 0x05
eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    if(usAddress == 0 ){}
    else{usAddress--;} 

    return MB_ENOREG;
}
//0x02
eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    if(usAddress == 0 ){}
    else{usAddress--;} 

    return MB_ENOREG;
}      
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
