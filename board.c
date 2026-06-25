#include "board.h"
#include <math.h>
#include "Delay.h"

/**********************************************************
***	Emm_V5.0步进闭环控制例程
***	编写作者：ZHANGDATOU
***	技术支持：张大头闭环伺服
***	淘宝店铺：https://zhangdatou.taobao.com
***	CSDN博客：http s://blog.csdn.net/zhangdatou666
***	qq交流群：262438510
**********************************************************/

/**
	*	@brief		外设时钟初始化
	*	@param		无
	*	@retval		无
	*/
void clock_init(void)
{
	// 使能GPIOA端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
}

/**
	*	@brief		gpio引脚初始化
	*	@param		无
	*	@retval		无
	*/
void gpio_init(void)
{
	// 初始化PA5(En) PA6(Stp) PA7(Dir)端口为推挽输出模式
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5	| GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 初始化PA5(En) PA6(Stp) PA7(Dir)端口为低电平输出
	GPIO_ResetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
}

/**
	*	@brief		板载初始化
	*	@param		无
	*	@retval		无
	*/
void board_init(void)
{
	clock_init();
	gpio_init();
}

void step_motor_rotate(float x)
{
	int steps = (int)(fabs(x) * 2); // 比例因子自己调试，x=1可能转1~5步
	if (steps == 0) return;

	// 设置方向
	if (x > 0) {
		GPIO_SetBits(GPIOA, GPIO_Pin_7);  // DIR=1，向右
	} else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_7); // DIR=0，向左
	}

	GPIO_ResetBits(GPIOA, GPIO_Pin_5); // EN = 0，开启使能

	for (int i = 0; i < steps; i++) {
		GPIO_SetBits(GPIOA, GPIO_Pin_6);   // STP 高
		Delay_us(200);                     // 保证时序，延时可调
		GPIO_ResetBits(GPIOA, GPIO_Pin_6); // STP 低
		Delay_us(200);                     // 一次脉冲完成
	}

	GPIO_SetBits(GPIOA, GPIO_Pin_5); // EN = 1，关闭使能（可选，看你驱动需求）
}

