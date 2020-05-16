#include "Keyboard_jp.h"   // This is a custome keyboard library for Japanese keyboard. 
//#include "Keyboard.h"   // If you want to use English keyboard, please use genuine Arduino keyboard library. Then delete the Keyboard_jp file.

#include "IRRC.h"

#define MAX_BUTTON_DATA_BYTE_COUNT      8

#define PIN_LED                         17
#define PIN_IR_SENSOR_SIG               2
#define PIN_IR_SENSOR_GND               3
#define PIN_IR_SENSOR_PWR               4

void setup()
{
  pinMode(PIN_LED, OUTPUT);

  pinMode(PIN_IR_SENSOR_SIG, INPUT);
  pinMode(PIN_IR_SENSOR_GND, OUTPUT);
  digitalWrite(PIN_IR_SENSOR_GND, LOW);
  pinMode(PIN_IR_SENSOR_PWR, OUTPUT);
  digitalWrite(PIN_IR_SENSOR_PWR, HIGH);

  Keyboard.begin();
  //Serial.begin(115200UL);
}

void loop()
{
  uint8_t data[MAX_BUTTON_DATA_BYTE_COUNT];
  uint8_t mode;
  uint8_t timeHigh,timeLow;
  uint8_t fBit;
  uint8_t byteCount;
  uint8_t bitCount=0;
  uint8_t i;
  uint16_t count = 0;
  uint8_t type;

  while(digitalRead(PIN_IR_SENSOR_SIG));
  
  mode=MODE_CHECK_HEADER;
    
  while(1)
  {
    timeHigh=0;
    timeLow=0;
      
    while(!digitalRead(PIN_IR_SENSOR_SIG))
    {
      digitalWrite(PIN_LED, LOW);
      timeHigh++;
      if(timeHigh==0)
      {
        timeHigh=0xFF;
        while(!digitalRead(PIN_IR_SENSOR_SIG));
        break;
      }
      _delay_us(50);
    }
    while(digitalRead(PIN_IR_SENSOR_SIG))
    {
      digitalWrite(PIN_LED, HIGH);
      timeLow++;
      if(timeLow==0)
      {
        timeLow=0xFF;
        break;
      }
      _delay_us(50);
    }
    
    if(mode==MODE_CHECK_HEADER)
    {
      if(timeHigh>=K_THRESHOLD_HEADER_HIGH_MIN && timeHigh<=K_THRESHOLD_HEADER_HIGH_MAX)
      {
        if(timeLow>=K_THRESHOLD_HEADER_LOW_MIN && timeLow<=K_THRESHOLD_HEADER_LOW_MAX)
        {
          mode=MODE_ANALYZE;
          fBit=0x80;
          byteCount=0;
          bitCount=0;
          for(i=0;i<MAX_BUTTON_DATA_BYTE_COUNT;i++)  data[i]=0;
          type=TYPE_K;
        }
        else if(timeLow>=K_THRESHOLD_HEADER_REP_LOW_MIN && timeLow<=K_THRESHOLD_HEADER_REP_LOW_MAX)
        {
          mode=MODE_REPEAT;
        }
      }
      
      if(timeHigh>=S_THRESHOLD_HEADER_HIGH_MIN && timeHigh<=S_THRESHOLD_HEADER_HIGH_MAX)
      {
        if(timeLow>=S_THRESHOLD_HEADER_LOW_MIN && timeLow<=S_THRESHOLD_HEADER_LOW_MAX)
        {
          mode=MODE_ANALYZE;
          fBit=0x80;
          byteCount=0;
          bitCount=0;
          for(i=0;i<MAX_BUTTON_DATA_BYTE_COUNT;i++)  data[i]=0;
          type=TYPE_S;
        }
      }
      
      if(timeHigh>=P_THRESHOLD_HEADER_HIGH_MIN && timeHigh<=P_THRESHOLD_HEADER_HIGH_MAX)
      {
        if(timeLow>=P_THRESHOLD_HEADER_LOW_MIN && timeLow<=P_THRESHOLD_HEADER_LOW_MAX)
        {
          mode=MODE_ANALYZE;
          fBit=0x80;
          byteCount=0;
          bitCount=0;
          for(i=0;i<MAX_BUTTON_DATA_BYTE_COUNT;i++)  data[i]=0;
          type=TYPE_P;
        }
      }
      
    }
    else if(mode==MODE_ANALYZE)
    {
      if(type==TYPE_K || type==TYPE_P)
      {
        if(timeLow>=K_THRESHOLD_STOP_LOW_MIN)
        {
          mode=MODE_RECEIVED;
        }
        else
        {
          if(timeLow>=(timeHigh+timeHigh))
          {
            data[byteCount]|=fBit;
          }
          fBit>>=1;
          if(fBit==0)
          {
            byteCount++;
            fBit=0x80;
            if(byteCount>=MAX_BUTTON_DATA_BYTE_COUNT)
            {
              mode=MODE_OVERFLOW;
            }
          }
          bitCount++;
        }
      }
      else if(type==TYPE_S)
      {
        if(timeHigh>=S_THRESHOLD_CODE && timeHigh>0)
        {          
          data[byteCount]|=fBit;
        }
        bitCount++;
        
        fBit>>=1;
        if(fBit==0)
        {
          byteCount++;
          fBit=0x80;
          if(byteCount>=MAX_BUTTON_DATA_BYTE_COUNT)
          {
            mode=MODE_OVERFLOW;
          }
        }
        
        if(mode!=MODE_OVERFLOW)
        {
          if(timeLow>=S_THRESHOLD_STOP_LOW_MIN)
          {
            mode=MODE_RECEIVED;
          }
        }
      }
    }
    else if(mode==MODE_REPEAT)
    {
      if(timeLow>=K_THRESHOLD_STOP_LOW_MIN)
      {
        mode=MODE_REPEAT_RECEIVED;
      }
      else
      {
        mode=MODE_OVERFLOW;
      }
    }
    else if(mode==MODE_OVERFLOW)
    {
      if(type==TYPE_K)
      {
        if(timeLow>=K_THRESHOLD_STOP_LOW_MIN)
        {
          mode=MODE_RECEIVED;
        }
      }
    }
    
    if(mode==MODE_RECEIVED)
    {
      int byteCount=(bitCount/8)+((bitCount%8)?1:0);
      int tmp;
      
      Keyboard.write('{');
      Keyboard.print(bitCount,DEC);
      Keyboard.write(',');
      
      for(i=0;i<byteCount;i++)
      {
        Keyboard.print("0x");
        tmp=data[i]>>4;
        if(tmp<10)  Keyboard.write(tmp+'0');
        else        Keyboard.write(tmp+'A'-10);
        tmp=data[i]&0x0F;
        if(tmp<10)  Keyboard.write(tmp+'0');
        else        Keyboard.write(tmp+'A'-10);
        
        if(i<byteCount-1)
        {
          Keyboard.write(',');
        }
      }
      Keyboard.write('}');
      Keyboard.write(',');
      break;
    }
    else if(mode==MODE_REPEAT_RECEIVED)
    {
#ifndef  DISABLE_REPEAT_CODE
      Keyboard.println("RepeatCode");
#endif
      break;
    }
    else if(mode==MODE_CHECK_HEADER)
    {
      bitCount=0;
      break;
    }
  }
  while(!digitalRead(PIN_IR_SENSOR_SIG));
  digitalWrite(PIN_LED, HIGH);
}
