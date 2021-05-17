
#include <EasyTransfer.h>
EasyTransfer ET;

struct rovData         // As variáveis dentro dessa struct são recebidas através de transmissão serial da placa que está na superfície.
{
  int RSYVal;          // Valor do bit referente ao eixo Y do direcional analógico direito. Iniciais do inglês, "Right Stick Y Value".
  int LSYVal;          // Valor do bit referente ao eixo y do direcional analógico esquerdo. Iniciais do inglês, "Left Stick Y Value".
  boolean triangulo;   // Botão triângulo
  boolean Up;          // Valor lógico referente ao botão "cima" do direcional digital.
  boolean Down;        // Valor lógico referente ao botão "baixo" do direcional digital.
}
data;

int LPWM_Output = 8;  //(pino 2 do BTS7960B) Entrada de controle PWM do lado esquerdo da ponte H. Rotação do eixo do Thruster 1 no sentido horário.
int RPWM_Output = 9;  //(pino 1 do BTS7960B) Entrada de controle PWM do lado direito da ponte H. Rotação do eixo do Thruster 1 no sentido anti-horário.

int LPWM_Output_2 = 6;  //(pino 2 do BTS7960B) Entrada de controle PWM do lado esquerdo da ponte H. Rotação do eixo do Thruster 2 no sentido horário.
int RPWM_Output_2 = 7;  //(pino 1 do BTS7960B) Entrada de controle PWM do lado direito da ponte H. Rotação do eixo do Thruster 2 no sentido anti-horário.

int LPWM_Output_3 = 3;  //(pino 2 do BTS7960B) Entrada de controle PWM do lado esquerdo da ponte H. Rotação do eixo do Thruster 3 no sentido horário.
int RPWM_Output_3 = 5;  //(pino 1 do BTS7960B) Entrada de controle PWM do lado direito da ponte H. Rotação do eixo do Thruster 3 no sentido anti-horário.

int RSYVal = 0;
int LSYVal = 0;
boolean Up = false;
boolean Down = false;
boolean triangulo = false;
int rele = 22;          //Relé conectado no pino 22 do Arduino MEGA
boolean estado_rele = LOW;

int ledPin = 13;        // Led indicador de liga/desliga
int ledState = LOW;
unsigned long previousMillis = 0;
unsigned long interval = 1000;
unsigned long lastComCheck = 0;
unsigned long lastComInterval = 1500;

void setup()
{
  Serial.begin(115200); 
  ET.begin(details(data), &Serial);

  pinMode(LPWM_Output, OUTPUT);
  pinMode(RPWM_Output, OUTPUT);

  pinMode(LPWM_Output_2, OUTPUT);
  pinMode(RPWM_Output_2, OUTPUT);

  pinMode(LPWM_Output_3, OUTPUT);
  pinMode(RPWM_Output_3, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);

}

void loop()
{
  unsigned long currentMillis = millis();
  if(ET.receiveData())
  {
    lastComCheck = millis();
    interval = 1000;


    /*                               Thruster 1                                              */
    /*****************************************************************************************/
    //Movimentação para frente
    if(data.LSYVal < 100){

      digitalWrite(LPWM_Output, HIGH);
      digitalWrite(RPWM_Output, LOW);              
    }
    // Parado
    else if(data.LSYVal >= 100 && data.LSYVal < 156){

      digitalWrite(LPWM_Output, LOW);
      digitalWrite(RPWM_Output, LOW);     
    }
    //Movimentação em Ré
    else{

      digitalWrite(LPWM_Output, LOW);
      digitalWrite(RPWM_Output, HIGH);       
    }    
    /*                               Thruster 2                                              */
    /*****************************************************************************************/
    //Movimentação para frente
    if(data.RSYVal < 100){

      digitalWrite(LPWM_Output_2, HIGH);
      digitalWrite(RPWM_Output_2, LOW);              
    }
    // Parado
    else if(data.RSYVal >= 100 && data.RSYVal < 156){

      digitalWrite(LPWM_Output_2, LOW);
      digitalWrite(RPWM_Output_2, LOW);      
    }
    //Movimentação em Ré
    else{

      digitalWrite(LPWM_Output_2, LOW);
      digitalWrite(RPWM_Output_2, HIGH);      
    }
    /*                               Thruster 3                                              */
    /*****************************************************************************************/
    if(data.Up){       // Sentido Direto                  

      digitalWrite(LPWM_Output_3, HIGH);
      digitalWrite(RPWM_Output_3, LOW);
    }

    else if(data.Down){      // Reverso      

      digitalWrite(LPWM_Output_3, LOW);
      digitalWrite(RPWM_Output_3, HIGH);      
    }

    else{                    // Parado

      digitalWrite(LPWM_Output_3, LOW);
      digitalWrite(RPWM_Output_3, LOW);
    }

    /*               Acionamento de Rele para Iluminação                                     */
    /*****************************************************************************************/
    if(data.triangulo == true){
      Serial.println(" ************** Triangulo Pressionado! **************");
      Serial.println(" **************     RELÉ ACIONADO! **************");
      delay(20);
      if(estado_rele == LOW){
        estado_rele = HIGH;
        digitalWrite(rele, !digitalRead(rele)); 
      }
    }
    else{
      estado_rele = LOW; 
    }
  }

  /*****************************************************************************************/

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
  digitalWrite(LPWM_Output, LOW);
  digitalWrite(RPWM_Output, LOW);
  digitalWrite(LPWM_Output_2, LOW);
  digitalWrite(RPWM_Output_2, LOW);
  digitalWrite(LPWM_Output_3, LOW);
  digitalWrite(RPWM_Output_3, LOW);
}
//--------------------------------------


