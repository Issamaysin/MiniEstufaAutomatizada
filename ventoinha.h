/* **********************************************************************************************/
/* File name:        ventoinha.h                                                                */
/* File description: Declarações para a classe que representa a ventoinha                       */
/*                    obs: dar o .setup(int pino) no inicio e chamar loopCall(temperatura atual)*/
/*                          para ela ligar/desligar quando precisar                             */
/* Author name:      Renato Pepe                                		                        */
/* Creation date:    14/10/2021                                                                 */
/* Revision date:    15/10/2021                                                                 */
/* **********************************************************************************************/

#ifndef VENTOINHA_H
#define VENTOINHA_H

#include "atuadorT.h"


/* ******************************************************* */
/* Class name:  ventoinha                                  */
/* Class description: representa a ventoinha do sistema    */
/* ******************************************************* */
class ventoinha: public atuadorT
{
public:


  /* ************************************************************************** */
  /* Method name:        loopCall                                               */
  /* Method description: Controla a ventoinha, ligando ou desligando de acordo  */
  /*                      com a relação entre o setpoint e a temperatura medida */
  /*                      obs: realiza a operação a cada 500ms                  */
  /* Input params:       float fTemperatura: temperatura atual do sistema       */
  /* Output params:      n/a                                                    */
  /* ****************************************************************************/
  void loopCall(float fTemperatura);
};



#endif
