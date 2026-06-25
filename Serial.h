#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>

#define RX_BUFFER_SIZE 100 // 定义接收缓冲区的最大长度

extern uint8_t Serial_RxData;
extern uint8_t Serial_RxFlag;
// uint8_t real_value = 0; // 这个变量可以移除或 repurpose

// 新增的全局变量
extern char RxBuffer[RX_BUFFER_SIZE]; // 接收缓冲区
extern uint8_t RxCounter ;         // 接收计数器
extern uint8_t FrameReady ;        // 帧接收完成标志

extern int last_num1; // 用于存储倒数第二个数字
extern int last_num2; // 用于存储最后一个数字

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
void Serial_SendNumber(uint32_t Number, uint8_t Length);
void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

void ParseFrame(void);

#endif
