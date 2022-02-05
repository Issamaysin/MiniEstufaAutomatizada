/* ******************************************************************************/
/* File name:        aquecedor.cpp                                              */
/* File description: Definições das funções relativas ao aquecedor              */
/* Author name:      Renato Pepe                                                */
/* Creation date:    14/10/2021                                                 */
/* Revision date:    15/10/2021                                                 */
/* ******************************************************************************/

#include <Arduino.h>
#include "aquecedor.h"

  /* ************************************************************************** */
  /* Method name:        loopCall                                               */
  /* Method description: Controla o aquecedor, ligando ou desligando de acordo  */
  /*                      com a relação entre o setpoint e a temperatura medida */
  /* Input params:       float fTemperatura: temperatura atual do sistema       */
  /* Output params:      n/a                                                    */
  /* ****************************************************************************/
void aquecedor::loopCall(float fTemperatura){
  /* Verifica se precisa ligar/desligar o aquecedor */
  
   /* se o a temperatura atual está menor que o setpoint e aquecedor está desligado->liga o aquecedor */
   if (get_SetPoint() > fTemperatura && false == get_Status()) {
     set_Status(true);
   }
   /* se a temperatura atual está maior que o setpoint e aquecedor está ligado->desliga o aquecedor */
   else if (get_SetPoint() <= fTemperatura && true == get_Status()) {
     set_Status(false);
   }
 }
