//**********************时间直行***********************************//

void go_time(long n)
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < n; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji1();
    digitalWrite(lzyEN, LOW);
    dianji2();

  }
}

//**********************减速时间直行***********************************//

void js_go_time(long n)
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < n; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();

  }
}


//****************************时间后退********************************//
void back_time(long n)
{
  digitalWrite(lzzCW, HIGH); //转向控制
  digitalWrite(lzyCW, LOW);

  for (long i = 0; i < n; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji1();
    digitalWrite(lzyEN, LOW);
    dianji2();
  }
}


//**********************循迹中的直行***********************************//

void go()
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < 100; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji1();
    digitalWrite(lzyEN, LOW);
    dianji2();
  }
}

void back()
{
  digitalWrite(lzzCW, HIGH); //转向控制
  digitalWrite(lzyCW, LOW);

  for (long i = 0; i < 100; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji1();
    digitalWrite(lzyEN, LOW);
    dianji2();

  }
}

//**********************循迹中减速的直行（速度120）***********************************//

void go1()
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < 100 ; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();

  }
}


//**********************左转弯******************************//

void left_30()
{
  digitalWrite(lzzCW, HIGH); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < 25500; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji7();
    digitalWrite(lzyEN, LOW);
    dianji8();
  }
}

void left_45()
{
  digitalWrite(lzzCW, HIGH); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < 28000; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }
}

void left_90()
{
  digitalWrite(lzzCW, HIGH); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < 57000; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }
}

void left_135()
{
  digitalWrite(lzzCW, HIGH); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < 84500; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }
}


void left_180()
{
  digitalWrite(lzzCW, HIGH); //转向控制
  digitalWrite(lzyCW, HIGH);

  for (long i = 0; i < 110000; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }


}
//**********************右转弯******************************//

void right_30()
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, LOW);

  for (long i = 0; i < 25500; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }
}

void right_45()
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, LOW);

  for (long i = 0; i < 28000; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }
}


void right_90()
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, LOW);

  for (long i = 0; i < 57000; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }


}


void right_135()
{
  digitalWrite(lzzCW, LOW); //转向控制
  digitalWrite(lzyCW, LOW);

  for (long i = 0; i < 84500; i++)
  {
    digitalWrite(lzzEN, LOW);
    dianji5();
    digitalWrite(lzyEN, LOW);
    dianji6();
  }

}
//***************************车辆停止***********************//
void tingzhi(int t)
{
  //停止
  digitalWrite(lzzEN, HIGH);
  digitalWrite(lzyEN, HIGH);
  delay(t);
}

//*********************时间循迹*************************//
void sj_xunji(long n)
{
  for (long i = 0; i < n; i++)
  {
    //读取数字口高低电平信号至变量HD
    HD1 = digitalRead(14);
    HD2 = digitalRead(15);
    HD3 = digitalRead(16);
    HD4 = digitalRead(17);
    HD5 = digitalRead(18);
    HD6 = digitalRead(19);

    //中间在黑线
    if (HD1 == 1 && HD2 == 1 && HD3 == 0 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v1 = 110 + a;
      v2 = 110;
      go();

    }


    else if ( HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 0 && HD5 == 1 && HD6 == 1)
    {
      v1 = 110;
      v2 = 110 + a;
      go();

    }

    else if ( HD1 == 1 && HD2 == 0 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v1 = 110 + b;
      v2 = 110;
      go();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 0 && HD6 == 1)
    {
      v1 = 110;
      v2 = 110 + b;
      go();
    }

    else if ( HD1 == 0 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v1 = 110 + c;
      v2 = 110;
      go();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 0)
    {
      v1 = 110;
      v2 = 110 + c;
      go();
    }

    else
    {
      v1 = 110;
      v2 = 110;
      go();
    }
  }
}

//*********************时间后退循迹*************************//
void sj_xunji_houtui(long n)
{
  for (long i = 0; i < n; i++)
  {
    //读取数字口高低电平信号至变量HD
    HD7 = digitalRead(22);   //后右内
    HD8 = digitalRead(23);   //后左内
    HD9 = digitalRead(24);   //后右外
    HD10 = digitalRead(25); //后左外

    if (HD9 == 0 && HD7 == 0 && HD8 == 1 && HD10 == 0)
    {
      v1 = 110 + b;
      v2 = 110;
      back();
    }

    else if (HD9 == 0 && HD7 == 1 && HD8 == 0 && HD10 == 0)
    {
      v1 = 110;
      v2 = 110 + b;
      back();
    }

    else if (HD9 == 1 && HD7 == 0 && HD8 == 0 && HD10 == 0)
    {
      v1 = 110 + c;
      v2 = 110;
      back();
    }

    else if (HD9 == 0 && HD7 == 0 && HD8 == 0 && HD10 == 1)
    {
      v1 = 110;
      v2 = 110 + c;
      back();
    }

    else
    {
      v1 = 110;
      v2 = 110;
      back();
    }
  }
}

