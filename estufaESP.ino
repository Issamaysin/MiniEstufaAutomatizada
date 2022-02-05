/* *******************************************************************************/
/* File name:        estufaESP.ino                                               */
/* File description: Arquivo main onde os objetos são declarados, inicializados, */
/*                    e suas funções de controle são chamadas periodicamente     */
/* Author name:      Renato Pepe                                                 */
/* Creation date:    08/10/2021                                                  */
/* Revision date:    05/02/2022                                                  */
/* *******************************************************************************/

#include "board.h"
#include "sensorTemp.h"
#include "aquecedor.h"
#include "ventoinha.h"
#include "ledGrow.h"
#include "irrigador.h"
#include "interfaceWifi.h"
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

/* Objetos dos atuadores e sensores */
aquecedor aquecedor;
ventoinha cooler;
sensorTemp sensorT;
ledGrow luz;
irrigador irrigas;

extern bool flag_WifiCommand;
extern float tempAtual;
extern String stControlCode;

//Variavel que controla a periodicidade da chamada dos atuadores
unsigned long ulLoopCallCooldown = 0;


void setup() {
  //Setup do serial para debugger
  Serial.begin(115200);
  delay(50);
  
  //Setup da comunicação wifi
  arduinoIOTCloudSetup();
  delay(50);
  
  //setup do aquecedor, cooler, sensor de temperatura, e modulo de irrigacao
  aquecedor.setup(PIN_AQUECEDOR);
  cooler.setup(PIN_COOLER);
  sensorT.setup(PIN_SENSOR_TEMPERATURA);
  irrigas.setup();
 
  //inicializa cooler mantendo temp abaixo de 28C
  cooler.set_SetPoint(28.0f);
        
  //inicializa aquecedor mantendo a temperatura acima de 20C
  aquecedor.set_SetPoint(20.0f);
 
  //inicializa luz com tempo de 15horas ligadas por dia
  luz.set_TimeOn(15.0f);

    
  
  //faz uma chamada inicial dos atuadores: aquecedor, cooler, lampada, e irrigador
  tempAtual = sensorT.lerTemperatura();
  luz.loopCall();
  aquecedor.loopCall(tempAtual);
  cooler.loopCall(tempAtual);
  irrigas.loopCall();
}



void loop() {
  ArduinoCloud.update();

  //salva tmeperatura atual na variavel
  tempAtual = sensorT.lerTemperatura();

  //Se algum comando foi enviado pelo usuário, repassa a string contendo o comando para a função que trata inputs
  if(flag_WifiCommand){
    //Reseta flag e invoca a função para ler o comando
    flag_WifiCommand = false;
    receiveComand(stControlCode.c_str());
  }

  //faz chamada dos atuadores: aquecedor, cooler, lampada, e irrigador. Tem cooldown de 10 segundos
  if(millis() - ulLoopCallCooldown > 10000){  
    //Alerta caso a temperatura esteja critica
    if(tempAtual > 40.0f){
      stControlCode = "ALERTA: temperatura está muito alta";
    }else if(tempAtual < 0.0f){
      stControlCode = "ALERTA: temperatura está muito baixa";
    }

    //Chamada dos atuadores
    luz.loopCall();
    aquecedor.loopCall(tempAtual);
    cooler.loopCall(tempAtual);
    irrigas.loopCall();
  
    //Reseta cooldown 
    ulLoopCallCooldown = millis();
  }
}
