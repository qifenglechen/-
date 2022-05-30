//***********************2018中国工程机器人大赛光电搬运机器人程序*******************************//

//********************************颜色部分**************************************
#include <TimerOne.h> //申明库文件
//把TCS3200颜色传感器各控制引脚连到Arduino数字端口
//VCC--灰色   GND--紫色和红色
#define S0    3  //(蓝色)      物体表面的反射光越强，TCS3002D内置振荡器产生的方波频率越高，
#define S1    4  //（绿色）S0和S1的组合决定输出信号频率比例因子，比例因子为2%
//比率因子为TCS3200传感器OUT引脚输出信号频率与其内置振荡器频率之比
#define S2    5 //（黄色）S2和S3的组合决定让红、绿、蓝，哪种光线通过滤波器
#define S3    6//（橙色）
#define OUT    2  //（棕色）TCS3200颜色传感器输出信号连接到Arduino中断0引脚，并引发脉冲信号中断
//在中断函数中记录TCS3200输出信号的脉冲个数
//#define LED    7  //控制TCS3200颜色传感器是否点亮LED灯
float g_SF[3];     //从TCS3200输出信号的脉冲数转换为RGB标准值的RGB比例因子
int   g_count = 0;  // 计算与反射光强相对应TCS3200颜色传感器输出信号的脉冲数
// 数组用于存储在1s内TCS3200输出信号的脉冲数，它乘以RGB比例因子就是RGB标准值
int   g_array[3];
int   g_flag = 0;   // 滤波器模式选择顺序标志

//判断颜色相关变量
int i = 0;

int y1;   //前进距离设置
int y2;

int k0;   //用于判断任务2中前往颜色区域是否存在物块
int k1;
int k2;
int k;

// 初始化TSC3200各控制引脚的输入输出模式
//设置TCS3002D的内置振荡器方波频率与其输出信号频率的比例因子为2%
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  //  pinMode(LED, OUTPUT);
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
}

//选择滤波器模式，决定让红、绿、蓝，哪种光线通过滤波器
void TSC_FilterColor(int Level01, int Level02)
{
  if (Level01 != 0)
    Level01 = HIGH;
  if (Level02 != 0)
    Level02 = HIGH;
  digitalWrite(S2, Level01);
  digitalWrite(S3, Level02);
}

//中断函数，计算TCS3200输出信号的脉冲数
void TSC_Count()
{
  g_count ++ ;
}

//定时器中断函数，每1s中断后，把该时间内的红、绿、蓝三种光线通过滤波器时，
//TCS3200输出信号脉冲个数分别存储到数组g_array[3]的相应元素变量中
void TSC_Callback()
{
  switch (g_flag)
  {
    case 0:
      Serial.println("->WB Start");
      TSC_WB(LOW, LOW);   //选择让红色光线通过滤波器的模式
      break;
    case 1:
      Serial.print("->Frequency R=");
      Serial.println(g_count);   //打印1s内的红光通过滤波器时，TCS3200输出的脉冲个数
      g_array[0] = g_count;    //存储1s内的红光通过滤波器时，TCS3200输出的脉冲个数
      TSC_WB(HIGH, HIGH);  //选择让绿色光线通过滤波器的模式
      break;
    case 2:
      Serial.print("->Frequency G=");
      Serial.println(g_count);   //打印1s内的绿光通过滤波器时，TCS3200输出的脉冲个数
      g_array[1] = g_count;    //存储1s内的绿光通过滤波器时，TCS3200输出的脉冲个数
      TSC_WB(LOW, HIGH);  //选择让蓝色光线通过滤波器的模式
      break;

    case 3:
      Serial.print("->Frequency B=");
      Serial.println(g_count);   //打印1s内的蓝光通过滤波器时，TCS3200输出的脉冲个数
      Serial.println("->WB End");
      g_array[2] = g_count;     //存储1s内的蓝光通过滤波器时，TCS3200输出的脉冲个数
      TSC_WB(HIGH, LOW);   //选择无滤波器的模式
      break;
    default:
      g_count = 0;     //计数值清零
      break;
  }
}
//设置反射光中红、绿、蓝三色光分别通过滤波器时如何处理数据的标志
//该函数被TSC_Callback( )调用
void TSC_WB(int Level0, int Level1)
{
  g_count = 0;   //计数值清零
  g_flag ++;     //输出信号计数标志
  TSC_FilterColor(Level0, Level1); //滤波器模式
  Timer1.setPeriod(1000000);     //设置输出信号脉冲计数时长1s
}

