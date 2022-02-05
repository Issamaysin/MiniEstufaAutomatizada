/* ******************************************************************************/
/* File name:        ledGrow.h                                                  */
/* File description: Header para classe que permite controlar a lampada grow    */
/*                    obs: Lampada está conectada no Normalmente aberto do relé */
/* Author name:      Renato Pepe                                                */
/* Creation date:    11/10/2021                                                 */
/* Revision date:    11/10/2021                                                 */
/* ******************************************************************************/

#ifndef LEDGROW_H
#define LEDGROW_H

//Descomentar este define para debug, irá imprimir variaveis no monitor serial
//#define debug

/* ***************************************************** */
/* Class name:  ledGrow                                  */
/* Class description: Representa a lampada grow que é    */
/*                     responsável por iluminar a planta */
/* ***************************************************** */
class ledGrow
{
	/*
   * Status da lampada 
   *  false = off , true = on
	*/
	bool bStatus;
 
	/*
   * Por quanto tempo a lampada ficará ligada (em horas)
	 */
	float fTimeOn;
	
  /*
   * Variavel responsável por contar o tempo na função loopCall
   */
	unsigned long ulTimeElapsed;


public:

  /*
   * Gets and sets das variaveis de status e tempo
   */
	void set_Status(bool bStatus);
	bool get_Status();
	void set_TimeOn(float fTimeOn);
  float get_TimeOn();

	
/* ********************************************************************************** */
/* Method name:        ledGrow                                                        */
/* Method description: Construtor que configura e inicializa a lampada                */
/* Input params:       n/a                                                            */
/* Output params:      n/a                                                            */
/* ********************************************************************************** */
	ledGrow();

/* ****************************************************************** */
/* Method name:        loopCall                                       */
/* Method description: Funcao que deverá ser chamada no loop para     */
/*                      controlar a lampada                           */
/* Input params:       n/a                                            */
/* Output params:      n/a                                            */
/* ****************************************************************** */
	void loopCall();
};


/* ********************************************************************* */
/* Method name:        convertHoursToMillis                              */
/* Method description: Converte um numero em horas para milisegundos     */
/* Input params:       float fHoras: número em horas que será convertido */
/* Output params:      unsigned long: input convertida para ms           */
/* ********************************************************************* */
unsigned long convertHoursToMillis(float fHoras);


#endif
