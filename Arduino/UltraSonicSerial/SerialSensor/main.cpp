#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "SerialPort.h"
#include <cstdlib>

using namespace std;
/*puerto serie*/
char *port_name = "\\\\.\\COM3";

char *dameDistancia = "dist";
char *promedio = "prom";

int read_result;
//cadena para ingresar
char incomingData[MAX_LOGINTUD_DATOS];

int main(){
  SerialPort arduino(port_name);
  if (arduino.estaConectado()) cout << "Estableciendo conexion" << endl;
  else cout << "ERROR, verifica nombre del puerto";

  while (arduino.estaConectado()){

  	int opcion;
  	do{

  		cout << "1 - Mostrar la distancia" <<endl;
  		cout << "2 - Mostrar promedio de distancias" <<endl;
  		cout << "3 - Salir" <<endl;
  		cout << "Ingrese una opcion: ";
  		cin >> opcion;
  		cout <<"\n\n";

  		if(opcion == 1){
  			arduino.escribirPuertoSerie(dameDistancia, MAX_LOGINTUD_DATOS);
		 	Sleep(100);
		 	arduino.leerPuertoSerie(incomingData, MAX_LOGINTUD_DATOS);
	 		cout << "Distancia = " << incomingData << "\n\n";
		  }

		  if(opcion == 2){
		  	arduino.escribirPuertoSerie(promedio, MAX_LOGINTUD_DATOS);
		  	Sleep(2500);
		 	arduino.leerPuertoSerie(incomingData, MAX_LOGINTUD_DATOS);
 			cout << "Promedio = " << incomingData << "\n\n";
		  }
		  if(opcion == 3){
		  	return(0);
		  }
	  }while(true);
}
}
