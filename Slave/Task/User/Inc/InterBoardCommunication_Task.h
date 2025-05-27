/**
 * @file		InterBoardCommunication_Task.c | InterBoardCommunication_Task.h
 * @brief
 * @author      ZhangJiaJia (Zhang643328686@163.com)
 * @date        2025-05-25 (创建日期)
 * @date        2025-05-27 (最后修改日期)
 * @version     0.1.2
 * @note
 * @warning
 * @license     WTFPL License
 *
 * @par 版本修订历史
 * @{
 *  @li 版本号: 0.1.2
 *      - 修订日期: 2025-05-27
 *      - 主要变更:
 *			- 少量优化了程序
 *      - 作者: ZhangJiaJia
 *
 *  @li 版本号: 0.1.1
 *      - 修订日期: 2025-05-27
 *      - 主要变更:
 *			- 修复了CubeMX配置中的一些无害bug
 *      - 作者: ZhangJiaJia
 *
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


#ifndef __InterBoardCommunication_Task_H
#define __InterBoardCommunication_Task_H


#include <stdint.h>


// 对 InterBoardCommunication_Task 函数中的 State 的说明：
// 0x00：板间通信功能正常
// 0x01：板间通信功能自检错误，错误原因：等待超时
// 0x02：板间通信功能自检错误，错误原因：自检数据包不匹配
// 0x04：板间通信功能结构解析错误，错误原因：数据包结构解析错误
// 0x08：板间通信功能语义解析错误，错误原因：未知解析命令


// C语言部分
#ifdef __cplusplus
extern "C" {
#endif

void InterBoardCommunication_Task(void* argument);


#ifdef __cplusplus
}
#endif


#endif

