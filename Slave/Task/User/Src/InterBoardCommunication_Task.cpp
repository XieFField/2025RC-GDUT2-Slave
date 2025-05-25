


#include <stdint.h>							// C 语言标准库头文件
#include "stm32f4xx_hal.h"					// main.h 头文件里面其实已经包含了这个头文件
#include "cmsis_os.h"						// FreeRTOS 头文件
#include "data_pool.h"						// 数据池头文件
#include "FreeRTOS.h"						// FreeRTOS 头文件
#include "main.h"							// HAL 库头文件
#include "task.h"							// FreeRTOS 头文件，但是我不知道要不要包含这个头文件
#include "InterBoardCommunication_Task.h"	// 板间通信任务头文件


void InterBoardCommunication_Task(void* argument)
{

}