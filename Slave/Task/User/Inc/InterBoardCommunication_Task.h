/**
 * @file		InterBoardCommunication_Task.c | InterBoardCommunication_Task.h
 * @brief
 * @author      ZhangJiaJia (Zhang643328686@163.com)
 * @date        2025-05-25 (��������)
 * @date        2025-05-27 (����޸�����)
 * @version     0.1.2
 * @note
 * @warning
 * @license     WTFPL License
 *
 * @par �汾�޶���ʷ
 * @{
 *  @li �汾��: 0.1.2
 *      - �޶�����: 2025-05-27
 *      - ��Ҫ���:
 *			- �����Ż��˳���
 *      - ����: ZhangJiaJia
 *
 *  @li �汾��: 0.1.1
 *      - �޶�����: 2025-05-27
 *      - ��Ҫ���:
 *			- �޸���CubeMX�����е�һЩ�޺�bug
 *      - ����: ZhangJiaJia
 *
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


#ifndef __InterBoardCommunication_Task_H
#define __InterBoardCommunication_Task_H


#include <stdint.h>


// �� InterBoardCommunication_Task �����е� State ��˵����
// 0x00�����ͨ�Ź�������
// 0x01�����ͨ�Ź����Լ���󣬴���ԭ�򣺵ȴ���ʱ
// 0x02�����ͨ�Ź����Լ���󣬴���ԭ���Լ����ݰ���ƥ��
// 0x04�����ͨ�Ź��ܽṹ�������󣬴���ԭ�����ݰ��ṹ��������
// 0x08�����ͨ�Ź�������������󣬴���ԭ��δ֪��������


// C���Բ���
#ifdef __cplusplus
extern "C" {
#endif

void InterBoardCommunication_Task(void* argument);


#ifdef __cplusplus
}
#endif


#endif

