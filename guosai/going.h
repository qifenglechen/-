void dianji1()
{
  unsigned long current = micros();
  if (current - previous1 >= v1)
  { // 检查是否到了亮灭灯的时间，也就是，如果现在和上一次亮灭灯的时间差比你设置的间隔时间大
    previous1 = current;   // 保存最后一次亮灯的时间
    if (DJ1State == LOW)
      DJ1State = HIGH;
    else
      DJ1State = LOW;
    digitalWrite(lzzCLK, DJ1State);
  }
}

void dianji2()
{
  unsigned long current = micros();
  if (current - previous2 >= v2)
  {
    previous2 = current;
    if (DJ2State == LOW)
      DJ2State = HIGH;
    else
      DJ2State = LOW;
    digitalWrite(lzyCLK, DJ2State);
  }
}

void dianji5()
{
  unsigned long current = micros();
  if (current - previous1 >= v5)
  { // 检查是否到了亮灭灯的时间，也就是，如果现在和上一次亮灭灯的时间差比你设置的间隔时间大
    previous1 = current;   // 保存最后一次亮灯的时间
    if (DJ1State == LOW)
      DJ1State = HIGH;
    else
      DJ1State = LOW;
    digitalWrite(lzzCLK, DJ1State);
  }
}

void dianji6()
{
  unsigned long current = micros();
  if (current - previous2 >= v6)
  {
    previous2 = current;
    if (DJ2State == LOW)
      DJ2State = HIGH;
    else
      DJ2State = LOW;
    digitalWrite(lzyCLK, DJ2State);
  }
}

void dianji7()
{
  unsigned long current = micros();
  if (current - previous1 >= v7)
  { // 检查是否到了亮灭灯的时间，也就是，如果现在和上一次亮灭灯的时间差比你设置的间隔时间大
    previous1 = current;   // 保存最后一次亮灯的时间
    if (DJ1State == LOW)
      DJ1State = HIGH;
    else
      DJ1State = LOW;
    digitalWrite(lzzCLK, DJ1State);
  }
}

void dianji8()
{
  unsigned long current = micros();
  if (current - previous2 >= v8)
  {
    previous2 = current;
    if (DJ2State == LOW)
      DJ2State = HIGH;
    else
      DJ2State = LOW;
    digitalWrite(lzyCLK, DJ2State);
  }
}
