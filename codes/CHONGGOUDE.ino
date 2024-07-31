#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include "RTClib.h"
#include <SPI.h>
#define TIME_24_HOUR      true

int hour=0;int minute=0;
int menu_ifflag=0;
int menu_num=25;
int clarm_mode=0;
int tpausing=0;
int timer_num=0;
int timer_mode=0;
int music_mode=0;
int flag=0;
int flag_copy=0;
int game_mode=0;
int game_speed=1;
int alarm_end=0;

DateTime now;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0,SCL,SDA,U8X8_PIN_NONE);
// U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 12, /* data=*/ 11, /* cs=*/ 8, /* dc=*/ 9, /* reset=*/ 10);

RTC_DS3231 rtc;

void setup() 
{
  u8g2.begin();
  if(!rtc.begin())
  {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0,20,"something WRONG");
    u8g2.sendBuffer();
    delay(1000);  
    abort();
  }
  u8g2.clearBuffer();//清除内部缓冲区
  u8g2.setFont(u8g2_font_ncenB08_tr);//设置字体%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  pinMode(13,OUTPUT);//连蜂鸣器，第13口
  pinMode(2,INPUT);//上，第12口
  pinMode(3,INPUT);//确认，第10口
  pinMode(4,INPUT);//下，第11口

  pinMode(5,INPUT);pinMode(6,INPUT);pinMode(7,INPUT);pinMode(8,INPUT);pinMode(9,INPUT);pinMode(10,INPUT);pinMode(12,INPUT);//上，第12口
}

void settime()
{
  // rtc.adjust(DateTime(2023,6,3,11,05,00));
  now=rtc.now();//时间设置
}

void setclarm()
{
  u8g2.clearBuffer();
  if(clarm_mode%2==0)
    {
      u8g2.drawStr(10,20,"set hour");
    }
  else
    {
      u8g2.drawStr(10,20,"set minute");
    }
  u8g2.setCursor(10, 55);
  u8g2.print("AL."); 

  if(hour<10)
  {
   u8g2.print("0"); 
  }

  u8g2.print(hour);

  u8g2.print(":");

  if(minute<10) 
  {
   u8g2.print("0"); 
  }

  u8g2.print(minute);

  u8g2.sendBuffer();
  if(digitalRead(3)==HIGH)
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    clarm_mode=clarm_mode+1;
  }
  if(digitalRead(4)==HIGH&&digitalRead(2)==LOW)//6口设置闹钟的时
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    if(clarm_mode%2==0)
    {
      hour=hour+1;
      if(hour==24)
      {
        hour=0;
      }
    }
    else
    {
      minute=minute+1;
      if(minute==60)
      {
        minute=0;
      }
    }
  }
  else if(digitalRead(4)==LOW&&digitalRead(2)==HIGH)//6口设置闹钟的时
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    if(clarm_mode%2==0)
    {
      if(hour==0)
      {
        hour=23;
      }
      else
      {
        hour=hour-1;
      }
    }
    else
    {
      if(minute==0)
      {
        minute=59;
      }   
      else
      {
        minute=minute-1;
      }
    }
  }
  
}

void menu_if()
{
    int temp=0;
    while(digitalRead(3)==HIGH)
    {
      temp++;
      delay(50);
      if(temp==30)
      {
        break;
      }
    }
    if(temp==30)
    {
      if(menu_ifflag==0)
        menu_ifflag=1;
      else
        menu_ifflag=0;
    }
    else
    ;
}

void menu()
{
  if(digitalRead(4)==HIGH&&digitalRead(2)!=HIGH)
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    menu_num++;
  }
  else if(digitalRead(2)==HIGH&&digitalRead(4)!=HIGH)
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    menu_num--;
  }
  if(menu_num==50||menu_num==0)
   menu_num=25;
  else
  ;
  u8g2.drawStr((u8g2.getDisplayWidth()-u8g2.getStrWidth("menu"))/2,10,"menu");
  u8g2.setCursor(10,30);
  switch(menu_num%5)
  {
    case 0:
    u8g2.print("time");
    break;
    case 1:
    alarm_end=0;
    u8g2.print("set alarm");
    break;
    case 2:
    u8g2.print("timer");
    break;
    case 3:
    u8g2.print("music");
    break;
    case 4:
    u8g2.print("game");
    break;
  }
u8g2.sendBuffer(); 
}

