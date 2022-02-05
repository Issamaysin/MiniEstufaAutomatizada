/* **********************************************************************************************/
/* File name:        aquecedor.h                                                                */
/* File description: Declarações para a classe que representa o aquecedor                       */
/*                    obs: dar o .setup(int pino) no inicio e chamar loopCall(temperatura atual)*/
/*                          para ele ligar/desligar quando precisar                             */
/* Author name:      Renato Pepe                                                                */
/* Creation date:    14/10/2021                                                                 */
/* Revision date:    15/10/2021                                                                 */
/* **********************************************************************************************/

#ifndef AQUECEDOR_H
#define AQUECEDOR_H

#include "atuadorT.h"


/* ******************************************************* */
/* Class name:  aquecedor                                  */
/* Class description: representa o aquecedor do sistema    */
/* ******************************************************* */
class aquecedor: public atuadorT
{
public:


  /* ************************************************************************** */
  /* Method name:        loopCall                                               */
  /* Method description: Controla o aquecedor, ligando ou desligando de acordo  */
  /*                      com a relação entre o setpoint e a temperatura medida */
  /* Input params:       float fTemperatura: temperatura atual do sistema       */
  /* Output params:      n/a                                                    */
  /* ****************************************************************************/
  void loopCall(float fTemperatura);
};



#endif
