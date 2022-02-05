/* *******************************************************************************/
/* File name:        ledGrow.h                                                   */
/* File description: Definições para classe que permite controlar a lampada grow */
/*                    obs: Lampada está conectada no Normalmente aberto do relé  */
/* Author name:      Renato Pepe                                                 */
/* Creation date:    11/10/2021                                                  */
/* Revision date:    11/10/2021                                                  */
/* *******************************************************************************/



#include <Arduino.h>
#include "ledGrow.h"
#include "board.h"



/* ********************************************************************************** */
/* Method name:        ledGrow                                                        */
/* Method description: Construtor que configura e inicializa a lampada                */
/* Input params:       n/a                                                            */
/* Output params:      n/a                                                            */
/* ********************************************************************************** */
ledGrow::ledGrow() {
  //seta o pin que controla a lampada como output
  pinMode(PIN_LAMPADA, OUTPUT);
  
	//Inicia com tempo 0
	set_TimeOn(0.0f);
  
	//Status sempre inicializa no desligado
	set_Status(false);

  //inicializa o contador de tempo
  ulTimeElapsed = millis();

#ifdef debug
  //Imprime info no Serial pra testes
	Serial.print("lampada inicializada, tempo on = ");
	Serial.println(fTimeOn);
#endif

}

/* ********************************************************************************* */
/* Method name:        set_Status                                                    */
/* Method description: Seta a variavel de status da lampada e liga/desliga de acordo */
/* Input params:       bool bStatus: status da lampada, true = on | false = off     */
/* Output params:      n/a                                                           */
/* ********************************************************************************* */
void ledGrow::set_Status(bool bStatus) {
  
	this->bStatus = bStatus;
  if(true == bStatus){
    digitalWrite(PIN_LAMPADA, LOW);
  }else{
    digitalWrite(PIN_LAMPADA, HIGH);
  }
}

/* **************************************************************************************** */
/* Method name:        set_TimeOn                                                           */
/* Method description: Seta a variavel de tempo da lampada                                  */
/* Input params:       float fTimeOn: quanto tempo (em horas) a lampada deverá ficar ligada */
/* Output params:      n/a                                                                  */
/* **************************************************************************************** */
void ledGrow::set_TimeOn(float fTimeOn) {
	if (0 <= fTimeOn && 24 >= fTimeOn) {
		this->fTimeOn = fTimeOn;
	}
	else {
		this->fTimeOn = 0.0f;
	}
}

/* ********************************************************************************* */
/* Method name:        get_Status                                                    */
/* Method description: Retorna a variavel de status para saber como a lampada está   */
/* Input params:       n/a                                                           */
/* Output params:      bool: status atual da lampada                                 */
/* ********************************************************************************* */
bool ledGrow::get_Status() {
	return bStatus;
}


/* ********************************************************************************* */
/* Method name:        get_TimeOn                                                    */
/* Method description: Retorna a variavel de tempo da lampada                        */
/* Input params:       n/a                                                           */
/* Output params:      float: quanto tempo a lampada ficará ligada (em horas)        */
/* ********************************************************************************* */
float ledGrow::get_TimeOn() {
	return fTimeOn;
}


/* ****************************************************************** */
/* Method name:        loopCall                                       */
/* Method description: Funcao que deverá ser chamada no loop para     */
/*                      controlar a lampada                           */
/* Input params:       n/a                                            */
/* Output params:      n/a                                            */
/* ****************************************************************** */
void ledGrow::loopCall() {

#ifdef debug
  //Imprime info no Serial pra testes.
	Serial.print("millis =");
	Serial.print(millis());
	Serial.print("  timeElapsed =");
	Serial.println(ulTimeElapsed);
#endif

  /*
   * Atualiza o contador do tempo a cada 24 horas
   */
	if (convertHoursToMillis(24.0f) < (millis() - ulTimeElapsed)) {
		ulTimeElapsed = millis();
	}

  /*
   * Condição para quando está no tempo da lampada ficar ligada
   */
	if (millis() < (ulTimeElapsed + convertHoursToMillis(get_TimeOn())) && false == get_Status()) {
		set_Status(true);
	}

  /*
   * Condição para quando está no tempo da lampada ficar desligada
   */
	if (millis() > (ulTimeElapsed + convertHoursToMillis(get_TimeOn())) && true == get_Status()) {
		set_Status(false);
	}
}

/* ********************************************************************* */
/* Method name:        convertHoursToMillis                              */
/* Method description: Converte um numero em horas para milisegundos     */
/* Input params:       float fHoras: número em horas que será convertido */
/* Output params:      unsigned long: input convertida para ms           */
/* ********************************************************************* */
unsigned long convertHoursToMillis(float fHoras) {
	return (unsigned long)(fHoras * 60 * 60 * 1000);
}
