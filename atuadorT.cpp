/* ******************************************************************************/
/* File name:        atuadorT.cpp                                               */
/* File description: Definições das funções relativas ao atuador de temperatura */
/* Author name:      Renato Pepe                                                */
/* Creation date:    15/10/2021                                                 */
/* Revision date:    15/10/2021                                                 */
/* ******************************************************************************/

#include <Arduino.h>
#include "atuadorT.h"

  /* *****************************************************************************/
  /* Method name:        set_Status                                              */
  /* Method description: Muda a variavel que guarda o estado do atuadorT e       */
  /*                      liga/desliga de acordo com o parametro de input        */
  /* Input params:       bool bStatus: status desejado (true = on | false = off) */
  /* Output params:      n/a                                                     */
  /* *****************************************************************************/
void atuadorT::set_Status(bool bStatus){
  
  /* Atualiza o status e liga/desliga o atuador */
  this->bStatus = bStatus;
  if (bStatus) {
    digitalWrite(iPinAtuador, HIGH);
  }
  else {
    digitalWrite(iPinAtuador, LOW);
  }

#ifdef debuggerSerial
  /* Imprime no serial monitor a mudança de status */
  if (bStatus) {
    Serial.println("Atuador foi ligado");
  }else{
    Serial.println("Atuador foi desligado");
  }
#endif
}

  /* **************************************************************************/
  /* Method name:        set_SetPoint                                         */
  /* Method description: Define um novo setpoint de temperatura               */
  /*                       obs: limitado entre 0C e 40C                       */
  /* Input params:       float fSetpoint: temperatura desejada                */
  /* Output params:      bool: true se foi setado corretamente e false caso   */
  /*                            o parametro esteja fora da faixa estabelecida */
  /* **************************************************************************/
bool atuadorT::set_SetPoint(float fSetPoint) {

  if (40.0f < fSetPoint || 0.0f > fSetPoint) {
  #ifdef debuggerSerial
    Serial.println("SetPoint não alterado, muito quente/frio para a planta");
  #endif
    return false;
  }

  this->fSetPoint = fSetPoint;

#ifdef debuggerSerial
  /* Imprime novo setpoint no serial monitor */
  Serial.print("SetPoint da temperatura = ");
  Serial.println(fSetPoint);
#endif

  return true;
}

  /* ******************************************************************/
  /* Method name:        get_Status                                   */
  /* Method description: Retorna o status do atuadorT, true = ligado  */
  /*                      e false = desligado                         */
  /* Input params:       n/a                                          */
  /* Output params:      bool: status atual do atuadorT               */
  /* ******************************************************************/
bool atuadorT::get_Status(){
  return bStatus;
}

  /* ******************************************************************/
  /* Method name:        get_SetPoint                                 */
  /* Method description: Retorna o setpoint configurado no atuadorT   */
  /* Input params:       n/a                                          */
  /* Output params:      float: setpoint previamente setado           */
  /* ******************************************************************/
float atuadorT::get_SetPoint() {
  return fSetPoint;
}



  /* *********************************************************************** */
  /* Method name:        setup                                               */
  /* Method description: Configura e inicializa o atuador, deve ser          */
  /*                      chamada no setup do programa                       */
  /* Input params:       int iPinAtuador: pino onde o atuador está conectado */
  /* Output params:      n/a                                                 */
  /* *********************************************************************** */
void atuadorT::setup(int iPinAtuador) {
  /* registra o pino do atuador na variavel (para que o set_Status consiga ligar/desligar o atuador) */
  this->iPinAtuador = iPinAtuador;

  /* Configura o pino que controla o aquecedor como output */
  pinMode(iPinAtuador, OUTPUT);

  /* Inicializa o aquecedor desligado com setPoint em 0ºC */
  set_Status(false);
  set_SetPoint(0.0f);
}
