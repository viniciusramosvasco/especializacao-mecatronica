
#include <EasyTransfer.h>
EasyTransfer ET;

struct rovData
{
  int RSYVal;
  int RSXVal;
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
int RSXVal = 0;
int LSYVal = 0;

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

    //Movimentação para frente
    if(data.RSYVal < 100){
      int motor_speed = map(data.RSYVal,0,99,99,0);
      int motor_speed_2 = map(data.RSYVal,0,99,99,0);
      Serial.println(motor_speed, DEC);
      Serial.println("\t");
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led1, LOW);    
      digitalWrite(led2, LOW);
      byte brightness;
      byte brightness_2;
      brightness = motor_speed;
      brightness_2 = motor_speed_2;
      analogWrite(led1, brightness);
      analogWrite(led2, brightness_2);
      /*int forwardPWM = motor_speed;
       int forwardPWM_2 = motor_speed_2;
       analogWrite(LPWM_Output, forwardPWM);
       analogWrite(LPWM_Output_2, forwardPWM_2);
       analogWrite(RPWM_Output, 0);
       analogWrite(RPWM_Output_2, 0);
       */
    }
    // Parado
    else if(data.RSYVal >= 100 && data.RSYVal < 156){
      motor_speed = 0;
      motor_speed_2 = 0;
      Serial.println(motor_speed, DEC);
      Serial.println("\t");
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      //    Serial.println("Analogico na posicao Neutra!!");
    }
    //Movimentação em Ré
    else{
      /*Serial.println("BIT: "); 
       Serial.println(RSYVal, DEC);*/      //analógico direito
      int motor_speed = map(data.RSYVal,156,255,0,99);
      int motor_speed_2 = map(data.RSYVal,156,255,0,99);
      /*Serial.println("RIGHT MOTOR REVERSE: ");*/
      Serial.println(motor_speed, DEC);
      Serial.println("\t");
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      byte brightness;     
      brightness = motor_speed;
      brightness_2 = motor_speed_2;
      analogWrite(led1, brightness);
      analogWrite(led2, brightness_2);
      /*int reversePWM = motor_speed;
       reversePWM_2 = motor_speed_2
       analogWrite(LPWM_Output, 0);
       analogWrite(LPWM_Output_2, 0);
       analogWrite(RPWM_Output, reversePWM);
       analogWrite(RPWM_Output_2, reversePWM_2);*/
    }


    //Movimentação para Esquerda
    if(data.RSXVal < 100){            
      /*Serial.println("BIT: ");
       Serial.println(RSXVal, DEC);*/
      int motor_speed = 0;
      int motor_speed_2 = map(data.RSXVal,0,99,99,0);
      Serial.println(motor_speed, DEC);
      Serial.println("\t");
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      byte brightness_2;
      brightness_2 = motor_speed_2;
      analogWrite(led2, brightness_2);
      /*int forwardPWM_2 = motor_speed_2;
       analogWrite(LPWM_Output_2, forwardPWM_2);
       analogWrite(RPWM_Output_2, 0);*/
    }
    //Parado
    else if(data.RSXVal >= 100 && data.RSXVal < 156){
      motor_speed = 0;
      motor_speed_2 = 0;
      Serial.println(motor_speed, DEC);
      Serial.println("\t");
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      //    Serial.println("Analogico na posicao Neutra!!");
    }
    //Movimentação para Direita
    else{                                        
      /*Serial.println("BIT: "); 
       Serial.println(RSXVal, DEC);*/      //analógico direito
      int motor_speed = map(data.RSXVal,156,255,0,99);
      int motor_speed_2 = 0;
      Serial.println(motor_speed, DEC);
      Serial.println("\t");
      Serial.println(motor_speed_2, DEC);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      byte brightness;     
      brightness = motor_speed;
      analogWrite(led1, brightness);
      /*int reversePWM = motor_speed;
       analogWrite(LPWM_Output, 0);
       analogWrite(RPWM_Output, reversePWM);*/
    }

    //motor3
    if(data.motor3 < 100){       // Sentido Direto            
      /*Serial.println("BIT: ");
       Serial.println(LSYVal, DEC);*/
      int motor_speed_3 = map(data.motor3,0,99,99,0);
      /*Serial.println("VERTICAL FORWARD: ");*/
      Serial.println(motor_speed_3, DEC);
      digitalWrite(led3, LOW);    
      byte brightness_3;     
      brightness_3 = motor_speed_3;
      analogWrite(led3, brightness_3);
      /*int forwardPWM = motor_speed_3;
       analogWrite(LPWM_Output, forwardPWM);
       analogWrite(RPWM_Output, 0);*/
    }

    else if(data.motor3 >= 100 && data.motor3 < 156){
      motor_speed_3 = 0;
      Serial.println(motor_speed_3, DEC);
      digitalWrite(led3, LOW);
      //    Serial.println("Analogico na posicao Neutra!!");
    }

    else{                                        // Sentido Reverso
      /*Serial.println("BIT: "); 
       Serial.println(RSYVal, DEC);*/      //analógico direito
      int motor_speed_3 = map(data.motor3,156,255,0,99);
      /*Serial.println("RIGHT MOTOR REVERSE: ");*/
      Serial.println(motor_speed_3, DEC);
      digitalWrite(led3, LOW);    
      byte brightness_3;     
      brightness_3 = motor_speed_3;
      analogWrite(led3, brightness_3);
      /*int reversePWM = motor_speed_3;
       analogWrite(LPWM_Output, 0);
       analogWrite(RPWM_Output, reversePWM);*/
    }

  }
    //*************************************************************    

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




