#include <IRremote.h>    // IRremote库声明
const int RECV_PIN = 11; //定义红外接收器的引脚为11
IRrecv irrecv(RECV_PIN);
decode_results results; //解码结果放在 decode results结构的 result中
int in1 = 8;
int in2 = 9;
int in3 = 3;
int in4 = 4;
//上面定义了板上的4个控制端，12一组，34一组
int speedPinA = 5;
int speedPinB = 6;
//上面定义了PWM引脚
//下面开始定义方向
//tup=0; tdown=1; tleft=2; tright=3;
int turn = 8;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // 启动接收器
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //下面程序开始时让控制端都为高电平，电机保持不动。
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}
void loop()
{
  switch (turn) //通过这个循环，控制小车方向
  {
  case 0: //前进
    _mup(in1, in2, in3, in4);
    //读入电位器的值，然后通过PWM输出，控制电机转速
    _mSetSpeed(speedPinA, 255);
    _mSetSpeed(speedPinB, 255);
    break;
  case 1: //后退
    _mdown(in1, in2, in3, in4);
    //读入电位器的值，然后通过PWM输出，控制电机转速
    _mSetSpeed(speedPinA, 255);
    _mSetSpeed(speedPinB, 255);
    break;
  case 2: //左转
    _mleft(in1, in2, in3, in4);
    _mSetSpeed(speedPinA, 255);
    _mSetSpeed(speedPinB, 255);
    break;
  case 3: //右转
    _mright(in1, in2, in3, in4);
    _mSetSpeed(speedPinA, 255);
    _mSetSpeed(speedPinB, 255);
    break;
  case 4: //停止
    _mStop(in1, in2, in3, in4);
    break;
  };
  if (irrecv.decode(&results)) //解码成功，收到一组红外讯号
  {
    Serial.println(results.value); //以16进制换行输出接收代码
    switch (results.value)         //通过这个循环，比对
    {
    case 16736925: //前进
      turn = 0;
      break;
    case 16754775: //后退
      turn = 1;
      break;
    case 16720605: //向左
      turn = 2;
      break;
    case 16761405: //向右
      turn = 3;
      break;
    case 16712445: //后退
      turn = 4;
      break;
    };
    irrecv.resume(); // 接收下一个值
  }
}
void _mleft(int pin1, int pin2, int pin3, int pin4) //左转
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}
void _mright(int pin1, int pin2, int pin3, int pin4) //右转
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}
void _mup(int pin1, int pin2, int pin3, int pin4) //前进
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}
void _mdown(int pin1, int pin2, int pin3, int pin4) //后退
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);
}
void _mStop(int pin1, int pin2, int pin3, int pin4) //紧急制动，实际就是将电机两个端短接了
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
}
void _mSetSpeed(int pinPWM, int SpeedValue) //控制速度，实际上就是断断续续的控制298N的使能端，手抖的厉害的可以用个按钮自己尝试一下，估计也能实现对电机速度的控制，O(∩_∩)O~
{
  analogWrite(pinPWM, SpeedValue);
}