//*********************时间减速循迹*************************//
void sj_js_xunji(long n)
{
  for (long i = 0; i < n; i++)
  {
    //读取数字口高低电平信号至变量HD
    HD1 = digitalRead(14);
    HD2 = digitalRead(15);
    HD3 = digitalRead(16);
    HD4 = digitalRead(17);
    HD5 = digitalRead(18);
    HD6 = digitalRead(19);

    //中间在黑线
    if (HD1 == 1 && HD2 == 1 && HD3 == 0 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + a;
      v6 = 160;
      go1();

    }


    else if ( HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 0 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160;
      v6 = 160 + a;
      go1();

    }

    else if ( HD1 == 1 && HD2 == 0 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + b;
      v6 = 160;
      go1();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 0 && HD6 == 1)
    {
      v5 = 160;
      v6 = 160 + b;
      go1();
    }

    else if ( HD1 == 0 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + c;
      v6 = 160;
      go1();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 0)
    {
      v5 = 160;
      v6 = 160 + c;
      go1();
    }

    else
    {
      v5 = 160;
      v6 = 160;
      go1();
    }
  }
}

//************前两个灰度传感器遇黑线结束循迹****************
void qhd_xunji()
{
  while (1) //无限循环循迹程序
  {
    //读取数字口高低电平信号至变量HD
    HD1 = digitalRead(14);
    HD2 = digitalRead(15);
    HD3 = digitalRead(16);
    HD4 = digitalRead(17);
    HD5 = digitalRead(18);
    HD6 = digitalRead(19);

    QHDZ = digitalRead(28);
    QHDY = digitalRead(29);

    if (QHDZ == 1 && QHDY == 1)
    {
      break;
    }


    //中间在黑线
    if (HD1 == 1 && HD2 == 1 && HD3 == 0 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + a;
      v6 = 160;
      go1();

    }


    else if ( HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 0 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160;
      v6 = 160 + a;
      go1();

    }

    else if ( HD1 == 1 && HD2 == 0 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + b;
      v6 = 160;
      go1();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 0 && HD6 == 1)
    {
      v5 = 160;
      v6 = 160 + b;
      go1();
    }

    else if ( HD1 == 0 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + c;
      v6 = 160;
      go1();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 0)
    {
      v5 = 160;
      v6 = 160 + c;
      go1();
    }

    else
    {
      v5 = 160;
      v6 = 160;
      go1();
    }
  }
}

//************后两个灰度传感器遇黑线结束循迹****************
void hhd_xunji()  //速度100
{
  while (1) //无限循环循迹程序
  {
    //读取数字口高低电平信号至变量HD
    //读取数字口高低电平信号至变量HD
    HD1 = digitalRead(14);
    HD2 = digitalRead(15);
    HD3 = digitalRead(16);
    HD4 = digitalRead(17);
    HD5 = digitalRead(18);
    HD6 = digitalRead(19);

    HHDZ = digitalRead(26);
    HHDY = digitalRead(27);


    if (HHDZ == 1 && HHDY == 1)
    {
      break;
    }

    //中间在黑线
    if (HD1 == 1 && HD2 == 1 && HD3 == 0 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + a;
      v6 = 160;
      go1();

    }


    else if ( HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 0 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160;
      v6 = 160 + a;
      go1();

    }

    else if ( HD1 == 1 && HD2 == 0 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + b;
      v6 = 160;
      go1();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 0 && HD6 == 1)
    {
      v5 = 160;
      v6 = 160 + b;
      go1();
    }

    else if ( HD1 == 0 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 1)
    {
      v5 = 160 + c;
      v6 = 160;
      go1();

    }

    else if (  HD1 == 1 && HD2 == 1 && HD3 == 1 && HD4 == 1 && HD5 == 1 && HD6 == 0)
    {
      v5 = 160;
      v6 = 160 + c;
      go1();
    }

    else
    {
      v5 = 160;
      v6 = 160;
      go1();
    }
  }
}


//************ 后退 后两个灰度传感器遇黑线结束循迹****************
void houtui_hhd_xunji()  //速度88
{
  while (1) //无限循环循迹程序
  {
    //读取数字口高低电平信号至变量HD
    HD7 = digitalRead(22);   //后右内
    HD8 = digitalRead(23);   //后左内
    HD9 = digitalRead(24);   //后右外
    HD10 = digitalRead(25); //后右外

    HHDZ = digitalRead(26);
    HHDY = digitalRead(27);

    if (HHDZ == 1 && HHDY == 1)
    {
      break;
    }

    if (HD9 == 0 && HD7 == 0 && HD8 == 1 && HD10 == 0)
    {
      v1 = 110 + b;
      v2 = 110;
      back();

    }


    else if (HD9 == 0 && HD7 == 1 && HD8 == 0 && HD10 == 0)
    {
      v1 = 110;
      v2 = 110 + b;
      back();
    }

    else if (HD9 == 1 && HD7 == 0 && HD8 == 0 && HD10 == 0)
    {
      v1 = 110 + c;
      v2 = 110;
      back();
    }

    else if (HD9 == 0 && HD7 == 0 && HD8 == 0 && HD10 == 1)
    {
      v1 = 110;
      v2 = 110 + c;
      back();
    }


    else
    {
      v1 = 110;
      v2 = 110;
      back();
    }
  }
}
