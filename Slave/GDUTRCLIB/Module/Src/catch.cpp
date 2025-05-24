/**
 * @file catch.cpp
 * @author   Wu Jia
 * @brief ????
 * @version 0.2
 * @date 2025-05-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "catch.h"

bool Catcher :: Reset()
{
    static int start_time=get_systemTick()/1000;
    if(get_systemTick()/1000 - start_time > 1000)
    {
        CatcherMotor.encoder_offset = CatcherMotor.get_encoder();
        CatcherMotor.encoder_offset = CatcherMotor.get_encoder();
        machine_init_ = true;
    }
    else
    { 
        CatcherMotor.Out = -200;
        CatcherMotor.Out = 2000;
        machine_init_ = false;
    }
}

void Catcher :: CatcherMotorCtrl()
{
    Motor_SendMsgs(&hcan1, CatcherMotor);
}

void Catcher :: Catcher_Open(float open_angle)
{
    if(!machine_init_)
    {
        Reset();
        PidCatcherPos.PID_Mode_Init(0.1,0.1,true,false);
        PidCatcherPos.PID_Param_Init(10, 0, 0.2, 120, 480, 0.2);
    }

    if(open_angle > catcher_max_angle)
            open_angle = catcher_max_angle;
        else if(open_angle < catcher_min_angle)
            open_angle = 0;
        else{;}

        PidCatcherPos.target = open_angle;
        PidCatcherPos.current = CatcherMotor.get_angle();

        PidCatcherSpd.target = PidCatcherPos.Adjust();
        PidCatcherSpd.current = CatcherMotor.get_speed();
        CatcherMotor.Out = PidCatcherSpd.Adjust();

}

void Catcher :: Catcher_Close(float close_angle)
{
    if(!machine_init_)
    {
        Reset();
        PidCatcherPos.PID_Mode_Init(0.1,0.1,true,false);
        PidCatcherPos.PID_Param_Init(10, 0, 0.2, 120, 480, 0.2);
    }

    if(close_angle > catcher_max_angle)
            close_angle = catcher_max_angle;
        else if(close_angle < catcher_min_angle)
            close_angle = 0;
        else{;}

        PidCatcherPos.target = close_angle;
        PidCatcherPos.current = CatcherMotor.get_angle();

        PidCatcherSpd.target = PidCatcherPos.Adjust();
        PidCatcherSpd.current = CatcherMotor.get_speed();
        CatcherMotor.Out = PidCatcherSpd.Adjust();
}
