/**
 * @file		InterBoardCommunication_Task.c | InterBoardCommunication_Task.h
 * @brief
 * @author      ZhangJiaJia (Zhang643328686@163.com)
 * @date        2025-05-25 (创建日期)
 * @date        2025-05-27 (最后修改日期)
 * @version     0.1.0
 * @note
 * @warning
 * @license     WTFPL License
 *
 * @par 版本修订历史
 * @{
 *	@li 版本号: 0.1.0
 *      - 修订日期: 2025-05-27
 *      - 主要变更:
 *			- 完成了板间通信任务的数据包格式解析工作，搭建了板间通信任务的框架
 *      - 不足之处:
 *			- 数据包语义解析工作还没有完成
 *			- 功能状态量设置和处理不够完善
 *      - 作者: ZhangJiaJia
 * @}
 */


#include <stdint.h>							// C 语言标准库头文件，包含整数类型定义等
#include <string.h>							// C 语言标准库头文件，包含字符串处理函数等
#include "stm32f4xx_hal.h"					// main.h 头文件里面其实已经包含了这个头文件
#include "cmsis_os.h"						// FreeRTOS 头文件
#include "data_pool.h"						// 数据池头文件
#include "FreeRTOS.h"						// FreeRTOS 头文件
#include "main.h"							// HAL 库头文件
#include "task.h"							// FreeRTOS 头文件，但是我不知道要不要包含这个头文件
#include "InterBoardCommunication_Task.h"	// 板间通信任务头文件


uint8_t InterBoardCommunication_Rx_Buff[InterBoardCommunication_UART_RX_SIZE] = {0};


/**
 * @brief		板间通信任务入口函数
 * @param[in]	不知道是什么
 * @return		无
 * @note		无
 */
void InterBoardCommunication_Task(void* argument)
{
	uint8_t State = 0;				// 板间通信状态变量
	uint8_t DataPacketsSemanticsBuff[1] = { 0 };	// 数据包语义缓冲区

	osDelay(10);		// 习惯性上电延时

	State |= InterBoardCommunication_PowerOnSelfTest();	// 板间通信上电自检

	if (State != 0)
	{
		//vTaskSuspend(NULL);		// 如果自检失败，挂起任务
	}

	for (;;)
	{
		// 等待接收数据
		if (xQueueReceive(InterBoardCommunication_UART_RX_Port, InterBoardCommunication_Rx_Buff, pdTRUE) == pdPASS)
		{
			// 结构解析
			State |= InterBoardCommunication_StructureAnalysis(InterBoardCommunication_Rx_Buff, DataPacketsSemanticsBuff);

			// 语义解析
			State |= InterBoardCommunication_SemanticAnalysis(DataPacketsSemanticsBuff);
		}

		//taskYIELD();	// 触发任务调度
	}
}

/**
 * @brief		板间通信上电自检
 * @param[in]	无
 * @return		uint8_t 返回自检状态
 * @note		无
 */
uint8_t InterBoardCommunication_PowerOnSelfTest(void)
{
	uint8_t State = 0;

	if (xQueueReceive(InterBoardCommunication_UART_RX_Port, InterBoardCommunication_Rx_Buff, pdMS_TO_TICKS(1000)) == pdPASS)
	{
		uint8_t SelfTestData[7] = {0x55, 0xAA, 0x01, 0x00, 0xC4, 0x0D, 0x0A};		// 自检数据包

		if (memcmp(InterBoardCommunication_Rx_Buff, SelfTestData, sizeof(SelfTestData)) == 0)
		{
			// 自检成功
			// None		
		}
		else
		{
			State |= 0x02;	// 自检错误，错误原因：自检数据包不匹配
		}
	}
	else
	{
		State |= 0x01;	// 自检错误，错误原因：等待超时
	}

	return State;	// 返回自检状态
}

/**
 * @brief		板间通信数据包结构解析
 * @param[in]	Uart_Rx_Buff 接收缓冲区
 * @param[out]	DataPacketsSemanticsBuff 数据包语义缓冲区
 * @return		uint8_t 返回解析状态
 * @note		如果解析成功，返回 0，并更新 DataPacketsSemanticsBuff 为最新数据
 * @note		如果解析失败，返回 0x04，并不更新 DataPacketsSemanticsBuff
 * @note		CRC8校验的计算使用的是外部黑箱函数，校验位计算范围为 Uart_Rx_Buff[2] 到 Uart_Rx_Buff[3] 的数据长度（即数据内容长度为 2 字节），CRC8 校验值存储在 Uart_Rx_Buff[4] 中
 */
uint8_t InterBoardCommunication_StructureAnalysis(uint8_t* Uart_Rx_Buff, uint8_t* DataPacketsSemanticsBuff)
{
	uint8_t State = 0;
	uint8_t CRC8 = 0;	// CRC8校验变量

	// 检查包头
	if (Uart_Rx_Buff[0] == 0x55 && Uart_Rx_Buff[1] == 0xAA)
	{
		// None
	}
	else
	{
		State |= 0x04;	// 包头错误，但统一为数据包结构解析错误
		return State;	// 终止解析并返回状态
	}

	// 检查数据长度
	if (Uart_Rx_Buff[2] == 0x01)							
	{
		// None
	}
	else
	{
		State |= 0x04;	// 数据长度错误，但统一为数据包结构解析错误
		return State;	// 终止解析并返回状态
	}

	// CRC8校验计算
	CRC8 = serial_get_crc8_value((Uart_Rx_Buff + 2), 2);

	// 检查CRC8校验值
	if (CRC8 == Uart_Rx_Buff[4])
	{
		// None
	}
	else
	{
		State |= 0x04;	// CRC8校验错误，但统一为数据包结构解析错误
		return State;	// 终止解析并返回状态
	}

	// 检查包尾
	if (Uart_Rx_Buff[5] == 0x0D && Uart_Rx_Buff[6] == 0x0A)
	{
		// None
	}
	else
	{
		State |= 0x04;	// 包尾错误，但统一为数据包结构解析错误
		return State;	// 终止解析并返回状态
	}

	DataPacketsSemanticsBuff[0] = Uart_Rx_Buff[3];		// 提取数据内容

	return State;	// 返回解析状态
}

/**
 * @brief		板间通信数据包语义解析
 * @param[in]	DataPacketsSemanticsBuff 数据包语义缓冲区
 * @return		uint8_t 返回解析状态
 * @note		无
 */
uint8_t InterBoardCommunication_SemanticAnalysis(uint8_t* DataPacketsSemanticsBuff)
{
	uint8_t State = 0;

	switch (DataPacketsSemanticsBuff[0])
	{
		case 0x00:
			break;

		case 0x01:
			break;

		default:
			State |= 0x08;	// 语义解析错误，错误原因：未知解析命令
			break;
	}

	return State;	// 返回解析状态
}