//***********************************************************************

//**************************舵机部分*************************************

int shengjiang_servo = 34; //定义数字接口34连接升降舵机信号线  黄色
int gouzi_servo_s = 35; //定义数字接口35连接升勾子上舵机信号线  绿色
int gouzi_servo_x = 36; //定义数字接口36连接勾子下舵机信号线  蓝色
int jiazi_servo = 37; //定义数字接口37连接夹子舵机信号线  紫色

int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
//***********************************************************************

//************************步进电机部分**********************************//
const int lzzCLK = 40; //黑
int DJ1State = LOW;
int lzzEN = 38; //蓝       //左轮
int DIR1 = LOW;
int lzzCW = 39; //绿

const int lzyCLK = 44;   //红
int DJ2State = LOW;
int lzyEN = 42;     //白      //右轮
int DIR2 = LOW;
int lzyCW = 43;     //棕

long previous1 = 0;
long previous2 = 0;

long v1 = 110; //时间直行、后退循迹速度
long v2 = 110;

long v5 = 160; //前后传感器循迹速度
long v6 = 160;

long v7 = 200; //转弯速度
long v8 = 200;

//偏移量修正值
int a = 45;
int b = 80;
int c = 115;

//*****************************************************************//

//******************************灰度传感**************************//
int QHDZ = 28; //前面左边传感器
int QHDY = 29; //前面右边传感器

int HHDZ = 26; //后面左边传感器
int HHDY = 27; //后面右边传感器

int HD1;
int HD2;
int HD3;
int HD4;
int HD5;
int HD6;

int HD7;  //后退
int HD8;
int HD9;  //后退
int HD10;
//*****************************************************************

#include "gouzi.h"
#include "jiazi.h"
#include "going.h"
#include "shengjiang.h"
#include "xunjia.h"
#include "colour.h"


//初始变量和引脚
void setup()
{
  //串行通讯
  Serial.begin (9600);

  //初始化各IO,模式为OUTPUT 输出模式
  pinMode(lzzEN, OUTPUT);
  pinMode(lzzCW, OUTPUT);
  pinMode(lzzCLK, OUTPUT);
  pinMode(lzyEN, OUTPUT);
  pinMode(lzyCW, OUTPUT);
  pinMode(lzyCLK, OUTPUT);

  //定义循迹模块为输入模式
  pinMode(14, INPUT);
  pinMode(15, INPUT);
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(24, INPUT);
  pinMode(25, INPUT);

  //设定舵机为输出模式
  pinMode(shengjiang_servo, OUTPUT); //设定舵机接口为输出接口
  pinMode(gouzi_servo_s, OUTPUT); //设定舵机接口为输出接口
  pinMode(gouzi_servo_x, OUTPUT); //设定舵机接口为输出接口
  pinMode(jiazi_servo, OUTPUT); //设定舵机接口为输出接口

  //设置灰度传感输出接口
  pinMode(QHDZ, INPUT);
  pinMode(QHDY, INPUT);

  pinMode(HHDZ, INPUT);
  pinMode(HHDY, INPUT);

  //************************************************************************************************
  //颜色识别部分
  TSC_Init();
  Timer1.initialize();   // defaulte is 1s
  Timer1.attachInterrupt(TSC_Callback); //设置定时器1的中断，中断调用函数为TSC_Callback()
  //设置TCS3200输出信号的上跳沿触发中断，中断源为3号引脚，中断调用函数为TSC_Count()，上升沿触发
  attachInterrupt(0, TSC_Count, RISING);
  //  digitalWrite(LED, HIGH);//点亮LED灯5
  // delay(4000); //延时4s，以等待被测物体红、绿、蓝三色在1s内的TCS3200输出信号脉冲计数


  //通过白平衡测试，计算得到白色物体RGB值255与1s内三色光脉冲数的RGB比例因子
  g_SF[0] = 0.10075;  //255.0/ g_array[0];    //红色光比例因子   //0.09020;
  g_SF[1] = 0.10204;  //255.0/ g_array[1];    //绿色光比例因子   //0.09763;
  g_SF[2] = 0.08444;  //255.0/ g_array[2];    //蓝色光比例因子   //0.08139;
  //打印白平衡后的红、绿、蓝三色的RGB比例因子
  Serial.println(g_SF[0], 5);
  Serial.println(g_SF[1], 5);
  Serial.println(g_SF[2], 5);
  //红、绿、蓝三色光分别对应的1s内TCS3200输出脉冲数乘以相应的比例因子就是RGB标准值
  //打印被测物体的RGB值
  for (int i = 0; i < 3; i++);
  Serial.println(int(g_array[i] * g_SF[i]));
}

