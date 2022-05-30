void servopulse1(int gouzi_servo_s, int myangle) //定义一个脉冲函数
{
  pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(gouzi_servo_s, HIGH); //将舵机接口电平至高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(gouzi_servo_s, LOW); //将舵机接口电平至低
  delay(20 - pulsewidth / 1000);
}

void servopulse2(int gouzi_servo_x, int myangle) //定义一个脉冲函数
{
  pulsewidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(gouzi_servo_x, HIGH); //将舵机接口电平至高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(gouzi_servo_x, LOW); //将舵机接口电平至低
  delay(20 - pulsewidth / 1000);
}

//勾子上舵机
void gouzi_servo1(int x1)
{
  for (int i = 0; i <= 50; i++) //给予舵机足够的时间让它转到指定角度
  {
    servopulse1(gouzi_servo_s, x1); //引用脉冲函数
  }

}

//勾子下舵机
void gouzi_servo2(int x2)
{

  for (int i = 0; i <= 50; i++) //给予舵机足够的时间让它转到指定角度
  {
    servopulse2(gouzi_servo_x, x2); //引用脉冲函数
  }

}
