#include <PS2X_lib.h>
#include <EasyTransfer.h>
EasyTransfer ET;

//------------------------------------
float softwareVersion  = 2.0;

//PS2 controller setup----------------
PS2X ps2x;
int error = 0; 
byte type = 0;
byte vibrate = 0;

//variables---------------------------
boolean enable = false;
int neutral = 128;
int verticals = 0;
int LSYVal = 0;
int RSYVal = 0;
int RSXVal = 0;
boolean enabled = false;

//BWD---------------------------------
unsigned long lastSend = 0;
unsigned long currentTime;
int sendInterval = 75;

//rs422 com setup---------------------
struct rovData
{
  int RSYVal;
  int RSXVal;
  int motor3;
  int relay1;
  int relay2;
}data;

//-------------------------------------------
void setup()
{
 Serial.begin(9600);
 ET.begin(details(data), &Serial);
 error = ps2x.config_gamepad(2,3,5,6, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
 
 if(error == 0)
 {
   Serial.println("Ready");
 }
 
}
//-------------------------------------------
void loop()
{       
 if(error == 1) //skip loop if no controller found
  return; 
  
 if(type == 2)
 { //Guitar Hero Controller
 }
 else
 {   
    //ps2x.read_gamepad(false, vibrate);       //read controller and set large motor to spin at 'vibrate' speed
    //vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on
                                               //how hard you press the blue (X) button  
    ps2x.read_gamepad();
    
    if(ps2x.ButtonPressed(PSB_START) && enabled == false)
    {
      enable = true;
      Serial.println("enabled");
      enabled = true;
    }
    else if(ps2x.ButtonPressed(PSB_START) && enabled == true)
    {
      enable = false;
      Serial.println("disabled");
      enabled = false;
    }
                      
    LSYVal = ps2x.Analog(PSS_LY);
    RSYVal = ps2x.Analog(PSS_RY);
    RSXVal = ps2x.Analog(PSS_RX);

    motorCalc();   
 }      
}
//-----------------------------------------
inline void motorCalc()
{
    data.RSYVal = RSYVal;
    data.RSXVal = RSXVal;  
    data.motor3 = LSYVal;
    
    //debug
    /*
    Serial.println(data.motor1);
    Serial.println(data.motor2);
    Serial.println(data.motor3);
    Serial.println("...");  
    */  
    
    currentTime = millis();
    if(currentTime - lastSend > sendInterval)
    {
      lastSend = currentTime;
      if(enable == true)
      {
        ET.sendData();
      }
    }
}
