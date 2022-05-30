//************************在A处判断颜色************************//
void yanseA()
{
  g_flag = 0;
  //每获得一次被测物体RGB颜色值需时2s
  delay(4000);
  //打印出被测物体RGB颜色值
  for (int i = 0; i < 3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));
  if (   ( (g_array[0] * g_SF[0]) > 200)  && ( (g_array[1] * g_SF[1]) > 200) && ((g_array[2] * g_SF[2]) > 200 ) ) //白色
  {
    k0 = 2;
    Serial.print("yanse=");
    Serial.println("bai");

    right_45();   //朝向白色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();

  }
  else  if ( ( (g_array[0] * g_SF[0]) > (g_array[1] * g_SF[1]) ) && ( (g_array[0] * g_SF[0]) > (g_array[2] * g_SF[2]) ) && (g_array[0] * g_SF[0]) > 120) //红色
  {
    k0 = 3;
    Serial.print("yanse=");
    Serial.println("hong");

    right_90();   //朝向红色色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();


  }
  else  if (((g_array[2] * g_SF[2]) > (g_array[1] * g_SF[1]))  && ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0]) ) ) //蓝色
  {
    k0 = 5;
    Serial.print("yanse=");
    Serial.println("lan");

    left_180();   //朝向蓝色区域

    sj_xunji(100);   //到达E点
    qhd_xunji();

    gouzi_servo2(30);  //勾取E处物块
    gouzi_servo1(110);
    gouzi_servo2(120);
    gouzi_servo1(110);

    sj_xunji(100);   //到达颜色区域
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();

    gouzi_servo2(1);   //将物块放进夹子
    gouzi_servo1(10);
    gouzi_servo2(100);

    jiazi(122);    //夹取物块

  }
  else  if (((g_array[0] * g_SF[0]) < 70)  && ((g_array[1] * g_SF[1]) < 70) && ((g_array[2] * g_SF[2]) < 70)) //黑色
  {
    k0 = 4;
    Serial.print("yanse=");
    Serial.println("hei");

    right_135();   //朝向黑色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();

  }

  else  if ( ((g_array[2] * g_SF[2]) < (g_array[1] * g_SF[1])) && ( ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0])  ) ) && ( (g_array[1] * g_SF[1]) > 70 && (g_array[1] * g_SF[1]) < 200 )) //绿色
  {
    k0 = 1;
    Serial.print("yanse=");
    Serial.println("lv");

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();

  }
}



//************************在A0处判断颜色************************//
void yanseA0()
{
  g_flag = 0;
  //每获得一次被测物体RGB颜色值需时2s
  delay(4000);
  //打印出被测物体RGB颜色值
  for (int i = 0; i < 3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));
  if (   ( (g_array[0] * g_SF[0]) > 200)  && ( (g_array[1] * g_SF[1]) > 200) && ((g_array[2] * g_SF[2]) > 200 ) ) //白色
  {
    k0 = 2;
    Serial.print("yanse=");
    Serial.println("bai");

    right_45();   //朝向白色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();


  }
  else  if ( ( (g_array[0] * g_SF[0]) > (g_array[1] * g_SF[1]) ) && ( (g_array[0] * g_SF[0]) > (g_array[2] * g_SF[2]) ) && (g_array[0] * g_SF[0]) > 120) //红色
  {
    k0 = 3;
    Serial.print("yanse=");
    Serial.println("hong");

    right_90();   //朝向红色色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();


  }
  else  if (((g_array[2] * g_SF[2]) > (g_array[1] * g_SF[1]))  && ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0]) ) ) //蓝色
  {
    k0 = 5;
    Serial.print("yanse=");
    Serial.println("lan");

    left_180();   //朝向蓝色区域

    sj_xunji(100);   //到达E点
    qhd_xunji();

    gouzi_servo2(30);  //勾取E处物块
    gouzi_servo1(110);
    gouzi_servo2(120);
    gouzi_servo1(110);

    sj_xunji(100);   //到达颜色区域
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();

    gouzi_servo2(1);   //将物块放进夹子
    gouzi_servo1(10);
    gouzi_servo2(100);

    jiazi(122);    //夹取物块

  }
  else  if (((g_array[0] * g_SF[0]) < 70)  && ((g_array[1] * g_SF[1]) < 70) && ((g_array[2] * g_SF[2]) < 70)) //黑色
  {
    k0 = 4;
    Serial.print("yanse=");
    Serial.println("hei");

    right_135();   //朝向黑色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();

  }

  else  if ( ((g_array[2] * g_SF[2]) < (g_array[1] * g_SF[1])) && ( ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0])  ) ) && ( (g_array[1] * g_SF[1]) > 70 && (g_array[1] * g_SF[1]) < 200 )) //绿色
  {
    k0 = 1;
    Serial.print("yanse=");
    Serial.println("lv");

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();

  }
}

