
Autor: Renato Pepe (https://github.com/Issamaysin)

Projeto mini estufa automatizada: Consiste em uma pequena estufa, para uma unica planta, onde os processos de iluminação, aquecimento
	resfriamento, e irrigação realizados automaticamente. O usuário pode controlar e checar os parametros a distancia através de uma
	interface wifi

A estufa é controlada por uma placa ESP8266, o processo de iluminação é feito utilizando uma lampada LED grow especifica para o crescimento
	de plantas que é ligada/desligada pelo controlador através de um relé, o aquecimento é feito por uma escada de resistores e o resfriamento
	através de um cooler, ambos são conectados ao controlador através de transistores TIP122, e a medição da temperatura é realizada por um 
	sensor de temperatura DS18B20, o processo de irrigação utiliza um sensor resistivo de umidade do solo e uma valvula de água conectada a
	uma fonte de água. A interface Wifi utiliza a plataforma Arduino IoT cloud para se conectar e trocar informações com o controlador, devido
	as limitações dessa ferramenta a interface utiliza um comando de texto para se comunicar, onde o usuário escreve um código referente a função
	que deseja executar e recebe uma frase com os resultados da operação.


	Comandos da interface: 
		~Formato do código: #AABCC+
	 *  	#   : Sinaliza o começo de um código, para filtrar strings aleatórias (1 digito)
	 *		AA  : Parametro que será alterado ou consultado (2 digitos)
	 *		B   : 'g' ou 's' -> get ou set, diz se o usuário pretende alterar um parametro ou ler um valor (1 digito)
	 *              CC  : se o B for igual a set CC terá o valor que será setado no parametro, representado por um numero inteiro com dois digitos.
	 *		+   : Caracter que sinaliza que um código finalizou
	 *
	 *		AA: Parametros: -Temperatura máxima : tx
	 *						-Temperatura minima : tn
	 *						-Temperatura atual  : ta
	 *						-Tempo da lampada   : lt
	 *                                              -Status da luz      : SL
	 *          			                -Status do aquecedor: SA
	 *						-Status do cooler   : SC
	 *
	 *		B : Parametros:                 -Get: g
	 *						-Set  s
	 *
	 *		CC: Numero inteiro com dois digitos.
	 *	
	 *		Exemplos:         #tag+    -> usuário recebe a informação sobre a temperatura atual da estufa
	 *				  #tns22+  -> usuário seta a temperatura minima que o sistema deve ficar em 22 ºC
	 *                                #SAg+	   -> usuário recebe a informação sobre o status do aquecedor
	 *				  #lts14+  -> usuário seta que a estufa deve ser iluminada durante 14 horas por dia.


