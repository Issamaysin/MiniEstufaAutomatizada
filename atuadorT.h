/* ****************************************************************************************/
/* File name:        atuadorT.h                                                           */
/* File description: Declarações para a classe que representa os atuadores de temperatura */
/* Author name:      Renato Pepe                                                          */
/* Creation date:    15/10/2021                                                           */
/* Revision date:    15/10/2021                                                           */
/* ****************************************************************************************/

#ifndef ATUADORT_H
#define ATUADORT_H

/* ******************************************************* */
/* Class name:  atuadorT                                   */
/* Class description: representa um atuador de temperatura */
/* ******************************************************* */
class atuadorT
{
  /* status do atuador, on = true | off = false */
  bool bStatus;
  
  /* Temperatura que se dejesa chegar (aquecedor tentará manter o sistema acima do setpoint e a ventoinha abaixo) */
  float fSetPoint;

  /* Pino onde o atuador está conectado */
  int iPinAtuador;

public:

  
  /* *****************************************************************************/
  /* Method name:        set_Status                                              */
  /* Method description: Muda a variavel que guarda o estado do atuadorT e       */
  /*                      liga/desliga de acordo com o parametro de input        */
  /* Input params:       bool bStatus: status desejado (true = on | false = off) */
  /* Output params:      n/a                                                     */
  /* *****************************************************************************/
  void set_Status(bool bStatus);

  /* **************************************************************************/
  /* Method name:        set_SetPoint                                         */
  /* Method description: Define um novo setpoint de temperatura               */
  /*                       obs: limitado entre 0C e 40C                       */
  /* Input params:       float fSetpoint: temperatura desejada                */
  /* Output params:      bool: true se foi setado corretamente e false caso   */
  /*                            o parametro esteja fora da faixa estabelecida */
  /* **************************************************************************/
  bool set_SetPoint(float fSetPoint);

  /* ******************************************************************/
  /* Method name:        get_Status                                   */
  /* Method description: Retorna o status do atuadorT, true = ligado  */
  /*                      e false = desligado                         */
  /* Input params:       n/a                                          */
  /* Output params:      bool: status atual do atuadorT               */
  /* ******************************************************************/
  bool get_Status();

  /* ******************************************************************/
  /* Method name:        get_SetPoint                                 */
  /* Method description: Retorna o setpoint configurado no atuadorT   */
  /* Input params:       n/a                                          */
  /* Output params:      float: setpoint previamente setado           */
  /* ******************************************************************/
  float get_SetPoint();


  /* *********************************************************************** */
  /* Method name:        setup                                               */
  /* Method description: Configura e inicializa o atuador, deve ser          */
  /*                      chamada no setup do programa                       */
  /* Input params:       int iPinAtuador: pino onde o atuador está conectado */
  /* Output params:      n/a                                                 */
  /* *********************************************************************** */
  void setup(int iPinAtuador);
};

#endif
