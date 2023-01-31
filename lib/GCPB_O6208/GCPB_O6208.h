#ifndef _GCPB_O6208_H
#define _GCPB_O6208_H

void PowerBankInit();    // 控制库初始化
void PowerBankLoop();     // 控制库主循环函数

int GetBatteryCap();    //当前电量获取
void SetIdleSleepTime(int loopTime);   //设置空闲多少次主循环后待机，默认是150次，如果一秒钟循环五次的话，那么30秒后待机
uint8_t GetButtonStatus();  //获取按键状态 bit0:长按键 bit1:双击按键 bit2:短按键
uint8_t GetChargeStatus(); //bit6: 0:放电关 1:放电开 bit7: 0:充电关 1:充电开

#endif