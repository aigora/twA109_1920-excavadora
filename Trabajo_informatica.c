#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SerialPort.h"
#include <windows.h>
#include <math.h>
#define MAX_DATA_LENGTH 255 
#define PI 3.141592

void autoConnect(SerialPort *arduino, char*);
void gotoxy(int x,int y);
int punto_x(int distancia, int angulo);
int punto_y(int distancia, int angulo);

int main (void)
{
	SerialPort *arduino;
	
	char* portName = "\\\\.\\COM5";
	
	char incomingData [MAX_DATA_LENGTH];
	
	arduino = (SerialPort*)malloc(sizeof(SerialPort));
	
	Crear_Conexion(arduino, portName);  //para comenzar la comunicación con Arduino
	
	autoConnect(arduino, incomingData);
	
	return 0;
}


void autoConnect(SerialPort *arduino, char *incomingData)
{
	char sendData = 0;
	int distancia, angulo;
	int px, py;
	
		while(!isConnected(arduino))
		{
			Sleep(100);
			Crear_Conexion(arduino, arduino->portName);		
		}
		
		if(isConnected(arduino))
			printf("Conectado con Arduino en el puerto %s", arduino->portName);
		
	printf("\n0- Apagar motor");
	printf("\n1- Encender motor");
	printf("\n9- Salir");
	
		while (isConnected(arduino) && sendData!='9') //para comenzar el funcionamiento con arduino
		{
			sendData = getch(); //recibe la tecla pulsada
			writeSerialPort(arduino, &sendData, sizeof(char)); //lo envía al puerto serie
			
			while (isConnected(arduino))
			{
				distancia = readSerialPort(arduino, incomingData, MAX_DATA_LENGTH); //recibe los datos de las distancias y los guarda en la variable distancia
				angulo = readSerialPort(arduino, incomingData, MAX_DATA_LENGTH); //recibe los datos de los ángulos y los guarda en la variable ángulo
				
				px = punto_x(distancia, angulo);  //pasa de argumentos la distancia y el ángulo y los transforma en la coordenada x del punto
				py = punto_y(distancia, angulo);  //pasa de argumentos la distancia y el ángulo y los transforma en la coordenada y del punto
				
				if(px<0 || py<0) //si es negativo, la función gotoxy no puede "dibujar" el punto
 				{
 					px = -px;
 					py = -py;
				}
				else
				{
					px = px;
					py = py;
				}
				
				gotoxy(px, py);  //función que posiciona el cursor en el punto indicado entre ( , )
				printf("*");
				
			}
		}
		
		
		if(!isConnected(arduino))
			printf("Se ha perdido la conexión con arduino\n");
}

void gotoxy(int x,int y)
{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y= y;
	SetConsoleCursorPosition(hcon, dwPos);
}

int punto_x(int distancia, int angulo)   //convierte las coordenadas polares (recibidas del arduino) a cartesianas (coordenada x)
{
	int x;
	x = distancia*cos(angulo*(180/PI));
	
	return x;
}

int punto_y(int distancia, int angulo)   //convierte las coordenadas polares (recibidas del arduino) a cartesianas (coordenada y)
{
	int y;
	y = distancia*sin(angulo*(180/PI));
	
	return y;
}
