/* **********************************************************************************************/
/* File name:        irrigador.h                                                                */
/* File description: Definições das funções relativas ao sistema de irrigação                   */
/* Author name:      Renato Pepe                                                                */
/* Creation date:    04/02/2022                                                                 */
/* Revision date:    05/02/2022                                                                 */
/* **********************************************************************************************/

#include <Arduino.h>
#include "board.h"
#include "irrigador.h"

//Niveis de umidade do vaso, valores obtidos de forma empirica e irão mudar para outros vasos e sensores
#define nivel_Baixo 660 //pouca agua, leituras acima desse valor indicam que a planta precisa ser aguada -> dita o inicio do clico de irrigacao
#define nivel_Alto 410   //saturado de agua, valor onde a irrigacao irá parar aguar -> dita a parada do ciclo de irrigacao


  /* *********************************************************************** */
  /* Method name:        setup                                               */
  /* Method description: Configura e inicializa o atuador, deve ser          */
  /*                      chamada no setup do programa                       */
  /* Input params:       n/a                                                 */
  /* Output params:      n/a                                                 */
  /* *********************************************************************** */
void irrigador::setup(){

  //Inicializa pino da valvula
  pinMode(PIN_VALVULA, OUTPUT);

  //Status inicial.
  bStatus = true; 

}


  /* ************************************************************************** */
  /* Method name:        loopCall                                               */
  /* Method description: Controla o sistema de irrigação, checa a umidade do    */
  /*               solo e abre a valvula para irrigar caso necessario   */
  /* Input params:       n/a                                                    */
  /* Output params:      n/a                                                    */
  /* ****************************************************************************/
void irrigador::loopCall(){

  int iNivelUmidade;

  /* Dois modos de operação, um apenas checa a umidade do solo, e o outro é o ciclo de irrigacao */
  if(bStatus){

    /*
     * Se a nivel da agua estiver acima do nivel_Baixo a planta está seca, portanto troca o modo de operação para inicar o ciclo de irrigacao, abre a valvula,
     *  e inicializa o timer
    */
    iNivelUmidade = analogRead(PIN_SENSOR_UMIDADE);

    if(iNivelUmidade >= nivel_Baixo){
        bStatus = false;
        digitalWrite(PIN_VALVULA, HIGH);
        ulTimerIrrigar = millis();
    }

    
    #ifdef debuggerSerial
    //Imprime o valor no monitor para checar os valores
      Serial.print("Nivel umidade solo (Estado checando): ");
      Serial.println(iNivelUmidade);
    #endif

  }else{

    //Se ainda nao passou os 5s que a valvula deve ficar aberta em casa ciclo não faz nada
    //Se já passou checa o nivel de agua, se ainda precisa aguar só reseta o timer, se nao precisar mais desliga a valvula e troca o modo de operação.
    if(millis() - ulTimerIrrigar > 5000){

      iNivelUmidade = analogRead(PIN_SENSOR_UMIDADE);
      
      #ifdef debuggerSerial
      //Imprime o valor no monitor para checar os valores
      Serial.print("Nivel umidade solo (Estado aguando): ");
      Serial.println(iNivelUmidade);
      #endif

      //se nivel umidade > nivel_Alto reseta timer, pois precisa aguar mais
      if(iNivelUmidade > nivel_Alto){
        ulTimerIrrigar = millis();
      }else{
        digitalWrite(PIN_VALVULA, LOW);
        bStatus = true;
      }
    
    }
  
  }
}