//***************************************************************************************
//gouzi_servo1 控制勾子上下  值越小越往上 极限：上—10   下—110
//gouzi_servo2 控制勾子左右  值越大越往左 极限：左—165    右—1
//jiazi 控制夹子  值越大越开，推荐值 开：160，合35
//shengjiang 控制升降舵机  值越大越下 极限：上—105，下—155

//sj_xunji(100); 100对应约4cm
//go_time(5000);  5000对应约4cm
//***********************主程序开始***************************
void loop()
{
  //*************************初始化舵机位置*******************************
  gouzi_servo1(10);
  gouzi_servo2(100);
  jiazi(180);
  shengjiang(155);

  //####################################测试###########################################

  //######################任务1开始#################################//

  //*********************起点到C点夹C物块*****************************//
  sj_xunji(1600);
  qhd_xunji();
  js_go_time(5000);

  jiazi(122);    //夹取物块

  //*******************后退掉头回中心****************************//
  sj_xunji_houtui(300);
  houtui_hhd_xunji();     //白点回到中心
  sj_xunji_houtui(80);
  houtui_hhd_xunji();

  //***************************识别C处物块颜色*************************//

  yanseC();

  //***************************逻辑判断*******************************//

  //回到中心判断A处夹取的物块的颜色

  if (k1 == 1)  //如果C处物块是绿色
  {
    yanseA();   //识别去绿色区中夹取的A处物块颜色

    if (k0 == 2) //白色
    {
      right_135();             //朝向E区域

      sj_xunji(200);     //到达E点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块
      tingzhi(100);

      sj_xunji_houtui(300);
      houtui_hhd_xunji();     //白点回到中心
      sj_xunji_houtui(80);
      houtui_hhd_xunji();

    }

    else if (k0 == 3) //红色
    {
      right_90();             //朝向E区域

      sj_xunji(200);     //到达E点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块

      sj_xunji_houtui(300);
      houtui_hhd_xunji();     //白点回到中心
      sj_xunji_houtui(80);
      houtui_hhd_xunji();

    }

    else if (k0 == 4) //黑色
    {
      right_45();             //朝向E区域

      sj_xunji(200);     //到达E点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块
      tingzhi(100);


      sj_xunji_houtui(300);
      houtui_hhd_xunji();     //白点回到中心
      sj_xunji_houtui(80);
      houtui_hhd_xunji();

    }

    else if (k0 == 5) //蓝色
    {
      ;
    }


    yanseE();   //识别去蓝色区中夹取的E处物块颜色


    //回到中心判断E处夹取的物块的颜色

    if (k2 == 2) //白色
    {
      left_90();            //朝向F区域
    }

    else if (k2 == 3) //红色
    {
      left_135();             //朝向F区域
    }

    else if (k2 == 4) //黑色
    {
      left_180();             //朝向F区域
    }

    else if (k2 == 5) //蓝色
    {
      right_135();             //朝向F区域
    }
  }

  else if (k1 == 5) //如果C处物块是蓝色
  {

    yanseE();   //识别去蓝色区中夹取的E处物块颜色

    if (k2 == 2)
    {
      left_45();            //朝向A区域

      sj_xunji(200);     //到达A点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块
      tingzhi(100);

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);  //白点处回到中心
      houtui_hhd_xunji();
    }

    else if (k2 == 3)
    {
      left_90();             //朝向A区域

      sj_xunji(200);     //到达A点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块
      tingzhi(100);

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);  //白点处回到中心
      houtui_hhd_xunji();
    }

    else if (k2 == 4)
    {
      left_135();             //朝向A区域

      sj_xunji(200);     //到达A点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块
      tingzhi(100);

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);  //白点处回到中心
      houtui_hhd_xunji();
    }

    else if (k2 == 5)
    {
      left_180();             //朝向A区域

      sj_xunji(200);     //到达A点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块
      tingzhi(100);

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);  //白点处回到中心
      houtui_hhd_xunji();
    }

    yanseA();   //识别去绿色区中夹取的A处物块颜色


    if (k0 == 1)
    {
      left_45();             //朝向F区域
    }

    else if (k0 == 2)
    {
      left_90();            //朝向F区域
    }

    else if (k0 == 3)
    {
      left_135();             //朝向F区域
    }

    else if (k0 == 4)
    {
      left_180();             //朝向F区域
    }

    else if (k0 == 5)
    {
      right_135();             //朝向F区域
    }
  }

  else   //如果C处物块为白色 红色 黑色
  {
    //前往A处夹取物块

    if (k1 == 2)
    {
      left_45();            //朝向A区域
    }

    else if (k1 == 3)
    {
      left_90();             //朝向A区域
    }

    else if (k1 == 4)
    {
      left_135();             //朝向A区域
    }

    sj_xunji(200);     //到达A点
    qhd_xunji();
    js_go_time(5000);

    jiazi(122);         //夹取物块


    sj_xunji_houtui(300);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);  //白点处回到中心
    houtui_hhd_xunji();


    yanseA();        //识别A处物块的颜色


    if (k0 == 5) //如果A处物块是 蓝色
    {

      yanseE0();  //识别E0处物块的颜色

      if (k2 == 1) //如果E物块是绿色
      {
        left_45();            //朝向F区域
      }

      else if (k2 == 2) //如果E物块是白色
      {
        left_90();            //朝向F区域
      }

      else if (k2 == 3) //如果E处物块是红色
      {
        left_135();             //朝向F区域
      }

      else if (k2 == 4) //如果E处物块是黑色
      {
        left_180();             //朝向F区域
      }

    }

    else  if (k0 == 1) //如果A处物块是绿色
    {
      left_180();             //朝向E区域

      sj_xunji(200);  //到达E点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);    //回到中心
      houtui_hhd_xunji();

      yanseE0();        //颜色识别
    }

    else  if (k0 == 2) //如果A处物块是白色
    {
      right_135();             //朝向E区域

      sj_xunji(200);  //到达E点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);    //回到中心
      houtui_hhd_xunji();

      yanseE0();        //颜色识别
    }

    else if (k0 == 3) //如果A处物块是红色
    {
      right_90();             //朝向E区域

      sj_xunji(200);  //到达E点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);    //回到中心
      houtui_hhd_xunji();

      yanseE0();        //颜色识别
    }

    else if (k0 == 4) //如果A处物块是黑色
    {
      right_45();             //朝向E区域

      sj_xunji(200);  //到达E点
      qhd_xunji();
      js_go_time(5000);

      jiazi(122);         //夹取物块

      sj_xunji_houtui(300);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);    //回到中心
      houtui_hhd_xunji();

      yanseE0();        //颜色识别
    }


    if (k2 == 1)
    {
      left_45();             //朝向F区域
    }

    else if (k2 == 2)
    {
      left_90();            //朝向F区域
    }

    else if (k2 == 3)
    {
      left_135();             //朝向F区域
    }

    else if (k2 == 4)
    {
      left_180();             //朝向F区域
    }

    else if (k2 == 5)
    {
      right_135();             //朝向F区域
    }


  }



  //######################任务1结束#################################//


  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

  //######################任务2开始#################################//

  //**************************到达F区域夹A****************************//

  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(350); //@

  right_30();    //右转一点

  gouzi_servo2(130);  //@
  gouzi_servo1(103);
  gouzi_servo2(1);   //将物块A放进夹子
  gouzi_servo1(10);
  gouzi_servo2(110);

  jiazi(35);

  left_30();  //转回直线状态


  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();

  //*************************前往G区勾取物块A***************************//
  left_90();        //左转90度朝向G区

  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(385); //@


  gouzi_servo2(70);  //@   //勾子右转到物块上方     //勾取物块
  gouzi_servo1(105);   //勾子下降
  sj_xunji_houtui(50);  //后退一点

  shengjiang(102);      //夹子升起

  gouzi_servo2(1);   //将物块放进夹子
  gouzi_servo1(65);

  gouzi_servo2(30); //将物块推进夹子正下方
  gouzi_servo1(100);
  gouzi_servo2(5);
  gouzi_servo2(130);
  gouzi_servo1(10);

  shengjiang(135);  //下降一点
  jiazi(60);        //夹子打开一点
  shengjiang(157);   //完全下降
  jiazi(35);

  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();

  //********************颜色判断根据任务一******************************
  if (k0 == 1)
  {
    right_135();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();

    left_90();            //朝向F区域
  }

  else if (k0 == 2)
  {
    left_180();

    sj_xunji(500);
    qhd_xunji();

    jiazi(160);   //打开夹子

    sj_xunji_houtui(500);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 3)
  {
    left_135();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 4)
  {
    left_90();

    sj_xunji(500);
    qhd_xunji();

    jiazi(160);   //打开夹子

    sj_xunji_houtui(500);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 5)
  {
    left_45();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }


  //*************************朝向F区域***************************//
  if (k0 == 1)
  {
    left_45();
  }

  else if (k0 == 2)
  {
    left_90();
  }

  else if (k0 == 3)
  {
    left_135();
  }

  else if (k0 == 4)
  {
    left_180();
  }

  else if (k0 == 5)
  {
    right_135();
  }

  //**************************到达F区域夹B****************************//
  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(480); //@

  gouzi_servo2(62); //@
  gouzi_servo1(105);
  gouzi_servo2(1);   //将物块A放进夹子
  gouzi_servo1(10);
  gouzi_servo2(130);

  jiazi(35);


  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();

  //*************************前往G区勾取物块B***************************//
  left_90();        //左转90度朝向G区

  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(365);   //@

  right_30();  //右转一点

  gouzi_servo2(152);  //@  //勾子右转到物块上方     //勾取物块
  gouzi_servo1(105);   //勾子下降

  shengjiang(102);      //夹子升起

  gouzi_servo2(1);   //将物块放进夹子
  gouzi_servo1(60);

  gouzi_servo2(30); //将物块推进夹子正下方
  gouzi_servo1(100);
  gouzi_servo2(5);
  gouzi_servo2(130);
  gouzi_servo1(10);

  shengjiang(135);  //下降一点
  jiazi(70);        //夹子打开一点
  shengjiang(155);   //完全下降
  jiazi(35);

  left_30();   //回到直线状态

  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();


  //****************************颜色识别B*******************************//

  yanse2();

  //*************************朝向F区域***************************//
  if (k0 == 1)
  {
    left_45();
  }

  else if (k0 == 2)
  {
    left_90();
  }

  else if (k0 == 3)
  {
    left_135();
  }

  else if (k0 == 4)
  {
    left_180();
  }

  else if (k0 == 5)
  {
    right_135();
  }


  //**************************到达F区域夹C****************************//
  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(530); //@

  gouzi_servo2(80);  //@
  gouzi_servo1(105);
  gouzi_servo2(1);   //将物块C放进夹子
  gouzi_servo1(10);
  gouzi_servo2(130);

  jiazi(35);

  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();

  //*************************前往G区勾取物块C***************************//
  left_90();        //左转90度朝向G区

  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(425);  //@

  right_30();   //向右旋转一点

  gouzi_servo2(140);   //@  //勾子右转到物块上方     //勾取物块
  gouzi_servo1(105);   //勾子下降

  shengjiang(102);      //夹子升起

  gouzi_servo2(1);   //将物块放进夹子
  gouzi_servo1(65);

  gouzi_servo2(30); //将物块推进夹子正下方
  gouzi_servo1(100);
  gouzi_servo2(5);
  gouzi_servo2(130);
  gouzi_servo1(10);

  shengjiang(135);  //下降一点
  jiazi(65);        //夹子打开一点
  shengjiang(160);   //完全下降
  jiazi(35);    //夹子完全夹紧

  left_30();   //转到直线状态

  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();

  //********************颜色判断根据任务一******************************
  if (k0 == 1)
  {
    right_135();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();

    left_90();            //朝向F区域
  }

  else if (k0 == 2)
  {
    left_180();

    sj_xunji(500);
    qhd_xunji();

    jiazi(160);   //打开夹子

    sj_xunji_houtui(500);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 3)
  {
    left_135();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 4)
  {
    left_90();

    sj_xunji(500);
    qhd_xunji();

    jiazi(160);   //打开夹子

    sj_xunji_houtui(500);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 5)
  {
    left_45();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  //*************************朝向F区域***************************//
  if (k0 == 1)
  {
    left_45();
  }

  else if (k0 == 2)
  {
    left_90();
  }

  else if (k0 == 3)
  {
    left_135();
  }

  else if (k0 == 4)
  {
    left_180();
  }

  //**************************到达F区域夹E****************************//
  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(410); //@

  right_30();   //向右旋转一点

  gouzi_servo2(115);  //@
  gouzi_servo1(105);
  gouzi_servo2(1);   //将物块E放进夹子
  gouzi_servo1(10);
  gouzi_servo2(130);

  jiazi(35);

  left_30();   //向左转到直线状态


  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();

  //*************************前往G区勾取物块C***************************//
  left_90();        //左转90度朝向G区

  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(425);  //@


  gouzi_servo2(80);   //@  //勾子右转到物块上方     //勾取物块
  gouzi_servo1(105);   //勾子下降

  shengjiang(102);      //夹子升起

  gouzi_servo2(1);   //将物块放进夹子
  gouzi_servo1(65);

  gouzi_servo2(30); //将物块推进夹子正下方
  gouzi_servo1(100);
  gouzi_servo2(5);
  gouzi_servo2(130);
  gouzi_servo1(10);

  shengjiang(135);  //下降一点
  jiazi(65);        //夹子打开一点
  shengjiang(160);   //完全下降
  jiazi(35);    //夹子完全夹紧


  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();


  //********************颜色判断根据任务一******************************
  if (k0 == 1)
  {
    right_135();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();

    left_90();            //朝向F区域
  }

  else if (k0 == 2)
  {
    left_180();

    sj_xunji(500);
    qhd_xunji();

    jiazi(160);   //打开夹子

    sj_xunji_houtui(500);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 3)
  {
    left_135();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 4)
  {
    left_90();

    sj_xunji(500);
    qhd_xunji();

    jiazi(160);   //打开夹子

    sj_xunji_houtui(500);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }

  else if (k0 == 5)
  {
    left_45();

    sj_xunji(400);
    shengjiang(130);  //夹子上升一点

    qhd_xunji();
    sj_xunji(50);
    shengjiang(140); //夹子下降一点

    jiazi(75);         //夹子打开一点
    back_time(1500);   //后退一点
    shengjiang(160);   //夹子下降到底

    jiazi(35);         //夹子夹紧
    sj_xunji_houtui(60);
    jiazi(160);         //夹子打开

    sj_xunji_houtui(400);
    houtui_hhd_xunji();
    sj_xunji_houtui(50);   //回到中心
    houtui_hhd_xunji();
  }



  //*************************朝向F区域***************************//
  if (k0 == 1)
  {
    left_45();
  }

  else if (k0 == 2)
  {
    left_90();
  }

  else if (k0 == 3)
  {
    left_135();
  }

  else if (k0 == 4)
  {
    left_180();
  }

  else if (k0 == 5)
  {
    right_135();
  }


  //**************************到达F区域夹D****************************//
  sj_xunji(200);      //从中点到达F区外圈停止
  qhd_xunji();
  sj_js_xunji(605); //@

  gouzi_servo2(50);  //@
  gouzi_servo1(105);
  gouzi_servo2(1);   //将物块D放进夹子
  gouzi_servo1(10);
  gouzi_servo2(130);

  jiazi(35);

  jiazi(35);


  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();

  //*************************前往G区勾取物块D***************************//
  left_90();        //左转90度朝向G区

  sj_xunji(200);      //从中点到达G区外圈停止
  qhd_xunji();
  sj_js_xunji(475);  //@


  gouzi_servo2(60);   //@  //勾子右转到物块上方     //勾取物块
  gouzi_servo1(105);   //勾子下降

  shengjiang(102);      //夹子升起

  gouzi_servo2(1);   //将物块放进夹子
  gouzi_servo1(65);

  gouzi_servo2(30); //将物块推进夹子正下方
  gouzi_servo1(100);
  gouzi_servo2(5);
  gouzi_servo2(130);
  gouzi_servo1(10);

  shengjiang(135);  //下降一点
  jiazi(65);        //夹子打开一点
  shengjiang(160);   //完全下降
  jiazi(35);    //夹子完全夹紧


  //***************************回到中点*********************************//

  sj_xunji_houtui(500);
  houtui_hhd_xunji();
  sj_xunji_houtui(50);   //回到中心
  houtui_hhd_xunji();


  //************************颜色识别B****************************//

  yanse2();


  //*******************************************************************************************************************************************//
  //######################任务2结束#################################//


  //***********************回到起点*********************************//
  left_45();
  sj_xunji(1100);
  tingzhi(30000);

  //************************比赛结束**********************************//


}
