/* ****************************************************************************************/
/* File name:        sensorTemperatura.h                                                  */
/* File description: Declarações para a classe wrapper do sensor de temperatura           */
/*                    obs: colocar nomeVariavelSensor.setup(pinoDoSensor) no setup        */
/*                        e ler temperatura em ºC com nomeVariavelSensor.lerTemperatura() */
/* Author name:      Renato Pepe                                                          */
/* Creation date:    11/10/2021                                                           */
/* Revision date:    13/10/2021                                                           */
/* ****************************************************************************************/

#ifndef SENSORTEMP_H
#define SENSORTEMP_H

#include "OneWire.h"
#include "DallasTemperature.h"

/* ******************************************************* */
/* Class name:  sensorTemp                                 */
/* Class description: Wrapper para o sensor de temperatura */
/* ******************************************************* */
class sensorTemp
{
  /* objeto endereco para leitura do sensor (biblioteca OneWire.h) */
  DeviceAddress daEndereco;

  /* objeto da classe OneWire (biblioteca OneWire.h) */
  OneWire owOneWire;

  /* objeto da classe DallasTemperature que representa o sensor (biblioteca DallasTemperature.h) */
  DallasTemperature dtSensor;


public:

  /* ********************************************************************** */
  /* Method name:        setup                                              */
  /* Method description: Configura e inicializa os objetos necessários para */
  /*                      a leitura do sensor de temperatura                */
  /* Input params:       iPinSensor: pino onde o sensor está conectado      */
  /* Output params:      n/a                                                */
  /* ************************************************************************/
  void setup(int iPinSensor);

  /* ********************************************************************** */
  /* Method name:        lerTemperatura                                     */
  /* Method description: realiza leitura da temperatura                     */
  /* Input params:       n/a                                                */
  /* Output params:      float : valor da temperatura em gruas Celsius      */
  /* ************************************************************************/
  float lerTemperatura();

};

#endif
