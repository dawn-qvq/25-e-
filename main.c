#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
#include "Serial.h"
#include "string.h"
#include "openmv.h"
#include "board.h"
#include <math.h>
uint8_t RxData;			//定义用于接收串口数据的变量
int openmv[7];//stm32接收数据数组
int16_t data1;
int16_t data2;
int16_t data3;
int16_t data4;
// 摄像头图像尺寸  
#define CAMERA_WIDTH 320  
#define CAMERA_HEIGHT 240  
// 假设的小球位置  
float ballX = CAMERA_WIDTH / 2; // 小球在图像中的x位置  
float ballY = CAMERA_HEIGHT / 2; // 小球在图像中的y位置
float x,y;
//uint8_t KeyNum;			//定义用于接收键码的变量
float Angle;			//定义角度变量
PID_Controller panPID;  
PID_Controller tiltPID;
float servo_rotation_value=0.0;// 舵机1（水平轴）初始角度
float servo_pitch_value=0.0; // 舵机2（垂直轴）初始角度
uint8_t servo_rotation_direction=0; // 舵机1方向翻转标志
uint8_t servo_pitch_direction=1; // 舵机2方向翻转标志
int main(void)
{
	/*模块初始化*/
	Servo_Init();		//舵机初始化
	board_init();//步进电机初始化
	//Key_Init();			//按键初始化
	OLED_Init();
	Serial_Init();
  // 初始化PID控制器  
	PID_Init(&panPID,  0.005, 0.0f, 0.0f); // 水平轴PID参数需要根据实际情况调整  
  PID_Init(&tiltPID, 0.005f, 0.0f, 0.003f); // 垂直轴PID参数需要根据实际情况调整  
 
	PID_SetSetpoint(&panPID,CAMERA_WIDTH/2);
	PID_SetSetpoint(&tiltPID,CAMERA_HEIGHT/2);
	Angle=90;
	while (1)
	{
		OLED_ShowNum(3, 0 ,y,3);
//		OLED_ShowSignedNum(1,0,ballX,3);
//		OLED_ShowSignedNum(2,0,ballX,3);
    // 假设这里更新了小球的位置  
				   if (FrameReady)
        {
            FrameReady = 0; // 清除标志位
            ParseFrame();   // 调用解析函数
					
					OLED_ShowNum(1, 0 ,last_num1,3);
					OLED_ShowNum(2, 0, last_num2,3);
					
				data1=(uint8_t)last_num1;
				data2=(uint8_t)last_num2;
            // 在这里您就可以使用 last_num1 和 last_num2 了
            // 例如，可以再通过串口打印出来进行验证
					
//            Serial_Printf("Last two numbers are: %d, %d\r\n", last_num1, last_num2);
        }
        // ...  
    // 计算舵机应该调整的角度
				
		ballX=(uint8_t)data1;
		ballY=(uint8_t)data2;
    float deltaX = ballX - CAMERA_WIDTH / 2;  
    float deltaY = ballY - CAMERA_HEIGHT / 2;  
		if(ballX==0){
			ballX=160;
			ballY=120;
		}
		//ballX = (ballX > MAX_X) ? MAX_X : ((ballX < MIN_X) ? MIN_X : ballX);  
    // 使用PID计算误差（图像像素）  
    x=PID_Compute(&panPID, ballX);  
    y=PID_Compute(&tiltPID, ballY);
		//x=(float)(deltaX)*0.005;
		//y=(float)(deltaY)*0.005;
//		if (!servo_rotation_direction) { // 如果servo_rotation_direction为false  
//        x = -x; // x取反  
//    }  
    if (!servo_pitch_direction) { // 如果servo_pitch_direction为false  
        y = y; // y取反  
    }  
    //在限位内，驱动X轴，Y轴移动 
//    if (MIN_ANGLE_X < servo_rotation_value + x && servo_rotation_value + x < MAX_ANGLE_X) {  
//        servo_rotation_value += x; // 更新旋转值  
////				Servo_SetAngle1(90+servo_rotation_value); // 控制水平轴舵机  
//    }  
		if (fabs(x) >= 1.0f)  // 加入死区限制
{
	if(x<-4)
	{
		x=-4;
	}
	if(x>4)
	{
		x=4;
	}
    step_motor_rotate(x); // 控制水平步进电机
}


    if (MIN_ANGLE_Y < servo_pitch_value + y && servo_pitch_value + y < MAX_ANGLE_Y) { // 假设俯仰值也有类似的有效范围检查  
        servo_pitch_value += y; // 更新俯仰值  
				Servo_SetAngle2(servo_pitch_value); // 控制水平轴舵机  
    }
    Delay_ms(5);		
	}
}
