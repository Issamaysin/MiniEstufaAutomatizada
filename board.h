/* ********************************************************************** */
/* File name:        Board.h                                              */
/* File description: Definições de pinos (ESP8266)                        */
/* Author name:      Renato Pepe                                		  */
/* Creation date:    27/09/2021                                           */
/* Revision date:    13/10/2021                                           */
/* ************************************************************************/

#ifndef BOARD_H
#define BOARD_H


/* 
 * Definições dos pinos 
*/
/*Atuadores*/
#define PIN_AQUECEDOR 5 //d1
#define PIN_COOLER 4    //d2
#define PIN_VALVULA 13  //d7
#define PIN_LAMPADA 14  //d5
#define PIN_LED 15      //d8

/*Sensores*/
#define PIN_SENSOR_TEMPERATURA 2 //d4
#define PIN_SENSOR_UMIDADE A0


//Comente esse define para desabilitar os prints no serial
#define debuggerSerial





#endif
