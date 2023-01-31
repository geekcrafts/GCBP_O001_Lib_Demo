#include <Arduino.h>
#include <Wire.h>
#include <GCPB_O6208.h>    //充电宝控制库引用
#include <LGFX_ESP32_GN.h> //LGFX显示库
#include <LovyanGFX.hpp>   //显示库配置
// 以下是界面素材资源
#include <font-arialblack48.h> //这个是字体
#include <background1.h>       //这个是背景
#include <background2.h>       //这个是背景
#include <background3.h>       //这个是背景

#include <anim/theme0_anim_png_0.h>
#include <anim/theme0_anim_png_1.h>
#include <anim/theme0_anim_png_2.h>
#include <anim/theme0_anim_png_3.h>
#include <anim/theme0_anim_png_4.h>
#include <anim/theme0_anim_png_5.h>

LGFX lcd;                // 主显示对象
LGFX_Sprite canvas;      // 内存画板
LGFX_Sprite draw_sprite; // 图片元素

// 背景色定义
int theme_0_background = lcd.color565(199, 196, 224);
int theme_1_background = lcd.color565(122, 182, 239);
int theme_2_background = lcd.color565(0, 0, 0);
// 文本颜色定义
int theme_0_textcolor = lcd.color565(255, 255, 255);
int theme_1_textcolor = lcd.color565(255, 255, 255);
int theme_2_textcolor = lcd.color565(255, 181, 90);
// 动图序号
int anim_index = 0;

// 显示初始化
void DisplayInit()
{
  // 显示库初始化函数
  lcd.init();
  // 设置屏幕显示方向
  lcd.setRotation(1);
  // 设置屏幕显示亮度
  lcd.setBrightness(50);
  // 初始化画布及清屏
  canvas.createSprite(240, 135);
  canvas.fillScreen(theme_1_background);
  canvas.pushSprite(&lcd, 0, 0);
}
// 显示背景
void DrawBackground_0()
{
  canvas.drawPng(background2, sizeof(background2), 0, 0);
}

// 显示背景
void DrawBackground_1()
{
  canvas.drawPng(background3, sizeof(background3), 0, 0);
}
// 刷新画布到屏幕
void RefreshDisplay()
{
  canvas.pushSprite(&lcd, 0, 0);
}

// 显示动图
void DrawAnim_0(int index)
{
  switch (index)
  {
  case 0:
    canvas.drawPng(theme0_anim_png_00, sizeof(theme0_anim_png_00), 0, 0);
    break;
  case 1:
    canvas.drawPng(theme0_anim_png_01, sizeof(theme0_anim_png_01),  0, 0);
    break;
  case 2:
    canvas.drawPng(theme0_anim_png_02, sizeof(theme0_anim_png_02),  0, 0);
    break;
  case 3:
    canvas.drawPng(theme0_anim_png_03, sizeof(theme0_anim_png_03),  0, 0);
    break;
  case 4:
    canvas.drawPng(theme0_anim_png_04, sizeof(theme0_anim_png_04), 0, 0);
    break;
  case 5:
    canvas.drawPng(theme0_anim_png_05, sizeof(theme0_anim_png_05),  0, 0);
    break;
  default:
    canvas.drawPng(theme0_anim_png_00, sizeof(theme0_anim_png_00),  0, 0);
    break;
  }
}

// 显示电量
void DrawBatteryCap_0(int cap)
{
  char draw_text[4];
  if (cap > 100)
    cap = 100;
  if (cap < 0)
    cap = 0;

  draw_sprite.createSprite(70, 70);
  draw_sprite.loadFont(font_arialblack_48);
  draw_sprite.fillSprite(0);
  draw_sprite.setTextDatum(CC_DATUM);          // 居中
  draw_sprite.setTextColor(theme_1_textcolor); // 设定字体颜色
  sprintf(draw_text, "%02d", cap);
  draw_sprite.drawString(draw_text, 35, 12);
  draw_sprite.pushSprite(&canvas, 145, 30, 0); // 显示在画布上
  draw_sprite.deleteSprite();
  draw_sprite.unloadFont();
}

// 显示电量

void DrawBatteryCap_1(int cap)
{
  char draw_text[4];
  if (cap > 100)
    cap = 100;
  if (cap < 0)
    cap = 0;

  draw_sprite.createSprite(70, 70);
  draw_sprite.loadFont(font_arialblack_48);
  draw_sprite.fillSprite(0);
  draw_sprite.setTextDatum(CC_DATUM);          // 居中
  draw_sprite.setTextColor(theme_1_textcolor); // 设定字体颜色
  sprintf(draw_text, "%02d", cap);
  draw_sprite.drawString(draw_text, 35, 12);
  draw_sprite.pushSprite(&canvas, 145, 45, 0); // 显示在画布上
  draw_sprite.deleteSprite();
  draw_sprite.unloadFont();
}

void setup()
{
  // 初始化串口
  Serial.setRxBufferSize(128);
  Serial.begin(115200);
  // 充电宝控制库初始化
  PowerBankInit();
  // 显示初始化
  DisplayInit();
}

void loop()
{
  // 充电宝控制库主循环函数
  PowerBankLoop();
  /*
  // 画背景
  DrawBackground_1();
  // 显示电量
   DrawBatteryCap_1(GetBatteryCap());
  // 画面刷新
  RefreshDisplay();
  delay(100);
  */
  //玉桂狗主题
  DrawBackground_0(); //画背景
 // anim_index++;     //动图序号循环
 // if (anim_index == 6)
 //   anim_index = 0;
//  DrawAnim_0(anim_index);  //画动图
  DrawBatteryCap_0(GetBatteryCap());  //显示电量
  RefreshDisplay();   //刷新显示
  // Serial.println(GetBatteryCap());
  delay(100);
}