void time()
{
  u8g2.setCursor(10, 15);
  u8g2.print(now.year()); u8g2.print("/"); u8g2.print(now.month()); u8g2.print("/"); u8g2.print(now.day());
  u8g2.setCursor(10, 35);
  if(now.hour()<10)
  {
   u8g2.print("0"); 
  }
  u8g2.print(now.hour());     
  u8g2.print(":");     
  if(now.minute()<10)
  {
   u8g2.print("0"); 
  }
  u8g2.print(now.minute());     
  u8g2.print(":");     
  if(now.second()<10)
  {
   u8g2.print("0"); 
  }
  u8g2.print(now.second()); 

  u8g2.setCursor(10, 55);
  u8g2.print("AL."); 
  if(hour<10)
  {
   u8g2.print("0"); 
  }
  u8g2.print(hour);
  u8g2.print(":");
  if(minute<10) 
  {
   u8g2.print("0"); 
  }
  u8g2.print(minute);
  u8g2.sendBuffer();
}

void timer()
{
  if(timer_mode%5==0)
  {
    timer_num=now.hour()*60*60+now.minute()*60+now.second();
    timer_mode=1;
  }
  else if(timer_mode%5==1)
  {
  u8g2.setCursor(10, 20); u8g2.print("timing");
  timer_print(now.hour()*60*60+now.minute()*60+now.second()-timer_num);
  }
  else if(timer_mode%5==2)
  {
  tpausing=now.hour()*60*60+now.minute()*60+now.second()-timer_num;
  timer_mode=3;
  }
  else if(timer_mode%5==3)
  {
    u8g2.setCursor(10, 20); u8g2.print("pausing");
    timer_print(tpausing);
  }
  else
  {
    u8g2.setCursor(10, 20); u8g2.print("zero cleaning");
    timer_num=0;
    timer_print(0);
  }
  if(digitalRead(3)==HIGH)
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    timer_mode=timer_mode+1;
  }
  else
  ;
}

void timer_print(int a)
{
  u8g2.setCursor(10, 45);
  if(a/(24*60)<10)
  {
   u8g2.print("0"); 
  }
  u8g2.print(a/(24*60));

  u8g2.print(":");
  
  if(a/60-(a/(24*60))*60<10) 
  {
   u8g2.print("0"); 
  }
  u8g2.print(a/60-(a/(24*60))*60);

  u8g2.print(":");

  if(a-(a/(24*60))*60*60-(a/60-(a/(24*60))*60)*60<10) 
  {
   u8g2.print("0"); 
  }
  u8g2.print(a-(a/(24*60))*60*60-(a/60-(a/(24*60))*60)*60);
  u8g2.sendBuffer();
}

void music()
{
  if(music_mode==0)
  {
    play_freely();
  }
  // else if(music_mode==1)//欢乐颂
  // {
  //   if(TUNE_1<sizeof(tune)/sizeof(tune[0]))
  //   {  
  //   u8g2.setCursor(10, 10);
  //   u8g2.print("Ode an die Freude"); 
  //   u8g2.sendBuffer(); 
  //   tone(13,tune[TUNE_1]);
  //   delay(500*durt[TUNE_1]);   //这里用来根据节拍调节延时，500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
  //   noTone(13);
  //   TUNE_1=TUNE_1+1;
  //   }
  // }
  if(digitalRead(4)==HIGH)
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    music_mode=music_mode+1;
  }
  if(digitalRead(2)==HIGH)
  {
    delay(300);
    tone(13,294);
    delay(20);
    noTone(13);
    music_mode=music_mode-1;
  }
}

void play_freely()
{
  u8g2.setCursor(10, 10);
  u8g2.print("freely");
  if(digitalRead(12)==HIGH)
  {
    tone(13,262);
    u8g2.drawBox(u8g2.getDisplayWidth()/2-10,u8g2.getDisplayHeight()-262*u8g2.getDisplayHeight()/500,20,262*u8g2.getDisplayHeight()/500);
  }
  else if(digitalRead(10)==HIGH)
  {
    tone(13,294);
    u8g2.drawBox(u8g2.getDisplayWidth()/2-10,u8g2.getDisplayHeight()-294*u8g2.getDisplayHeight()/500,20,294*u8g2.getDisplayHeight()/500);
  }
  else if(digitalRead(9)==HIGH)
  {
    tone(13,330);
    u8g2.drawBox(u8g2.getDisplayWidth()/2-10,u8g2.getDisplayHeight()-330*u8g2.getDisplayHeight()/500,20,330*u8g2.getDisplayHeight()/500);
  }
  else if(digitalRead(8)==HIGH)
  {
    tone(13,349);
    u8g2.drawBox(u8g2.getDisplayWidth()/2-10,u8g2.getDisplayHeight()-349*u8g2.getDisplayHeight()/500,20,349*u8g2.getDisplayHeight()/500);
  }
  else if(digitalRead(7)==HIGH)
  {
    tone(13,392);
    u8g2.drawBox(u8g2.getDisplayWidth()/2-10,u8g2.getDisplayHeight()-392*u8g2.getDisplayHeight()/500,20,392*u8g2.getDisplayHeight()/500);
  }
  else if(digitalRead(6)==HIGH)
  {
    tone(13,440);
    u8g2.drawBox(u8g2.getDisplayWidth()/2-10,u8g2.getDisplayHeight()-440*u8g2.getDisplayHeight()/500,20,440*u8g2.getDisplayHeight()/500);
  }
  else if(digitalRead(5)==HIGH)
  {
    tone(13,494);
    u8g2.drawBox(u8g2.getDisplayWidth()/2-10,u8g2.getDisplayHeight()-494*u8g2.getDisplayHeight()/500,20,494*u8g2.getDisplayHeight()/500);
  }
  else
  {
  noTone(13);
  }
  u8g2.sendBuffer();
}

