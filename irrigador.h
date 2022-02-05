/* **********************************************************************************************/
/* File name:        irrigador.h                                                                */
/* File description: Declarações para a classe que representa o sistema de irrigacao            */
/* Author name:      Renato Pepe                                		                        */
/* Creation date:    04/02/2022                                                                 */
/* Revision date:    05/02/2022                                                                 */
/* **********************************************************************************************/

#ifndef IRRIGADOR_H
#define IRRIGADOR_H



/* ******************************************************* */
/* Class name:  irrigador                                  */
/* Class description: representa o sistema de irrigacao    */
/* ******************************************************* */
class irrigador {

	//Status do irrigador, se ele está liberando água ou se está apenas checando a umidade
	bool bStatus; //false = aguando, true = checando umidade
	//Contador de tempo responsável por controlar o tempo que a valvula ficará aberta em cada ciclo de irrigação
	unsigned long ulTimerIrrigar;


public:

  /* *********************************************************************** */
  /* Method name:        setup                                               */
  /* Method description: Configura e inicializa o atuador, deve ser          */
  /*                      chamada no setup do programa                       */
  /* Input params:       n/a                                                 */
  /* Output params:      n/a                                                 */
  /* *********************************************************************** */
	void setup();    

  /* ************************************************************************** */
  /* Method name:        loopCall                                               */
  /* Method description: Controla o sistema de irrigação, checa a umidade do    */
  /*				       solo e abre a valvula para irrigar caso necessario   */
  /* Input params:       n/a                                                    */
  /* Output params:      n/a                                                    */
  /* ****************************************************************************/
	void loopCall();

};




#endif