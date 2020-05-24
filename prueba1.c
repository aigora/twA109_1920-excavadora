#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#define PI 3.141592
#define N 5

void gotoxy(int , int);
int punto_x(int distancia, int angulo);
int punto_y(int distancia, int angulo);

int main(void)
{
	FILE*fichero;
	int i, distancia, angulo;
	int px, py;
	int cierre;
	
	fichero = fopen("coordenadas.txt", "rt");
	if(fichero == NULL)
		printf("ERROR: no se ha podido abrir\n");
	else
	{
		do
		{
			fscanf(fichero, "%d %d\n", &distancia, &angulo);
		
			px = punto_x(distancia, angulo);
			py = punto_y(distancia, angulo);
 		
 			if(px<0 || py<0)
 			{
 				px = -px;
 				py = -py;
			}
			else
			{
				px = px;
				py = py;
			}
			
			//printf("%d %d ", px[i], py[i]);
			
			gotoxy(px, py);
			printf("*");
			
		}while(!feof(fichero));
 			
	}
	
	cierre = fclose(fichero);
	if(cierre == EOF)
		printf("ERROR: no se ha podido cerrar\n");
	else
		printf("\nTodo ok\n");
 
 	
 system ("PAUSE");
 return 0;
}

int punto_x(int distancia, int angulo)   //convierte las coordenadas polares (recibidas del arduino) a cartesianas
{
	int x;
		x = distancia * cos(angulo*(PI/180));
		return x;
}

int punto_y(int distancia, int angulo)   //convierte las coordenadas polares (recibidas del arduino) a cartesianas
{
	int y;
	
		y = distancia * sin(angulo*(PI/180));
		return y;
}


void gotoxy(int x,int y)
{
 HANDLE hcon;
 hcon = GetStdHandle(STD_OUTPUT_HANDLE);
 COORD dwPos;
 dwPos.X = x;
 dwPos.Y= y;
 SetConsoleCursorPosition(hcon,dwPos);
}
