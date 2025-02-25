// INCLUSÃO DE BIBLIOTECAS
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// DEFINIÇÕES DE PINOS
#define pinRx 10 //informe aqui qual porta Rx está sendo utilizada.
#define pinTx 11 //informe aqui qual porta Tx está sendo utilizada.



#define button 1 //definimos a saída digital 1 com o nome de Button.
#define button2 2 //definimos a saída digital 2 com o nome de Button2.

// DEFINIÇÕES
#define volumeMP3 30 //definimos o volume, entre 0 e 30.

#define DEBUG
// INSTANCIANDO OBJETOS
SoftwareSerial playerMP3Serial(pinRx, pinTx);

DFRobotDFPlayerMini playerMP3;


// DECLARAÇÃO DE FUNÇÕES


// DECLARAÇÃO DE VARIÁVEIS  


void setup() {
  pinMode(button, INPUT); //declaramos Button como INPUT.
  pinMode(button2, INPUT); //declaramos Button como INPUT.
  

  Serial.begin(9600);
  playerMP3Serial.begin(9600);

  Serial.println();
  Serial.println(F("Iniciando DFPlayer ... (Espere 3~5 segundos)"));

  if (!playerMP3.begin(playerMP3Serial)) {  // COMUNICAÇÃO REALIZADA VIA SOFTWARE SERIAL
    Serial.println(F("Falha:"));
    Serial.println(F("1.conexões!"));
    Serial.println(F("2.cheque o cartão SD!"));
    while(true){
      delay(0);
    }
  }

  Serial.println(F("DFPlayer iniciado!"));

  playerMP3.volume(volumeMP3);
  
  #ifdef DEBUG
    Serial.println("o Setup acabou");
  #endif  
 
  delay(5000);

  playerMP3.playFolder(1, 1);

}




















void loop() {
 return;
 delay (1000);
  
 delay(5000);

 playerMP3.playFolder(2, 1);
    Serial.println("Tocando pasta 02, musica 001");
    delay(1000);
    while(1){

    }
 return;

    if (digitalRead(button) == HIGH){
    
    }
    if (digitalRead(button2) == HIGH){
    playerMP3.playFolder(2, 2);
    Serial.println("Tocando pasta 02, musica 001");
    delay(1000);
    }  
}