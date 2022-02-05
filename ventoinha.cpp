/* ******************************************************************************/
/* File name:        ventoinha.cpp                                              */
/* File description: Definições das funções relativas a ventoinha               */
/* Author name:      Renato Pepe                                                */
/* Creation date:    14/10/2021                                                 */
/* Revision date:    15/10/2021                                                 */
/* ******************************************************************************/

#include <Arduino.h>
#include "ventoinha.h"


  


  /* ************************************************************************** */
  /* Method name:        loopCall                                               */
  /* Method description: Controla a ventoinha, ligando ou desligando de acordo  */
  /*                      com a relação entre o setpoint e a temperatura medida */
  /*                      obs: realiza a operação a cada 500ms                  */
  /* Input params:       float fTemperatura: temperatura atual do sistema       */
  /* Output params:      n/a                                                    */
  /* ****************************************************************************/
void ventoinha::loopCall(float fTemperatura){

  /* Verifica se precisa ligar/desligar a ventoinha */

  /* se o a temperatura atual está maior que o setpoint e a ventoinha está desligada->liga a ventoinha */
  if (get_SetPoint() < fTemperatura && false == get_Status()) {
    set_Status(true);
  }
   /* se a temperatura atual está menor que o setpoint e a ventoinha está ligado->desliga a ventoinha */
  else if (get_SetPoint() >= fTemperatura && true == get_Status()) {
    set_Status(false);
  }
  
}

void onStDataStorageChange(){}

