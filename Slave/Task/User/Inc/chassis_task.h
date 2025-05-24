#pragma once

#include "data_pool.h"
#include "catch.h"

#ifdef __cplusplus

typedef enum ROBOT_CRTL_E      //��״̬�������ڻ��ò��ϣ�����ʱ�����ᣬ˫��ͨѶ���ܻ�����, ���о�Ҳû�ã�������������
{
    OFF_MODE,   //����
    SHOOT_MODE, //����
    BALL_MODE,  //���˷�
}ROBOT_CRTL_E;

/*---------------------------------------------------------*/

typedef enum CHASSIS_CRTL_E     //����
{
    CHASSIS_OFF,                //����
    CHASSIS_COM_MODE,           //��ͨ�ƶ� 
    /*==========������===========*/
    CHASSIS_LOCK_RING_MODE,     //������ģʽ�������̲��ڻ��ϣ��������ӽ������ҿ�������Ļ�    
                                //             ���뻷�󣬵���ֻ�����Ż��ƶ�
    
    CHASSIS_TOGGLE_RING_MODE,   //���л�ģʽ    �����̲��ڻ��ϣ��������ӽ������ҿ�������Ļ�
                                //             ��ģʽ�£�ֻ���Ե���ǰ�����л�����
    CHASSIS_CALIBRA_MODE,       //У׼ģʽ������У׼ģʽ�������ģʽ�������Զ����������׼���ر��ϵİ壬��׼�󣬵��̲�������ң�زٿ�
                                //Ŀ����Ϊ�˼����಻��
    /*==========================*/

    /*=======�˶�ѧ���̷���======*/
    CHASSIS_LOCK_TARGET,

}CHASSIS_CRTL_E;


/*---------------------------------------------------------*/

typedef enum PITCH_CRTL_E       //����
{
    PITCH_RESET_MODE,           //���ã��ŵ���ͽǶ�
    PITCH_LOCK_MODE,            //�����Ƕ�����
    PITCH_HAND_MODE,            //�ֲٸ���
    PITCH_AUTO_MODE,            //�Զ�����
    PITCH_CATCH_MODE,           //Ħ��������ʱ�򣬸���̧��
}PITCH_CRTL_E;

/*---------------------------------------------------------*/

/*---------------------------------------------------------*/

typedef enum FRICTION_CTRL_E    //Ħ����
{
    FRICTION_OFF_MODE,          //Ħ���ֹر�
    FRICTION_ON_MODE,           //Ħ���ֿ���
}FRICTION_CTRL_E;

typedef enum SHOOT_CTRL_E        //�������
{
    SHOOT_OFF,                   //��λ
    SHOOT_ON,                    //����
}SHOOT_CTRL_E;

typedef enum DRIBBLE_CTRL_E     //����
{
    DRIBBLE_OFF,                //Ħ����ͣת
    SUCK_BALL_MODE,             //����,  ����Ǵ�צ������Ҫͬʱ����צ�رգ�ע���צ��ʱ��
    SPIT_BALL_MODE,             //����   ����Ǵ�צ������Ҫͬʱ����צ������ע�⿪צ��ʱ��
}DRIBBLE_CTRL_E;


typedef enum BALL_ANGLE_E       //��������Ƕ�
{
    DRIBBLE_ANGLE,  //����Ƕ�
    PLACE_ANGLE,    //����Ƕ�
}BALL_ANGLE_E;

typedef enum CATCH_BALL_E   //�������
{
    CATCH_ON,
    CATCH_OFF,
}CATCH_BALL_E;

typedef enum CAR_COMMUICA_E     //˫��ͨѶ   
{
    CAR_COMMUICA_OFF,       //
    CAR_COMMUICA_ON,        //
}CAR_COMMUICA_E;

/*---------------------------------------------------------*/

typedef enum LASER_CALIBRA_E    //����У׼
{
    LASER_CALIBRA_OFF,      //
    LASER_CALIBRA_ON,       //
}LASER_CALIBRA_E;

/*---------------------------------------------------------*/



void PidParamInit(void);

typedef struct CONTROL_T
{
    Robot_Twist_t       twist;
    ROBOT_CRTL_E        robot_crtl;         
    
    CHASSIS_CRTL_E      chassis_ctrl;       
    PITCH_CRTL_E        pitch_ctrl;        
    FRICTION_CTRL_E     friction_ctrl;      
    SHOOT_CTRL_E        shoot_ctrl;         
    DRIBBLE_CTRL_E      dribble_ctrl;       
    BALL_ANGLE_E        dri_angle_ctrl;     
    CATCH_BALL_E        catch_ball;
    CAR_COMMUICA_E      car_comm_ctrl;      
    LASER_CALIBRA_E     laser_ctrl;         

    uint8_t add_cnt=0;
}CONTROL_T;

extern "C" {
#endif
void Chassis_Task(void *pvParameters);


#ifdef __cplusplus
}

extern Catcher catcher;

#endif