void game()
{
  if(game_mode==0)
  {
    int ran=random(0,101);
    int y=u8g2.getDisplayHeight();
    int x=u8g2.getDisplayWidth();
    flag_copy=flag;
    int x_draw;
    switch(ran%3)
    {
      case 0:
        x_draw=x/4-5;
        break;
      case 1:
        x_draw=x/2-5;
        break;
      case 2:
        x_draw=x/4*3-5;
        break;
    }
    for(int t=10;t<y-10;t+=game_speed)
    {
      if(digitalRead(12)==HIGH)
        game_speed=1;
      if(digitalRead(10)==HIGH)
        game_speed=2;
      if(digitalRead(9)==HIGH)
        game_speed=3;
      if(digitalRead(8)==HIGH)
        game_speed=4;
      if(digitalRead(7)==HIGH)
        game_speed=5;
      if(digitalRead(6)==HIGH)
        game_speed=6;
      if(digitalRead(5)==HIGH)
        game_speed=7;
      u8g2.clearBuffer();
      u8g2.setCursor(10,30);
      u8g2.print(flag);
      u8g2.setCursor(10,15);
      u8g2.print("speed:  ");
      u8g2.print(game_speed);
      u8g2.drawBox(x_draw,t,10,5);
      u8g2.sendBuffer();
      if(ran%3==1&&t<y-10&&digitalRead(3)==HIGH)
      {
        delay(150);
        tone(13,294);
        delay(20);
        noTone(13);
        flag+=game_speed;
        break;
      }
      else if(ran%3==0&&t<y-10&&digitalRead(2)==HIGH)
      {
        delay(150);
        tone(13,294);
        delay(20);
        noTone(13);
        flag+=game_speed;
        break;
      }
      else if(ran%3==2&&t<y-10&&digitalRead(4)==HIGH)
      {
        delay(150);
        tone(13,294);
        delay(20);
        noTone(13);
        flag+=game_speed;
        break;
      }
    }
    if(flag==flag_copy)
    {
      game_mode=1;
    }
  }
  else
  {
    u8g2.setCursor(10,30);
    u8g2.print("game over!");
    tone(13,262);
    delay(20);
    noTone(13);
    u8g2.setCursor(10,45);
    u8g2.print("score:  ");
    u8g2.print(flag);
    if(digitalRead(2)==HIGH||digitalRead(4)==HIGH)
    {
      delay(150);
      game_mode=0;
      flag=0;
      flag_copy=0;
    }
  }
}

void alarm()
{
  while(alarm_end!=1)
  {
    tone(13,294);
    if(digitalRead(2)||digitalRead(3)||digitalRead(4)==HIGH)
    {
      delay(150);
      noTone(13);
      alarm_end=1;
    }
  }
  
}

void display()
{    //时间、调整时间、闹钟、调节闹钟、计时器
//音乐、游戏
  u8g2.setCursor(10,30);
  switch(menu_num%5)
  {
    case 0:
    time();
    break;
    case 1:
    setclarm();
    break;
    case 2:
    // u8g2.print("111");
    // u8g2.sendBuffer();
    timer();
    break;
    case 3:
    music();
    u8g2.sendBuffer();
    break;
    case 4:
    game();
    u8g2.sendBuffer();
    break;
  }
}
void loop() 
{
  u8g2.clearBuffer();
  settime();
  menu_if();
  if(menu_ifflag==1)
  {
    menu();
  }
  else if(menu_ifflag==0)
  {
    display();
  }
  if(now.hour()==hour&&now.minute()==minute)
  {
    alarm();
  }
}