//************************在C处判断颜色************************//
void yanseC()
{
  g_flag = 0;
  //每获得一次被测物体RGB颜色值需时2s
  delay(4000);
  //打印出被测物体RGB颜色值
  for (int i = 0; i < 3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));

  if (   ( (g_array[0] * g_SF[0]) > 200)  && ( (g_array[1] * g_SF[1]) > 200) && ((g_array[2] * g_SF[2]) > 200 ) ) //白色
  {
    k1 = 2;
    Serial.print("yanse=");
    Serial.println("hei");
    left_45();   //朝向白色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if ( ( (g_array[0] * g_SF[0]) > (g_array[1] * g_SF[1]) ) && ( (g_array[0] * g_SF[0]) > (g_array[2] * g_SF[2]) ) && (g_array[0] * g_SF[0]) > 120) //红色
  {
    k1 = 3;
    Serial.print("yanse=");
    Serial.println("hong");

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子


    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();
  }

  else  if (((g_array[2] * g_SF[2]) > (g_array[1] * g_SF[1]))  && ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0]) ) ) //蓝色
  {
    k1 = 5;
    Serial.print("yanse=");
    Serial.println("lan");

    right_90();   //朝向蓝色区域

    sj_xunji(100);   //到达E点
    qhd_xunji();

    gouzi_servo2(30);  //勾取E处物块
    gouzi_servo1(110);
    gouzi_servo2(120);
    gouzi_servo1(110);

    sj_xunji(100);   //到达颜色区域
    qhd_xunji();

    jiazi(180);   //打开夹子


    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();


    gouzi_servo2(1);   //将物块放进夹子
    gouzi_servo1(10);
    gouzi_servo2(130);

    jiazi(122);    //夹取物块
    tingzhi(100);

  }

  else  if (((g_array[0] * g_SF[0]) < 70)  && ((g_array[1] * g_SF[1]) < 70) && ((g_array[2] * g_SF[2]) < 70)) //黑色
  {
    k1 = 4;
    Serial.print("yanse=");
    Serial.println("hei");
    right_45();   //朝向黑色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if ( ((g_array[2] * g_SF[2]) < (g_array[1] * g_SF[1])) && ( ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0])  ) ) && ( (g_array[1] * g_SF[1]) > 70 && (g_array[1] * g_SF[1]) < 200 )) //绿色
  {
    k1 = 1;
    Serial.print("yanse=");
    Serial.println("lv");

    left_90();   //朝向绿色区域

    sj_xunji(100);   //到达E点
    qhd_xunji();

    gouzi_servo2(30);  //勾取E处物块
    gouzi_servo1(110);
    gouzi_servo2(120);
    gouzi_servo1(110);

    sj_xunji(200);   //到达颜色区域
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();


    gouzi_servo2(1);   //将物块放进夹子
    gouzi_servo1(10);
    gouzi_servo2(130);

    jiazi(122);    //夹取物块
    tingzhi(100);

  }
}

