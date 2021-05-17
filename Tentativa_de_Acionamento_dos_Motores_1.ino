
#include <PS2X_lib.h>  //for v1.6


/******************************************************************
 * set pins connected to PS2 controller:
 *   - 1e column: original 
 *   - 2e colmun: Stef?
 * replace pin numbers by the ones you use
 ******************************************************************/
#define PS2_DAT        7  //14    
#define PS2_CMD        6  //15
#define PS2_SEL        5  //16
#define PS2_CLK        3  //17

/******************************************************************
 * select modes of PS2 controller:
 *   - pressures = analog reading of push-butttons 
 *   - rumble    = motor rumbling
 * uncomment 1 of the lines for each mode selection
 ******************************************************************/
#define pressures   true
//#define pressures   false
#define rumble      true
//#define rumble      false

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you connect the controller, 
//or call config_gamepad(pins) again after connecting the controller.

int error = 0;
byte type = 0;
byte vibrate = 0;

/*Variáveis abaixo utilizadas para a propulsão dos thrusters*/
int RSYVal = 0;
int LSYVal = 0;
int motor_speed = 9;
int motor_speed_2 = 10;
int led1 = 9; /* led simulando thruster da direita*/
int led2 = 10;
/*int led2; /* led simulando thruster da esquerda*/
int brightness = 0; /* Brilho simulando velocidade do motor*/
int brightness_2 = 0;


/*int farol = 8; /* Pino 8 usado como LED do ROV*/ 
/*
boolean R2_antes = LOW; /*Estado inicial do R2
boolean R2_atual = LOW; /*Estado do botão R2
boolean estado_led = LOW;
boolean leitura;
long time = 0;  // the last time the output pin was toggled
long debounce = 50;    // the debounce time; increase if the output flickers
*/


void setup(){

  
  Serial.begin(57600);
  

  pinMode(motor_speed, OUTPUT);
  pinMode(motor_speed_2, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  
  
  
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
   
  //CHANGES for v1.6 HERE!!! **************PAY ATTENTION*************
  
  //setup pins and settings: GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
	if (pressures)
	  Serial.println("true ");
	else
	  Serial.println("false");
	Serial.print("rumble = ");
	if (rumble)
	  Serial.println("true)");
	else
	  Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
//  Serial.print(ps2x.Analog(1), HEX);
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
}

void loop() {
  
  
  /* You must Read Gamepad to get new values and set vibration values
     ps2x.read_gamepad(small motor on/off, larger motor strenght from 0-255)
     if you don't enable the rumble, use ps2x.read_gamepad(); with no values
     You should call this at least once a second
   */  
  if(error == 1) //skip loop if no controller found
    return; 
  
  if(type == 2){ 
    //Guitar Hero Controller
    }

  else { //DualShock Controller
    ps2x.read_gamepad(false, vibrate); //read controller and set large motor to spin at 'vibrate' speed
        
    if(ps2x.Button(PSB_START))         //will be TRUE as long as button is pressed
      Serial.println("Start is being held");
      
    if(ps2x.Button(PSB_SELECT))
      Serial.println("Select is being held");      

    if(ps2x.Button(PSB_PAD_UP)) {      //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
    }   

    vibrate = ps2x.Analog(PSAB_CROSS);  //this will set the large motor vibrate speed based on how hard you press the blue (X) button
    if (ps2x.NewButtonState()) {        //will be TRUE if any button changes state (on to off, or off to on)
      if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
      if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
      if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
      if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
      if(ps2x.Button(PSB_TRIANGLE))
        Serial.println("Triangle pressed");        
    }

    if(ps2x.ButtonPressed(PSB_CIRCLE))               //will be TRUE if button was JUST pressed
      Serial.println("Circle just pressed");
    if(ps2x.NewButtonState(PSB_CROSS))               //will be TRUE if button was JUST pressed OR released
      Serial.println("X just changed");
    if(ps2x.ButtonReleased(PSB_SQUARE))              //will be TRUE if button was JUST released
      Serial.println("Square just released");     

    if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) { //print stick values if either is TRUE
      Serial.print("Stick Values:");
      Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_LX), DEC); 
      Serial.print(",");
      Serial.print(ps2x.Analog(PSS_RY), DEC); 
      Serial.print(",");
      Serial.println(ps2x.Analog(PSS_RX), DEC); 
    }
    
    /* *************** Início do Acionamento da Iluminação LED ******************* */
