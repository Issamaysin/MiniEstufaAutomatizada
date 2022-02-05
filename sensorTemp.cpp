/* ******************************************************************************/
/* File name:        sensorTemperatura.cpp                                      */
/* File description: Definições das funções relativas ao sensor de temperatura  */
/* Author name:      Renato Pepe                                                */
/* Creation date:    11/10/2021                                                 */
/* Revision date:    13/10/2021                                                 */
/* ******************************************************************************/

#include "board.h"
#include "sensorTemp.h"




  /* ********************************************************************** */
  /* Method name:        setup                                              */
  /* Method description: Configura e inicializa os objetos necessários para */
  /*                      a leitura do sensor de temperatura                */
  /* Input params:       iPinSensor: pino onde o sensor está conectado      */
  /* Output params:      n/a                                                */
  /* ************************************************************************/
void sensorTemp::setup(int iPinSensor){
    /* cria objeto da classe OneWire (biblioteca OneWire.h) */
  owOneWire = OneWire(iPinSensor);

  /* passa a referencia do objeto owOneWire para a biblioteca DallasTemperature.h */
  dtSensor = DallasTemperature(&owOneWire);

  /* inicia objeto dtSensor */
  dtSensor.begin();
}

/* ********************************************************************** */
/* Method name:        lerTemperatura                                     */
/* Method description: realiza leitura da temperatura                     */
/* Input params:       n/a                                                */
/* Output params:      float : valor da temperatura em gruas Celsius      */
/* ************************************************************************/
float sensorTemp::lerTemperatura() {


  float fT  = 0.0;

  /* comando para conversao de temperatura (biblioteca DallasTemperature.h) */
  dtSensor.requestTemperatures();

  /* realiza a leitura se o for verificada presenca do sensor */
  if (!dtSensor.getAddress(daEndereco, 0)) {
    //Valor para não alterar muito o sistema caso o sensor de temperatura não responda
    fT = 25.48;
    
  #ifdef debuggerSerial
  /* Imprime mensagem de erro no Serial monitor */
    //Serial.println("Sensor nao encontrado");
  #endif
  }
  else {
    fT = dtSensor.getTempC(daEndereco);
  }

  return fT;
}
