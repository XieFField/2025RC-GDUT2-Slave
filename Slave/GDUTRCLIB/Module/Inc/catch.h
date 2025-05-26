#ifndef CATCH_H
#define CATCH_H

#include "motor.h"
#include "pid.h"
#include "speed_plan.h"

#ifdef __cplusplus
extern "C" {
#endif 

#ifdef __cplusplus
}
#endif

class Catcher : public PidTimer
{
public:
    Catcher(float max_angle, float min_angle)   //??
    {
        catcher_max_angle = max_angle;
        catcher_min_angle = min_angle;
    }

    Motor_C620 CatcherMotor[1] = {Motor_C620(1)}; //??ID?1

    bool Pid_Param_Init(float Kp, float Ki, float Kd, float Integral_Max, float OUT_Max, float DeadZone)
    {
        PidCatcherSpd.PID_Param_Init(Kp,Ki,Kd,Integral_Max,OUT_Max,DeadZone);
    }

    bool Pid_Mode_Init(float LowPass_error, float LowPass_d_err, bool D_of_Current, bool Imcreatement_of_Out)
    {
        PidCatcherSpd.PID_Mode_Init(LowPass_error,LowPass_d_err,D_of_Current,Imcreatement_of_Out);
    }

    
    void Catcher_Open(float open_angle);    //??
    void Catcher_Close(float close_angle);

    void CatcherMotorCtrl();
private:
    float catcher_max_angle = 0.0f, catcher_min_angle = 0.0f;

    PID PidCatcherSpd, PidCatcherPos;
    
    bool Reset();   //????
    bool machine_init_ = false; //?????
};

#endif
