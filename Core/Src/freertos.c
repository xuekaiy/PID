/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os2.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Task_Can.h"     /* CANTransmit() / CanSend_Type */
#include "Motor.h"        /* Arm_Motor / motor_t / FeedbackData，内部已含 PID.h */
#include "PID.h"  
#include "RemoteControl_Comm.h"        /* Pid_cal / PID_clear / pid_type */
#include "usart.h"
#include "Debug_Uart.h"    /* Debug_Printf()：调试串口 USART10 / PE3，115200 */

extern FDCAN_HandleTypeDef hfdcan1;
extern uint8_t  sendmessage[8];   /* main.c 里的全局 0x200 报文缓冲 */
extern int16_t  out;              /* main.c 里的全局电流指令 */
extern pid_type pid; 
      
/* main.c 里的全局速度环 PID */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Task_Init(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of defaultTask */
  

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task_Init */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_Init */
__weak void Task_Init(void *argument)
{
  /* USER CODE BEGIN Task_Init */
  
 

  for (;;)
  {
    float real = Arm_Motor[1].FeedbackData.RealSpeed;  /* 电机实际速度 */
    float pid_out;
    float dst = 300.0f;  /* 目标速度 */
    
    pid_out = Pid_cal(&pid, dst, real);  /* 速度环 PID 计算，返回电流指令 */
    
    if(fabs(pid_out) >= pid.MaxOut - 0.5f && pid.error[0] * pid_out > 0.0f )  /* 限幅，防止电流指令过大 */
    {
      pid.sum_error -= pid.error[0];
      pid.Iout      -= pid.ki * pid.error[0];
    }

    sendmessage[0] = (int16_t)pid_out >> 8;  /* 电流指令高字节 */
    sendmessage[1] = (int16_t)pid_out & 0xFF;  /* 电流指令低字节 */

    CANTransmit(&hfdcan1, 0x200, sendmessage);  /* 发送电流指令到电调 */
    
  }
  /* USER CODE END Task_Init */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

