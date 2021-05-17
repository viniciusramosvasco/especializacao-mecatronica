
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
boolean Up = false;
boolean Down = false;
boolean enabled = false;
boolean triangulo = false;

//BWD---------------------------------
unsigned long lastSend = 0;
unsigned long currentTime;
int sendInterval = 75;

//rs422 com setup---------------------
struct rovData
{
  int RSYVal;
  int LSYVal;
  boolean triangulo;
  boolean Up;
  boolean Down;  
}
data;

//-------------------------------------------
void setup()
{
  Serial.begin(115200);
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
    triangulo = ps2x.Button(PSB_TRIANGLE);
    Up = ps2x.Button(PSB_PAD_UP);
    Down = ps2x.Button(PSB_PAD_DOWN);    
    motorCalc();   
  }      
}
//-----------------------------------------
inline void motorCalc()
{
  data.RSYVal = RSYVal;
  data.LSYVal = LSYVal;
  data.triangulo = triangulo;
  data.Up = Up;
  data.Down = Down;
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