/*     int switchstate;
     
     leitura = ps2x.ButtonPressed(PSB_R2);
     
     if(leitura != R2_antes)
     {
      time = millis(); 
     }
 
     if ((millis() - time) > debounce)
     {
       switchstate = leitura;
       
       if (switchstate == HIGH && R2_atual == LOW) 
       {
       R2_atual = HIGH;
         if (estado_led == HIGH) 
            {
            estado_led = LOW;
            } 
         else
            {
            estado_led = HIGH;
            }
       }
       if (switchstate == LOW && R2_atual == HIGH) 
       {
       R2_atual = LOW;
       }
     }
       digitalWrite(farol, estado_led);
       R2_antes = leitura; 
 
    /* *************** Final do Acionamento da Iluminação LED ******************* */
    
    
   /* No trecho abaixo (até a chave do último 'else') é feita a conversão do valor do bit 
   de posição com o valor da velocidade do motor, no sentido direto e reverso. Para visualização do efeito, um aumento
   no brilho do led foi inserido. O pino do led é declarado como o mesmo do motor.
   */
   
   
   /* ************* Início do controle do motor da direita ******************** */
   
   
     LSYVal = ps2x.Analog(PSS_LY); //LSYVal = Left Stick Y Value; controlará direção do motor da esquerda.
     RSYVal = ps2x.Analog(PSS_RY); //RSYVal = Right Stick Y Value; controlará direção do motor da direita;

     if(RSYVal<100){                               // Sentido Direto
      Serial.println("O valor do bit na posição atual e: "); 
      Serial.println(RSYVal, DEC);
      int motor_speed = map(RSYVal,0,99,99,0);
      Serial.println("A velocidade de 0 a 99 bits atual do thruster da direita, no sentido direto e: ");
      Serial.println(motor_speed, DEC);
          digitalWrite(led1, LOW);    
          byte brightness;     
          brightness = motor_speed;
          analogWrite(led1, brightness);
        }
        
     else if(RSYVal>=100 && RSYVal<156){
          digitalWrite(led1, LOW);
          Serial.println("Analogico na posicao Neutra!!");
     }
     
     else{                                        // Sentido Reverso
          Serial.println("O valor do bit na posição atual e: "); 
          Serial.println(RSYVal, DEC); //analógico direito
          int motor_speed = map(RSYVal,156,255,0,99);
          Serial.println("A velocidade de 0 a 99 bits atual do thruster da direita, no sentido reverso e: ");
          Serial.println(motor_speed, DEC);
              digitalWrite(led1, LOW);    
              byte brightness;     
              brightness = motor_speed;
              analogWrite(led1, brightness);
     }
     
     /* ************* Fim do controle do motor da direita ******************** */
     
     
     /* ************* Início do controle do motor da esquerda ******************** */

     if(LSYVal<100){                                         // Sentido Direto
      Serial.println("O valor do bit na posição atual e: "); 
      Serial.println(LSYVal, DEC); //analógico esquerdo
      int motor_speed_2 = map(LSYVal,0,99,99,0);
      Serial.println("A velocidade de 0 a 99 bits atual do thruster da direita, no sentido direto e: ");
      Serial.println(motor_speed_2, DEC);
          digitalWrite(led2, LOW);    
          byte brightness_2;     
          brightness_2 = motor_speed_2;
          analogWrite(led2, brightness_2);
        }
        
     else if(LSYVal>=100 && LSYVal<156){
          digitalWrite(led2, LOW);
          Serial.println("Analogico na posicao Neutra!!");
     }
     
     else{                                                    // Sentido Reverso
          Serial.println("O valor do bit na posição atual e: "); 
          Serial.println(LSYVal, DEC); //analógico direito
          int motor_speed_2 = map(LSYVal,156,255,0,99);
          Serial.println("A velocidade de 0 a 99 bits atual do thruster da direita, no sentido reverso e: ");
          Serial.println(motor_speed_2, DEC);
              digitalWrite(led2, LOW);    
              byte brightness_2;     
              brightness_2 = motor_speed_2;
              analogWrite(led2, brightness_2);
     }
     /******************* Fim do controle do motor da esquerda ****************/
  }
}
