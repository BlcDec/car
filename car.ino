#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;
#define one_transmission 100
#define two_transmission 200

#define IR1   A8//定义寻迹传感器引脚
#define IR2   A9
#define IR3   A10
#define IR4   A11
#define IR5   A12

#define  v5out1 53

int Out1,Out2,Out3,Out4,Out5;

void stopIfFault();
void motor_forward(int transmission);
void motor_turn_left(int transmission);//1,2,3三个 gear
void motor_turn_right(int transmission);
void motor_reverse();
void motor_neutral();

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual MC33926 Motor Shield");
  pinMode(v5out1,OUTPUT);
   pinMode(IR1, INPUT); 
   pinMode(IR2, INPUT); 
   pinMode(IR3, INPUT); 
   pinMode(IR4, INPUT); 
   pinMode(IR5, INPUT); 
  md.init();
}



void loop()
{
      digitalWrite(v5out1,HIGH);
    while(1)
    {
        Out1 = digitalRead(IR1);
        Out2 = digitalRead(IR2);
        Out3 = digitalRead(IR3);
        Out4 = digitalRead(IR4);
        Out5 = digitalRead(IR5);
        Serial.print(" Out1:");
        Serial.print(Out1);
        Serial.print(" Out2:");
        Serial.print(Out2);
        Serial.print(" Out3:");
        Serial.print(Out3);
        Serial.print(" Out4:");
        Serial.print(Out4);
        Serial.print(" Out5:");
        Serial.println(Out5);

        if(Out1==1 && Out2==1 && Out3==0 && Out4==1 && Out5==1)
        {
              motor_forward(one_transmission);
           //   delay(5);

           
        }
        else if(Out1==1 && Out2==1 && Out3==1 && Out4==0 && Out5==1)
        {
              motor_turn_right(2);
            //  delay(5);

        }
        else if(Out1==1 && Out2==1 && Out3==1 && Out4==1 && Out5==0)
        {
           motor_turn_right(3); 
         //  delay(5);
        }
        else if(Out1==1 && Out2==0 && Out3==1 && Out4==1 && Out5==1)
        {
             motor_turn_left(2);

        //     delay(5);
        }
        else if(Out1==0 && Out2==1 && Out3==1 && Out4==1 && Out5==1)
        {
              motor_turn_left(3);
            //  delay(5);

        }
        else
        {
           motor_forward(one_transmission);
          // delay(5);
        }
    }  
}
void stopIfFault()
{
  if (md.getFault())
  {
    Serial.println("fault");
    while(1);
  }
}
void motor_forward(int transmission)
{
    md.setSpeeds(transmission,transmission);
}
void motor_turn_left(int transmission_flag)
{
  if(transmission_flag==1)//turn one gear
  {
     md.setSpeeds(200,100);
  }
  else if(transmission_flag==2)//turn two gear
  {
    md.setSpeeds(300,100);
  }
  else if(transmission_flag==3)//turn three gear
  {
    md.setSpeeds(400,50);
  }
}
void motor_turn_right(int transmission_flag)
{
  if(transmission_flag==1)//turn one gear
  {
     md.setSpeeds(100,200);
  }
  else if(transmission_flag==2)//turn two gear
  {
    md.setSpeeds(100,300);
  }
  else if(transmission_flag==3)//turn three gear
  {
     md.setSpeeds(50,400);
  }
}
void motor_reverse()
{
  md.setSpeeds(-100,-100);
}
void motor_neutral()
{
  md.setSpeeds(0,0);
}

