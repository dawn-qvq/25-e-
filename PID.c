//#include "stm32f10x.h"
//#include "PID.h"

//// 增量式 PID 控制器结构体初始化
//void PID_Init(PID_Controller *pid, float kp, float ki, float kd)
//{
//    pid->Setpoint = 0.0f;      // 目标值（期望角度）
//    pid->Input = 0.0f;         // 当前输入（实际角度）
//    pid->Output = 0.0f;        // 最终输出（比如PWM）
//    pid->Kp = kp;
//    pid->Ki = ki;
//    pid->Kd = kd;
//    pid->LastError = 0.0f;     // e(k-1)
//    pid->PrevError = 0.0f;     // e(k-2)
//}

//// 增量式 PID 计算函数
//float PID_Compute(PID_Controller *pid, float input)
//{
//    float error = pid->Setpoint - input;  // 当前误差 e(k)

//    // 增量计算公式：
//    // ΔOutput = Kp*(e(k)-e(k-1)) + Ki*e(k) + Kd*(e(k)-2e(k-1)+e(k-2))
//    float delta_output = 
//        pid->Kp * (error - pid->LastError) +
//        pid->Ki * error +
//        pid->Kd * (error - 2 * pid->LastError + pid->PrevError);

//    pid->Output += delta_output;  // 累加增量作为新输出值

//    // 更新历史误差
//    pid->PrevError = pid->LastError;
//    pid->LastError = error;

//    return pid->Output;  // 返回新的输出值（例如用于设定 PWM 占空比）
//}

//// 设置当前输入值
//void PID_SetInput(PID_Controller *pid, float input)
//{
//    pid->Input = input;
//}

//// 设置目标设定值
//void PID_SetSetpoint(PID_Controller *pid, float setpoint)
//{
//    pid->Setpoint = setpoint;
//}


#include "stm32f10x.h"  
#include "PID.h"

// PID控制器初始化函数  
void PID_Init(PID_Controller *pid, float kp, float ki, float kd)  
{  
    pid->Setpoint = 0.0f;  
    pid->Input = 0.0f;  
    pid->Output = 0.0f;  
    pid->Kp = kp;  
    pid->Ki = ki;  
    pid->Kd = kd;  
    pid->LastError = 0.0f;  
    pid->Integral = 0.0f;  
}  
  
// PID计算函数  
float PID_Compute(PID_Controller *pid, float input)  
{  
    float error = pid->Setpoint - input;  
    pid->Integral += error;  
    float derivative = error - pid->LastError;  
    pid->Output = pid->Kp * error + pid->Ki * pid->Integral + pid->Kd * derivative;  
    pid->LastError = error;  
    return pid->Output;  
}  
  
// 更新PID输入的函数  
void PID_SetInput(PID_Controller *pid, float input)  
{  
    pid->Input = input;  
}  
  
// 设置PID设定值的函数  
void PID_SetSetpoint(PID_Controller *pid, float setpoint)  
{  
    pid->Setpoint = setpoint;  
}
