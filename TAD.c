#include <stdio.h>
#include <stdlib.h>
#include "TAD.h"

typedef struct info
{
	int id;
	char linea;
	char * estacion;
}info;

typedef struct estacionCDT
{
	long int cant_pas;							//pasajeros que pasan en la estaicon
	int id;														
	struct estacionCDT * next;
}estacionCDT;

typedef struct lineaCDT
{
	char nombre;
	struct lineaCDT * next;
	long int total;								//total de pasajeros de la linea
	struct estacionCDT * first;					//puntero a la primer estacion de la linea
	long int max_pas;							//maxima cantidad de pasajeros que paso por una estacion
	char * est;									//estacion donde pasaron mas pasajeros
}lineaCDT;

typedef struct redSubteCDT
{
	lineaADT first;
	long int total_pasajeros;					//cantidad total de pasajeros de todas las lineas (se usa para calcular el porcentaje)
	long int pasajeros[7][2];   				//cantidad de pasajeros, dividida en cada dia de la semana y diurno/nocturno 	

}redSubteCDT;

redSubteCDT * newRed(){
	return calloc(1, sizeof(redSubteCDT));
}

static void cantPasRec(lineaADT l, FILE * query1){				//funcion recursiva que recorre cada linea e imprime la cant de pasajeros
	if (l == NULL)
	{
		return;
	}
	fprintf(query1, "%c, %ld\n", l -> nombre, l -> total);
	cantPasRec(l -> next, query1);
}

void pasajerosLinea(redSubteCDT * h){											//imprime la cantidad de pasajeros de cada linea
	FILE * query1 = fopen("./query1.csv", "wt");
	cantPasRec(h -> first, query1);
	fclose(query1);
}

void pasajerosPorDia(redSubteCDT * h){											//pasajeros segun dia, diurno/nocturno
	FILE * query2 = fopen("./query2.csv", "wt");
	char * dias[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
	for (int i = 0; i < 7; ++i)																		//recorre la matriz segun el dia
	{
		long int tot = 0;
		fprintf(query2, "%s,", dias[i]);
		for (int j = 0; j < 2; ++j)																	//recorre la matriz segun periodo
		{
			tot += h -> pasajeros[i][j];
			fprintf(query2,"%ld,", h -> pasajeros[i][j]);
		}
		fprintf(query2, "%ld\n", tot);
		tot = 0;
	}
	fclose(query2);
}

static void porcRec(lineaADT l, long int total, FILE * query3){						//recorre cada linea indicando el porcentaje de
	if (l == NULL)																	//pasajeros en base al total
	{
		return;
	}
	int porc = l -> total * 100 / total;
	fprintf(query3,"%c, %%%d", l-> nombre, porc);
	porcRec(l -> next, total, query3);
}

void porcPasajeros(redSubteCDT * h){														//imprime porcentaje de pasajeros en cada linea
	FILE * query3 = fopen("./query3.csv", "wt");
	porcRec(h -> first, h -> total_pasajeros, query3);
	fclose(query3);
}


static void maxEstRec(lineaADT l, FILE * query4){
	if (l == NULL)
	{
		return;
	}
	fprintf(query4,"%s, %c, %ld\n", l -> est, l -> nombre, l -> max_pas);
	maxEstRec(l -> next, query4);
}

void maxEst(redSubteCDT * h){													//maxima cantidad de pasajeros de cada estacion 
	FILE * query4 = fopen("./query4.csv", "wt");
	maxEstRec(h -> first, query4);												//se utiliza una funcion recursiva
	fclose(query4);
}



static estacionADT agregar(infoADT e, estacionADT est){				//agrega a la estacion a la linea correspondiente
	if (est == NULL || est -> id > e -> id)
	{
		estacionADT nueva = calloc(1, sizeof(estacionCDT));
		nueva -> id = e -> id;
		nueva -> next = est;
		return nueva;
	}
	est -> next = agregar(e, est -> next);
	return est;
}

static lineaADT agregarEstacionRec(infoADT e, lineaADT l){
	if (l == NULL || l -> nombre > e -> linea)							//la lista esta ordenada en forma ascendente
	{																	//segun valor ASCII de la linea 
		lineaADT nueva = calloc(1, sizeof(lineaCDT));
		nueva -> nombre = e -> linea;
		nueva -> next = l;
	}
	if (l -> nombre != e -> linea)
	{
		l -> next = agregarEstacionRec(e, l -> next);
	}
	l -> first = agregar(e, l -> first);								//cada linea tiene una lista de estaciones
	return l;

}

void agregarEstacion(infoADT e, redSubteADT red){				//agrega la estacion e a la red de subte
	red -> first = agregarEstacionRec(e, red -> first);			//se hara de forma recursiva

}
