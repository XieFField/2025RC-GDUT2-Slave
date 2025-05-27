/**
 * @file		InterBoardCommunication_Task.c | InterBoardCommunication_Task.h
 * @brief
 * @author      ZhangJiaJia (Zhang643328686@163.com)
 * @date        2025-05-25 (��������)
 * @date        2025-05-27 (����޸�����)
 * @version     0.1.0
 * @note
 * @warning
 * @license     WTFPL License
 *
 * @par �汾�޶���ʷ
 * @{
 *	@li �汾��: 0.1.0
 *      - �޶�����: 2025-05-27
 *      - ��Ҫ���:
 *			- ����˰��ͨ����������ݰ���ʽ������������˰��ͨ������Ŀ��
 *      - ����֮��:
 *			- ���ݰ��������������û�����
 *			- ����״̬�����úʹ���������
 *      - ����: ZhangJiaJia
 * @}
 */


#include <stdint.h>							// C ���Ա�׼��ͷ�ļ��������������Ͷ����
#include <string.h>							// C ���Ա�׼��ͷ�ļ��������ַ�����������
#include "stm32f4xx_hal.h"					// main.h ͷ�ļ�������ʵ�Ѿ����������ͷ�ļ�
#include "cmsis_os.h"						// FreeRTOS ͷ�ļ�
#include "data_pool.h"						// ���ݳ�ͷ�ļ�
#include "FreeRTOS.h"						// FreeRTOS ͷ�ļ�
#include "main.h"							// HAL ��ͷ�ļ�
#include "task.h"							// FreeRTOS ͷ�ļ��������Ҳ�֪��Ҫ��Ҫ�������ͷ�ļ�
#include "InterBoardCommunication_Task.h"	// ���ͨ������ͷ�ļ�


uint8_t InterBoardCommunication_Rx_Buff[InterBoardCommunication_UART_RX_SIZE] = {0};


/**
 * @brief		���ͨ��������ں���
 * @param[in]	��֪����ʲô
 * @return		��
 * @note		��
 */
void InterBoardCommunication_Task(void* argument)
{
	uint8_t State = 0;				// ���ͨ��״̬����
	uint8_t DataPacketsSemanticsBuff[1] = { 0 };	// ���ݰ����建����

	osDelay(10);		// ϰ�����ϵ���ʱ

	State |= InterBoardCommunication_PowerOnSelfTest();	// ���ͨ���ϵ��Լ�

	if (State != 0)
	{
		//vTaskSuspend(NULL);		// ����Լ�ʧ�ܣ���������
	}

	for (;;)
	{
		// �ȴ���������
		if (xQueueReceive(InterBoardCommunication_UART_RX_Port, InterBoardCommunication_Rx_Buff, pdTRUE) == pdPASS)
		{
			// �ṹ����
			State |= InterBoardCommunication_StructureAnalysis(InterBoardCommunication_Rx_Buff, DataPacketsSemanticsBuff);

			// �������
			State |= InterBoardCommunication_SemanticAnalysis(DataPacketsSemanticsBuff);
		}

		//taskYIELD();	// �����������
	}
}

/**
 * @brief		���ͨ���ϵ��Լ�
 * @param[in]	��
 * @return		uint8_t �����Լ�״̬
 * @note		��
 */
uint8_t InterBoardCommunication_PowerOnSelfTest(void)
{
	uint8_t State = 0;

	if (xQueueReceive(InterBoardCommunication_UART_RX_Port, InterBoardCommunication_Rx_Buff, pdMS_TO_TICKS(1000)) == pdPASS)
	{
		uint8_t SelfTestData[7] = {0x55, 0xAA, 0x01, 0x00, 0xC4, 0x0D, 0x0A};		// �Լ����ݰ�

		if (memcmp(InterBoardCommunication_Rx_Buff, SelfTestData, sizeof(SelfTestData)) == 0)
		{
			// �Լ�ɹ�
			// None		
		}
		else
		{
			State |= 0x02;	// �Լ���󣬴���ԭ���Լ����ݰ���ƥ��
		}
	}
	else
	{
		State |= 0x01;	// �Լ���󣬴���ԭ�򣺵ȴ���ʱ
	}

	return State;	// �����Լ�״̬
}

/**
 * @brief		���ͨ�����ݰ��ṹ����
 * @param[in]	Uart_Rx_Buff ���ջ�����
 * @param[out]	DataPacketsSemanticsBuff ���ݰ����建����
 * @return		uint8_t ���ؽ���״̬
 * @note		��������ɹ������� 0�������� DataPacketsSemanticsBuff Ϊ��������
 * @note		�������ʧ�ܣ����� 0x04���������� DataPacketsSemanticsBuff
 * @note		CRC8У��ļ���ʹ�õ����ⲿ���亯����У��λ���㷶ΧΪ Uart_Rx_Buff[2] �� Uart_Rx_Buff[3] �����ݳ��ȣ����������ݳ���Ϊ 2 �ֽڣ���CRC8 У��ֵ�洢�� Uart_Rx_Buff[4] ��
 */
uint8_t InterBoardCommunication_StructureAnalysis(uint8_t* Uart_Rx_Buff, uint8_t* DataPacketsSemanticsBuff)
{
	uint8_t State = 0;
	uint8_t CRC8 = 0;	// CRC8У�����

	// ����ͷ
	if (Uart_Rx_Buff[0] == 0x55 && Uart_Rx_Buff[1] == 0xAA)
	{
		// None
	}
	else
	{
		State |= 0x04;	// ��ͷ���󣬵�ͳһΪ���ݰ��ṹ��������
		return State;	// ��ֹ����������״̬
	}

	// ������ݳ���
	if (Uart_Rx_Buff[2] == 0x01)							
	{
		// None
	}
	else
	{
		State |= 0x04;	// ���ݳ��ȴ��󣬵�ͳһΪ���ݰ��ṹ��������
		return State;	// ��ֹ����������״̬
	}

	// CRC8У�����
	CRC8 = serial_get_crc8_value((Uart_Rx_Buff + 2), 2);

	// ���CRC8У��ֵ
	if (CRC8 == Uart_Rx_Buff[4])
	{
		// None
	}
	else
	{
		State |= 0x04;	// CRC8У����󣬵�ͳһΪ���ݰ��ṹ��������
		return State;	// ��ֹ����������״̬
	}

	// ����β
	if (Uart_Rx_Buff[5] == 0x0D && Uart_Rx_Buff[6] == 0x0A)
	{
		// None
	}
	else
	{
		State |= 0x04;	// ��β���󣬵�ͳһΪ���ݰ��ṹ��������
		return State;	// ��ֹ����������״̬
	}

	DataPacketsSemanticsBuff[0] = Uart_Rx_Buff[3];		// ��ȡ��������

	return State;	// ���ؽ���״̬
}

/**
 * @brief		���ͨ�����ݰ��������
 * @param[in]	DataPacketsSemanticsBuff ���ݰ����建����
 * @return		uint8_t ���ؽ���״̬
 * @note		��
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
			State |= 0x08;	// ����������󣬴���ԭ��δ֪��������
			break;
	}

	return State;	// ���ؽ���״̬
}