//************************在E处判断颜色************************//
void yanseE()
{
  g_flag = 0;
  //每获得一次被测物体RGB颜色值需时2s
  delay(4000);
  //打印出被测物体RGB颜色值
  for (int i = 0; i < 3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));
  if (   ( (g_array[0] * g_SF[0]) > 200)  && ( (g_array[1] * g_SF[1]) > 200) && ((g_array[2] * g_SF[2]) > 200 ) ) //白色
  {
    k2 = 2;
    Serial.print("yanse=");
    Serial.println("bai");

    left_135();   //朝向白色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if ( ( (g_array[0] * g_SF[0]) > (g_array[1] * g_SF[1]) ) && ( (g_array[0] * g_SF[0]) > (g_array[2] * g_SF[2]) ) && (g_array[0] * g_SF[0]) > 120) //红色
  {
    k2 = 3;
    Serial.print("yanse=");
    Serial.println("hong");

    left_90();   //朝向红色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if (((g_array[2] * g_SF[2]) > (g_array[1] * g_SF[1]))  && ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0]) ) ) //蓝色
  {
    k2 = 5;
    Serial.print("yanse=");
    Serial.println("lan");

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();


  }

  else  if (((g_array[0] * g_SF[0]) < 70)  && ((g_array[1] * g_SF[1]) < 70) && ((g_array[2] * g_SF[2]) < 70)) //黑色
  {
    k2 = 4;
    Serial.print("yanse=");
    Serial.println("hei");

    left_45();   //朝向黑色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if ( ((g_array[2] * g_SF[2]) < (g_array[1] * g_SF[1])) && ( ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0])  ) ) && ( (g_array[1] * g_SF[1]) > 70 && (g_array[1] * g_SF[1]) < 200 )) //绿色
  {

    k2 = 1;
    Serial.print("yanse=");
    Serial.println("lv");

    left_180();   //朝向绿色区域

    sj_xunji(800);   //到达A点
    qhd_xunji();

    gouzi_servo2(30);  //勾取A处物块
    gouzi_servo1(110);
    gouzi_servo2(120);
    gouzi_servo1(110);

    sj_xunji(100);   //到达颜色区域
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //颜色区域回到中心
    houtui_hhd_xunji();


    gouzi_servo2(1);   //将物块放进夹子
    gouzi_servo1(10);
    gouzi_servo2(130);

    jiazi(135);    //夹取物块
    tingzhi(100);
  }
}


//************************在E0处判断颜色************************//
void yanseE0()
{
  g_flag = 0;
  //每获得一次被测物体RGB颜色值需时2s
  delay(4000);
  //打印出被测物体RGB颜色值
  for (int i = 0; i < 3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));
  if (   ( (g_array[0] * g_SF[0]) > 200)  && ( (g_array[1] * g_SF[1]) > 200) && ((g_array[2] * g_SF[2]) > 200 ) ) //白色
  {
    k2 = 2;
    Serial.print("yanse=");
    Serial.println("bai");

    left_135();   //朝向白色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if ( ( (g_array[0] * g_SF[0]) > (g_array[1] * g_SF[1]) ) && ( (g_array[0] * g_SF[0]) > (g_array[2] * g_SF[2]) ) && (g_array[0] * g_SF[0]) > 120) //红色
  {
    k2 = 3;
    Serial.print("yanse=");
    Serial.println("hong");

    left_90();   //朝向红色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if (((g_array[2] * g_SF[2]) > (g_array[1] * g_SF[1]))  && ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0]) ) ) //蓝色
  {
    k2 = 5;
    Serial.print("yanse=");
    Serial.println("lan");


    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();


  }

  else  if (((g_array[0] * g_SF[0]) < 70)  && ((g_array[1] * g_SF[1]) < 70) && ((g_array[2] * g_SF[2]) < 70)) //黑色
  {
    k2 = 4;
    Serial.print("yanse=");
    Serial.println("hei");

    left_45();   //朝向黑色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();

  }

  else  if ( ((g_array[2] * g_SF[2]) < (g_array[1] * g_SF[1])) && ( ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0])  ) ) && ( (g_array[1] * g_SF[1]) > 70 && (g_array[1] * g_SF[1]) < 200 )) //绿色
  {

    k2 = 1;
    Serial.print("yanse=");
    Serial.println("lv");

    left_180();   //朝向绿色区域

    sj_xunji(800);
    qhd_xunji();

    jiazi(180);   //打开夹子

    sj_xunji_houtui(600);
    houtui_hhd_xunji();
    sj_xunji_houtui(80);   //回到中心
    houtui_hhd_xunji();
  }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&任务2&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&//

void yanse2()
{
  g_flag = 0;

  //每获得一次被测物体RGB颜色值需时4s
  delay(4000);
  //打印出被测物体RGB颜色值
  for (int i = 0; i < 3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));
  if (   ( (g_array[0] * g_SF[0]) > 200)  && ( (g_array[1] * g_SF[1]) > 200) && ((g_array[2] * g_SF[2]) > 200 ) ) //白色
  {
    k = 2;
    Serial.print("yanse=");
    Serial.println("bai");

    if (k == k0 || k == k1 || k == k2)
    {
      left_180();
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

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }

    else
    {
      left_180();
      sj_xunji(500);   //到达颜色区域
      qhd_xunji();

      jiazi(156);         //夹子打开

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }
  }
  else  if ( ( (g_array[0] * g_SF[0]) > (g_array[1] * g_SF[1]) ) && ( (g_array[0] * g_SF[0]) > (g_array[2] * g_SF[2]) ) && (g_array[0] * g_SF[0]) > 120) //红色
  {
    k = 3;
    Serial.print("yanse=");
    Serial.println("hong");
    if (k == k0 || k == k1 || k == k2)
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

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }

    else
    {
      left_135();
      sj_xunji(500);   //到达颜色区域
      qhd_xunji();

      jiazi(160);         //夹子打开

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();


    }
  }
  else  if (((g_array[2] * g_SF[2]) > (g_array[1] * g_SF[1]))  && ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0]) ) ) //蓝色
  {
    k = 5;
    Serial.print("yanse=");
    Serial.println("lan");
    if (k == k0 || k == k1 || k == k2)
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

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }
    else
    {
      left_45();
      sj_xunji(500);   //到达颜色区域
      qhd_xunji();

      jiazi(160);         //夹子打开

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }
  }


  else  if (((g_array[0] * g_SF[0]) < 80)  && ((g_array[1] * g_SF[1]) < 80) && ((g_array[2] * g_SF[2]) < 80)) //黑色
  {
    k = 4;
    Serial.print("yanse=");
    Serial.println("hei");

    if (k == k0 || k == k1 || k == k2)
    {
      left_90();
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

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }
    else
    {
      left_90();

      sj_xunji(500);   //到达颜色区域
      qhd_xunji();

      jiazi(160);         //夹子打开

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }
  }

  else  if ( ((g_array[2] * g_SF[2]) < (g_array[1] * g_SF[1])) && ( ( (g_array[1] * g_SF[1]) > (g_array[0] * g_SF[0])  ) ) && ( (g_array[1] * g_SF[1]) > 70 && (g_array[1] * g_SF[1]) < 200 )) //绿色
  {
    k = 1;
    Serial.print("yanse=");
    Serial.println("lv");

    if (k == k0 || k == k1 || k == k2)
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

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }
    else
    {
      right_135();

      sj_xunji(500);   //到达颜色区域
      qhd_xunji();

      jiazi(160);         //夹子打开

      sj_xunji_houtui(600);
      houtui_hhd_xunji();
      sj_xunji_houtui(80);   //颜色区域回到中心
      houtui_hhd_xunji();

    }
  }

}
