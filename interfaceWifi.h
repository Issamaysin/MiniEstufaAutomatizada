/* **********************************************************************************************/
/* File name:        interface.h                                                                */
/* File description: Declaracoes das funcoes que controlam a interface wifi                     */
/* Author name:      Renato Pepe                                		                        */
/* Creation date:    10/11/2021                                                                 */
/* Revision date:    05/02/2022                                                                 */
/* **********************************************************************************************/


#ifndef INTERFACEWIFI_H
#define INTERFACEWIFI_H


void arduinoIOTCloudSetup();



  /* ***************************************************************************************/
  /* Method name:        receiveComand                                  				   */
  /* Method description: Interpreta o comando do usuário e executa o pedido se for válido, */
  /*                      e imprime mensagem de erro se nao for um comando valido          */
	 /*	~Formato do código: #AABCC+
	 *  	#   : Sinaliza o começo de um código, para filtrar strings aleatórias (1 digito)
	 *		AA  : Parametro que será alterado ou consultado (2 digitos)
	 *		B   : 'g' ou 's' -> get ou set, diz se o usuário pretende alterar um parametro ou ler um valor (1 digito)
	 *      CC  : se o B for igual a set CC terá o valor que será setado no parametro, representado por um numero inteiro com dois digitos.
	 *		+   : Caracter que sinaliza que um código finalizou
	 *
	 *		AA: Parametros: -Temperatura máxima : tx
	 *						-Temperatura minima : tn
	 *						-Temperatura atual  : ta
	 *						-Tempo da lampada   : lt
	 *						-Umidade da terra   : ut
	 *                      -Status da agua     : as
	 *                      -Status da luz      : SL
	 *          			-Status do aquecedor: SA
	 *						-Status do cooler 	: SC
	 *
	 *		B : Parametros: -Get: g
	 *						-Set  s
	 *
	 *		CC: Numero inteiro com dois digitos.
	 */
  /* Input params:       char cCode: string que contem o código                             */
  /* Output params:      n/a                												*/
  /* ****************************************************************************************/
void receiveComand(const char cCode[9]);





#endif



