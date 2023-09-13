/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
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
List_t TestList;  //测试用列表
ListItem_t ListItem1;  //测试用列表项 1
ListItem_t ListItem2;  //测试用列表项 2
ListItem_t ListItem3;  //测试用列表项 3
uint16_t task2Count = 0;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

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
  vListInitialise(&TestList);
  vListInitialiseItem(&ListItem1);
  vListInitialiseItem(&ListItem2); 
  vListInitialiseItem(&ListItem3);
  ListItem1.xItemValue=40;  //ListItem1 列表项值为 40
  ListItem2.xItemValue=60;  //ListItem2 列表项值为 60
  ListItem3.xItemValue=50;  //ListItem3 列表项值为 50
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

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of myTask03 */
  osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
  myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

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
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
  
  /* Infinite loop */
  for(;;)
  {
    if(task2Count == 0){
      printf("/**********列表和列表项地址***********/\r\n");
      printf("TestList %#x \r\n",(int)&TestList);
      printf("TestList->pxIndex %#x \r\n",(int)TestList.pxIndex);
      printf("TestList->xListEnd %#x \r\n",(int)(&TestList.xListEnd));
      printf("ListItem1 %#x \r\n",(int)&ListItem1);
      printf("ListItem2 %#x \r\n",(int)&ListItem2);
      printf("ListItem3 %#x \r\n",(int)&ListItem3);
      printf("/****************结束*****************/\r\n\r\n");
    }
    else if(task2Count == 1){
      vListInsert(&TestList,&ListItem1);  //插入列表项 ListItem1
      printf("/*********添加列表项 ListItem1**********/\r\n");
      printf("TestList->xListEnd->pxNext %#x \r\n",(int)(TestList.xListEnd.pxNext));
      printf("ListItem1->pxNext %#x \r\n",(int)(ListItem1.pxNext));
      printf("/**********前后向连接分割线***********/\r\n");
      printf("TestList->xListEnd->pxPrevious  %#x \r\n",(int)(TestList.xListEnd.pxPrevious));
      printf("ListItem1->pxPrevious %#x \r\n",(int)(ListItem1.pxPrevious));
      printf("/*****************结束****************/\r\n\r\n");
    }
    else if (task2Count == 2)
    {
      vListInsert(&TestList,&ListItem2);  //插入列表项 ListItem2
      printf("/*********添加列表项 ListItem2**********/\r\n");
      printf("TestList->xListEnd->pxNext %#x \r\n",(int)(TestList.xListEnd.pxNext));
      printf("ListItem1->pxNext %#x \r\n",(int)(ListItem1.pxNext));
      printf("ListItem2->pxNext %#x \r\n",(int)(ListItem2.pxNext));
      printf("/***********前后向连接分割线**********/\r\n");
      printf("TestList->xListEnd->pxPrevious  %#x \r\n",(int)(TestList.xListEnd.pxPrevious));
      printf("ListItem1->pxPrevious %#x \r\n",(int)(ListItem1.pxPrevious));
      printf("ListItem2->pxPrevious %#x \r\n",(int)(ListItem2.pxPrevious));
      printf("/****************结束*****************/\r\n\r\n");
    }
    else if (task2Count == 3)
    {
      vListInsert(&TestList,&ListItem3);  //插入列表项 ListItem3
      printf("/*********添加列表项 ListItem3**********/\r\n");
      printf("TestList->xListEnd->pxNext %#x \r\n",(int)(TestList.xListEnd.pxNext));
      printf("ListItem1->pxNext %#x \r\n",(int)(ListItem1.pxNext));
      printf("ListItem3->pxNext %#x \r\n",(int)(ListItem3.pxNext));
      printf("ListItem2->pxNext %#x \r\n",(int)(ListItem2.pxNext));
      printf("/**********前后向连接分割线***********/\r\n");
      printf("TestList->xListEnd->pxPrevious %#x \r\n",(int)(TestList.xListEnd.pxPrevious));
      printf("ListItem1->pxPrevious %#x \r\n",(int)(ListItem1.pxPrevious));
      printf("ListItem3->pxPrevious %#x \r\n",(int)(ListItem3.pxPrevious));
      printf("ListItem2->pxPrevious %#x \r\n",(int)(ListItem2.pxPrevious));
      printf("/*****************结束****************/\r\n\r\n");
    }
    else if (task2Count == 4)
    {
      uxListRemove(&ListItem3); //删除 ListItem3
      printf("/**********删除列表项 ListItem3*********/\r\n");
      printf("TestList->xListEnd->pxNext %#x \r\n",(int)(TestList.xListEnd.pxNext));
      printf("ListItem1->pxNext %#x \r\n",(int)(ListItem1.pxNext));
      printf("ListItem2->pxNext %#x \r\n",(int)(ListItem2.pxNext));
      printf("/***********前后向连接分割线**********/\r\n");
      printf("TestList->xListEnd->pxPrevious %#x \r\n",(int)(TestList.xListEnd.pxPrevious));
      printf("ListItem1->pxPrevious %#x \r\n",(int)(ListItem1.pxPrevious));
      printf("ListItem2->pxPrevious %#x \r\n",(int)(ListItem2.pxPrevious));
      printf("/****************结束*****************/\r\n\r\n");
    }
    else if (task2Count == 5)
    {
      // TestList.pxIndex=TestList.pxIndex->pxNext;//pxIndex 向后移一项，
      //这样 pxIndex 就会指向 ListItem1。
      vListInsertEnd(&TestList,&ListItem3); //列表末尾添加列表项 ListItem2
      printf("/******在末尾添加列表项 ListItem3*******/\r\n");
      printf("TestList->pxIndex %#x \r\n",(int)TestList.pxIndex);
      printf("TestList->xListEnd->pxNext %#x \r\n",(int)(TestList.xListEnd.pxNext));
      printf("ListItem2->pxNext %#x \r\n",(int)(ListItem2.pxNext));
      printf("ListItem1->pxNext %#x \r\n",(int)(ListItem1.pxNext));
      printf("ListItem3->pxNext %#x \r\n",(int)(ListItem3.pxNext));
      printf("/***********前后向连接分割线**********/\r\n");
      printf("TestList->xListEnd->pxPrevious %#x \r\n",(int)(TestList.xListEnd.pxPrevious));
      printf("ListItem2->pxPrevious %#x \r\n",(int)(ListItem2.pxPrevious));
      printf("ListItem1->pxPrevious %#x \r\n",(int)(ListItem1.pxPrevious));
      printf("ListItem3->pxPrevious %#x \r\n",(int)(ListItem3.pxPrevious));
      printf("/****************结束*****************/\r\n\r\n\r\n");
    }
    task2Count++;
    osDelay(100);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the myTask03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(500);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
