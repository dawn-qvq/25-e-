//#ifndef __PID_H
//#define __PID_H

//// 增量式 PID 控制器结构体  
//typedef struct  
//{  
//    float Setpoint;     // 设定目标值  
//    float Input;        // 当前反馈值  
//    float Output;       // 控制输出值（累计增量）  

//    float Kp;           // 比例系数  
//    float Ki;           // 积分系数  
//    float Kd;           // 微分系数  

//    float LastError;    // e(k-1)，上一次误差  
//    float PrevError;    // e(k-2)，上上次误差（用于微分项）  
//} PID_Controller;  

//// 舵机 PID 控制器声明（全局）
//extern PID_Controller panPID;   // 水平轴（方位角）
//extern PID_Controller tiltPID;  // 垂直轴（俯仰角）

//// 函数声明
//void PID_Init(PID_Controller *pid, float kp, float ki, float kd);
//float PID_Compute(PID_Controller *pid, float input);
//void PID_SetInput(PID_Controller *pid, float input);
//void PID_SetSetpoint(PID_Controller *pid, float setpoint);

//#endif


#ifndef __PID_H
#define __PID_H
// PID控制器结构体  
typedef struct  
{  
    float Setpoint;     // 设定目标值  
    float Input;        // 当前反馈值  
    float Output;       // 控制输出  
    float Kp;           // 比例系数  
    float Ki;           // 积分系数  
    float Kd;           // 微分系数  
    float LastError;     // 上一次的误差  
    float Integral;     // 误差积分  
} PID_Controller;  
// 舵机PID控制器
extern PID_Controller panPID; // 水平轴（方位角）的PID控制器  
extern PID_Controller tiltPID; // 垂直轴（俯仰角）的PID控制器    
void PID_Init(PID_Controller *pid, float kp, float ki, float kd);
float PID_Compute(PID_Controller *pid, float input);
void PID_SetInput(PID_Controller *pid, float input); 
void PID_SetSetpoint(PID_Controller *pid, float setpoint);  	
#endif
