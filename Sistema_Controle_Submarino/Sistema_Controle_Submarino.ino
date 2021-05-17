
#include <EasyTransfer.h>
EasyTransfer ET;

struct rovData
{
  int motor1;
  int motor2;
  int motor3;
  int relay1;
  int relay2;
}data;

/*
int LPWM_Output = 8;
int RPWM_Output = 9;
int LPWM2_Output = 6;
int RPWM2_Output = 7;
int LPWM3_Output = 3;
int RPWM3_Output = 5;
*/
int RSYVal = 0;
int LSYVal = 0;
int TRIANGLE = 0;
int CROSS = 0;

int motor_speed = 12;
int motor_speed_2 = 11;
int motor_speed_3 = 5;
int brightness = 0;
int brightness_2 = 0;
int brightness_3 = 0;

int ledPin = 30;
int led1 = 12;
int led2 = 11;
int led3 = 5;
int ledState = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 1000;
unsigned long lastComCheck = 0;
unsigned long lastComInterval = 1500;

void setup()
{
  Serial.begin(9600); 
  ET.begin(details(data), &Serial);
/*
  pinMode(LPWM_Output, OUTPUT);
  pinMode(RPWM_Output, OUTPUT);
  pinMode(LPWM2_Output, OUTPUT);
  pinMode(RPWM2_Output, OUTPUT);
  pinMode(LPWM3_Output, OUTPUT);
  pinMode(RPWM3_Output, OUTPUT);
*/
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(motor_speed, OUTPUT);
  pinMode(motor_speed_2, OUTPUT);
  pinMode(motor_speed_3, OUTPUT);

}

void loop()
{
  unsigned long currentMillis = millis();
  if(ET.receiveData())
  {
    lastComCheck = millis();
    interval = 1000;

    //motor1
    if(data.motor1 < 100){       // Sentido Direto            
      /*Serial.println("BIT: ");
      Serial.println(RSYVal, DEC);*/
      int motor_speed = map(data.motor1,0,99,99,0);
      /*Serial.println("RIGHT MOTOR FORWARD: ");*/
      Serial.println(motor_speed, DEC);
      digitalWrite(led1, LOW);    
      byte brightness;     
      brightness = motor_speed;
      analogWrite(led1, brightness);

      /*int forwardPWM = motor_speed;
      analogWrite(LPWM_Output, forwardPWM);
      analogWrite(RPWM_Output, 0);*/    
    }

    else if(data.motor1 >= 100 && data.motor1 < 156){
      motor_speed = 0;
      Serial.println(motor_speed, DEC);
      digitalWrite(led1, LOW);
      //    Serial.println("Analogico na posicao Neutra!!");
    }

    else{                                        // Sentido Reverso
      /*Serial.println("BIT: "); 
      Serial.println(RSYVal, DEC);*/ //analógico direito
      int motor_speed = map(data.motor1,156,255,0,99);
      /*Serial.println("RIGHT MOTOR REVERSE: ");*/
      Serial.println(motor_speed, DEC);
      digitalWrite(led1, LOW);    
      byte brightness;     
      brightness = motor_speed;
      analogWrite(led1, brightness);

      /*int reversePWM = motor_speed;
      analogWrite(LPWM_Output, 0);
      analogWrite(RPWM_Output, reversePWM);*/              
    }


    //motor2
    if(data.motor2 < 100){       // Sentido Direto            
      /*Serial.println("BIT: "); 
      Serial.println(data.motor2, DEC);*/
      int motor_speed_2 = map(data.motor2,0,99,99,0);
      /*Serial.println("LEFT MOTOR FORWARD: ");*/
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led2, LOW);    
      byte brightness_2;     
      brightness_2 = motor_speed_2;
      analogWrite(led2, brightness_2);


      /*int forwardPWM2 = motor_speed_2;
      analogWrite(LPWM2_Output, forwardPWM2);
      analogWrite(RPWM2_Output, 0);*/    
    }

    else if(data.motor2 >= 100 && data.motor2 < 156){
      motor_speed_2 = 0;
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led2, LOW);
      //    Serial.println("Analogico na posicao Neutra!!");
    }

    else{                                        // Sentido Reverso
      /*Serial.println("BIT: "); 
      Serial.println(data.motor2, DEC);*/ //analógico esquerdo
      int motor_speed_2 = map(data.motor2,156,255,0,99);
      /*Serial.println("LEFT MOTOR REVERSE: ");*/
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led2, LOW);    
      byte brightness_2;     
      brightness_2 = motor_speed_2;
      analogWrite(led2, brightness_2);

      /*int reversePWM2 = motor_speed_2;
      analogWrite(LPWM2_Output, 0);
      analogWrite(RPWM2_Output, reversePWM2);*/              
    }

    //motor3
    if(data.motor3 > 0 ) 
    {
    Serial.println(data.motor3, DEC);
    digitalWrite(led3, HIGH);    
    }
    else
    {
    Serial.println(data.motor3, DEC);
    digitalWrite(led3, LOW);
    }
    
  }

  if(millis() - lastComCheck > 1000)
  {
    interval = 100;
    rovSafe();
  }  

  if(currentMillis - previousMillis > interval)
  {
    previousMillis = currentMillis;
    if(ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }

  //delay(5);
}
//--------------------------------------
inline void rovSafe()
{
  /*digitalWrite(LPWM_Output, LOW);
  digitalWrite(RPWM_Output, LOW);
  digitalWrite(LPWM2_Output, LOW);
  digitalWrite(RPWM2_Output, LOW);
  digitalWrite(LPWM3_Output, LOW);
  digitalWrite(RPWM3_Output, LOW);*/
}
//--------------------------------------

/*
inline void outputValues()
 {
 if(data.motor1 < 128) //motor1 Left
 {
 digitalWrite(motorPin1, HIGH);
 digitalWrite(motorPin2, LOW);
 }
 else if(data.motor1 > 128)
 {
 digitalWrite(motorPin1, HIGH);
 digitalWrite(motorPin2, LOW);
 }
 else if(data.motor1 == 128)
 {
 digitalWrite(motorPin1, LOW);
 digitalWrite(motorPin2, LOW);
 }
 else
 {
 digitalWrite(motorPin1, LOW);
 digitalWrite(motorPin2, LOW);
 }
 
 if(data.motor2 < 128)  //motor2 Right
 {
 digitalWrite(motorPin3, HIGH);
 digitalWrite(motorPin4, LOW);
 }
 else if(data.motor2 > 128)
 {
 digitalWrite(motorPin3, HIGH);
 digitalWrite(motorPin4, LOW);
 }
 else if(data.motor2 == 128)
 {
 digitalWrite(motorPin3, LOW);
 digitalWrite(motorPin4, LOW);
 }
 else
 {
 digitalWrite(motorPin1, LOW);
 digitalWrite(motorPin2, LOW);
 }
 
 
 if(data.motor3 == 1) //motor3 verticals
 {
 digitalWrite(motorPin5, HIGH);
 digitalWrite(motorPin6, LOW);
 }
 else if(data.motor3 == 2)
 {
 digitalWrite(motorPin5, HIGH);
 digitalWrite(motorPin6, LOW);
 }
 else if(data.motor3 == 0)
 {
 digitalWrite(motorPin5, LOW);
 digitalWrite(motorPin6, LOW);
 }
 else
 {
 digitalWrite(motorPin1, LOW);
 digitalWrite(motorPin2, LOW);
 }
 } 
 */



