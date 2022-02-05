/* **********************************************************************************************/
/* File name:        interface.cpp                                                              */
/* File description: Definicoes das funcoes que controlam a interface wifi                      */
/* Author name:      Renato Pepe                                		                        */
/* Creation date:    10/11/2021                                                                 */
/* Revision date:    05/02/2022                                                                 */
/* **********************************************************************************************/

#ifndef INTERFACEWIFI_CPP
#define INTERFACEWIFI_CPP

#include "board.h"
#include "sensorTemp.h"
#include "aquecedor.h"
#include "ventoinha.h"
#include "ledGrow.h"
#include "thingProperties.h"
#include "interfaceWifi.h"
#include <string>

using namespace std;


/****  Variaveis globais ****/
//É setada quando uma string de comunicação é recebida pela cloud.
bool flag_WifiCommand = false; 


extern aquecedor aquecedor;
extern ventoinha cooler;
extern sensorTemp sensorT;
extern ledGrow luz;

  /* ****************************************************************************/
  /* Method name:        arduinoIOTCloudSetup                                   */
  /* Method description: Faz o setup da comunicação wifi com a cloud do arduino */
  /* Input params:       n/a                                          			*/
  /* Output params:      n/a 													*/
  /* ****************************************************************************/
void arduinoIOTCloudSetup(){


  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

}


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
void receiveComand(const char cCode[9]){



	 //Para a função caso o primeiro digito não seja o sinal de confirmação e imprime mensagem de erro
	 if('#' != cCode[0]){
	 	stControlCode = "Erro - mensage digitada não é um código de comando. (faltou #)";  
	 	return;
	 }

	 //Checa se o ultimo caracter digitado na string é igual ao simbolo de confirmação de finalização do código
	 unsigned char ucIterator = 0;
	 while((cCode[ucIterator++] != '\0') && (ucIterator < 8)){}

	 if((cCode[ucIterator - 2] != '+') || ucIterator > 8 ){
	 	stControlCode = "Erro - mensage digitada não é um código de comando. (faltou + ou estourou numero maximo de digitos)"; 
	 	return;
	 }



	 //O código AA passa por um hash para ser comparado em um switch-case.
	 int iVariableCode = cCode[1] + cCode[2];


	#define temperaturaMaxima ('t' + 'x')	 //#236
	#define temperaturaMinima ('t' + 'n')    //#226
	#define temperaturaAtual ('t' + 'a')	 //#213
	#define luzTempo ('l' + 't')			 //#224
	#define statusLuz ('S' + 'L')			 //#159
	#define statusAquecedor ('S' + 'A')		 //#148
	#define statusCooler ('S' + 'C')		 //#150
	#define tempoOnline ('o' + 't')			 //#228

	//String auxiliar para formar a mensagem
	String textAux;

	 switch(iVariableCode){
	 		/* 
	 		 * Temperatura minima: temperatura da qual o sistema deverá se manter acima
	 		 *  -get: retorna o valor do setpoint do aquecedor
	 		 *	-set: altera a temperatura minima desejada, valor passado como parametro deverá ser um numero inteiro
	 		 *   	  de dois digitos que esteja entre 0 e 40
	 		 *  (temperaturaMinima# = 226)
	 		*/
	 		case temperaturaMinima:
	 			//Imprime para o usuario o valor da temperatura minima setada atualmente
	 			if('g' == cCode[3]){
	 				//Imprime na interface a temperatura minima, que está setada na configuração do aquecedor
	 				textAux = String("Temp min: ") + String(aquecedor.get_SetPoint()) + String(" C");
	 			}
	 			//Altera o valor da temperatura minima setada no sistema.
	 			else if('s' == cCode[3]){
	 				//Checa se os caracteres referentes ao valor são digitos numéricos
	 				if(('0' <= cCode[4]) && ('9' >= cCode[4]) && ('0' <= cCode[5]) && ('9' >= cCode[5])){
	 			
		 				//transforma os caracteres no valor que eles representam mas agora na forma de um inteiro em decimal)
		 				unsigned char ucValorParametro = (cCode[5] - '0') + 10*(cCode[4] - '0'); //valor passado pelo usuario está aqui.

		 				//Só irá alterar se o valor estiver entre 0 e 40, que é a range de temperatura que o aquecedor aceita
		 				if((unsigned char)40 < ucValorParametro || (unsigned char)0 > ucValorParametro) {
		 					textAux = String("Erro - SetPoint não alterado, muito quente ou frio para a planta");
		 				}else{
							textAux = String("Temp min alterada para: ") + String(ucValorParametro) + String(" C");
		 					aquecedor.set_SetPoint((float)ucValorParametro);
		 				}
	 				}else{
	 					textAux = String("Erro - Valor invalido, caracteres não representam numeros");
	 				}

	 			}else{
	 				textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;

	 		/* 
	 		 * Temperatura maxima: temperatura da qual o sistema deverá se manter abaixo
	 		 *  -get: retorna o valor do setpoint do cooler
	 		 *	-set: altera a temperatura maxima desejada, valor passado como parametro deverá ser um numero inteiro
	 		 *   	  de dois digitos que esteja entre 0 e 40
	 		 *  (temperaturaMaxima# = 236)
	 		*/
	 		case temperaturaMaxima:
	 			 if('g' == cCode[3]){
	 				//Imprime na interface a temperatura maxima, que está setada na configuração do cooler
	 				textAux = String("Temp max: ") + String(cooler.get_SetPoint()) + String(" C");
	 			}else if('s' == cCode[3]){

					//Checa se os caracteres referentes ao valor são digitos numéricos
	 				if(('0' <= cCode[4]) && ('9' >= cCode[4]) && ('0' <= cCode[5]) && ('9' >= cCode[5])){
	 			
		 				//transforma os caracteres no valor que eles representam mas agora na forma de um inteiro em decimal)
		 				unsigned char ucValorParametro = (cCode[5] - '0') + 10*(cCode[4] - '0'); //valor passado pelo usuario está aqui.

		 				//Só irá alterar se o valor estiver entre 0 e 40, que é a range de temperatura que o aquecedor aceita
		 				if((unsigned char)40 < ucValorParametro || (unsigned char)0 > ucValorParametro) {
		 					textAux = String("Erro - SetPoint não alterado, muito quente ou frio para a planta");
		 				}else{
							textAux = String("Temp max alterada para: ") + String(ucValorParametro) + String(" C");
		 					cooler.set_SetPoint((float)ucValorParametro);
		 				}
	 				}else{
	 					textAux = String("Erro - Valor invalido, caracteres não representam numeros");
	 				}

	 			}else{
					textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;


	 		/* 
	 		 * Temperatura atual: temperatura registrada na ultima leitura do sensor
	 		 *  -get: retorna o valor da temperatura que é armazenado na variavel tempAtual
	 		 *	-set: não é possível alterar o valor da temperatura atual.
	 		 *  (temperaturaAtual# = 213)
	 		*/
	 		case temperaturaAtual:
	 			if('g' == cCode[3]){
	 				//Imprime na interface a temperatura atual, que está setada na variavel tempAtual
	 				textAux = String("Temp atual: ") + String(tempAtual) + String(" C");
	 			}else if('s' == cCode[3]){
	 				textAux = String("Erro - não é possível alterar o valor da temperatura atual");
	 			}else{
	 				textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;


	 		/* 
	 		 *  Tempo da lampada: quantas horas por dia a luz led grow ficará acesa.
	 		 *  -get: retorna o valor atual de quantas horas a luz ficará acesa, armazenado no objeto luz
	 		 *	-set: altera quantas horas a luz ficará ligada por dia
	 		 *  (luzTempo# = 224)
	 		*/
	 		case luzTempo:
	 			if('g' == cCode[3]){
					//Imprime na interface o valor em horas da lampada
	 				textAux = String("Tempo da lampada: ") + String(luz.get_TimeOn()) + String(" horas/dia");
	 			}else if('s' == cCode[3]){

					//Checa se os caracteres referentes ao valor são digitos numéricos
	 				if(('0' <= cCode[4]) && ('9' >= cCode[4]) && ('0' <= cCode[5]) && ('9' >= cCode[5])){
	 			
		 				//transforma os caracteres no valor que eles representam mas agora na forma de um inteiro em decimal)
		 				unsigned char ucValorParametro = (cCode[5] - '0') + 10*(cCode[4] - '0'); //valor passado pelo usuario está aqui.

		 				//Só irá alterar se o valor estiver entre 0 e 24, que é a range de valores aceita pela função
		 				if((unsigned char)24 < ucValorParametro || (unsigned char)0 > ucValorParametro) {
		 					textAux = String("Erro - valor deve estar entre 0 e 24");
		 				}else{
							textAux = String("Tempo da lampada alterado para: ") + String(ucValorParametro) + String(" horas/dia");
		 					luz.set_TimeOn((float)ucValorParametro);
		 				}
	 				}else{
	 					textAux = String("Erro - Valor invalido, caracteres não representam numeros");
	 				}
	 			}else{
	 				textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;

		
	 		/* 
	 		 *  Status da lampada: diz ao usuario se a lampada está ligada ou desligada no momento.
	 		 *  -get: retorna status atual da lampada, armazenado no objeto luz
	 		 *	-set: não habilitado, não é possivel alterar o status da lampada desta forma, o status é controlado
	 		 *	 	  apenas pelo código principal em função do tempo setado no objeto luz
	 		 *  (statusLuz# = 159)
	 		*/
	 		case statusLuz:
	 			if('g' == cCode[3]){
	 				//Constroi mensagem com o status da lampada
	 				if(luz.get_Status()){
	 					textAux = "A luz está ligada";
	 				}else{
	 					textAux = "A luz está desligada";
	 				}
	 			}else if('s' == cCode[3]){
					textAux = String("Erro - não é possivel alterar o status da lampada desta forma");
	 			}else{
	 				textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;

	 		/* 
	 		 *  Status do aquecedor: diz ao usuario se o aquecedor está ligado ou desligado no momento.
	 		 *  -get: retorna status atual do aquecedor, armazenado no objeto aquecedor
	 		 *	-set: não habilitado, não é possivel alterar o status do aquecedor desta forma, o status é controlado
	 		 *	 	  apenas pelo código principal em função da temperatura minima setada.
	 		 *  (statusAquecedor# = 148)
	 		*/
	 		case statusAquecedor:
	 			if('g' == cCode[3]){
	 				//Constroi mensagem com o status do aquecedor
	 				if(aquecedor.get_Status()){
	 					textAux = "O aquecedor está ligado";
	 				}else{
	 					textAux = "O aquecedor está desligado";
	 				}
	 			}else if('s' == cCode[3]){
					textAux = String("Erro - não é possivel alterar o status do aquecedor desta forma");
	 			}else{
	 				textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;
	 		
	 		/* 
	 		 *  Status do cooler: diz ao usuario se o cooler está ligado ou desligado no momento.
	 		 *  -get: retorna status atual do cooler, armazenado no objeto cooler
	 		 *	-set: não habilitado, não é possivel alterar o status do cooler desta forma, o status é controlado
	 		 *	 	  apenas pelo código principal em função da temperatura maxima setada.
	 		 *  (statusCooler# = 150)
	 		*/
	 		case statusCooler:
	 			if('g' == cCode[3]){
	 				//Constroi mensagem com o status do cooler
	 				if(cooler.get_Status()){
	 					textAux = "O cooler está ligado";
	 				}else{
	 					textAux = "O cooler está desligado";
	 				}
	 			}else if('s' == cCode[3]){
					textAux = String("Erro - não é possivel alterar o status do cooler desta forma");
	 			}else{
	 				textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;


			/* 
	 		 *  Tempo online: diz ao usuario por quanto tempo o sistema está funcionando seguidamente
	 		 *  -get: retorna o tempo em dias + horas + minutos
	 		 *	-set: ---------
	 		 *  (statusCooler# = 228)
	 		*/
	 		case tempoOnline:
	 			if('g' == cCode[3]){
	 		 
	 				//transforma millis em uma string com o tempo.
	 				unsigned long ulBufferTempo = (millis()/1000);   //tempo em segundos
	 				textAux = "Tempo elapsado: " + String(ulBufferTempo/(60*60*24)) + String(" dias, ");
	 				ulBufferTempo = ulBufferTempo%(60*60*24); //retira o que foi contado
	 				textAux += String(ulBufferTempo/(60*60)) + String(" horas, ");
					ulBufferTempo = ulBufferTempo%(60*60); //retira o que foi contado
	 				textAux += String(ulBufferTempo/(60)) + String(" minutos, e ");
	 				ulBufferTempo = ulBufferTempo%(60); //retira o que foi contado
	 				textAux += String(ulBufferTempo) + String(" segundos");

	 			}else if('s' == cCode[3]){
					textAux = String("Erro - não é possivel alterar o parametro");
	 			}else{
	 				textAux = String("Erro - comando nao reconhecido");
	 			}
	 			break;

	 		default:
	 			//erro, encerra
	 			textAux = String("Erro - comando nao reconhecido");
	 			break;
	 }



	 //Imprime a mensagem salva no buffer para o usuário.
	 stControlCode = textAux;

}






/*
  Since StControlCode is READ_WRITE variable, onStControlCodeChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onStControlCodeChange()  {
	//Seta flag para avisar o loop principal que o usuário enviou uma mensagem que precisa ser interpretada.
	flag_WifiCommand = true;
}


#endif