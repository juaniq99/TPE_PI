// REDSUBTEADT.C /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "redSubteADT.h"

// Estructuras ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct info
{
	int id;
	char linea;
	char * estacion;
}info;

typedef struct estacionCDT
{
	long int cant_pas;					// Pasajeros que pasan en la estación
	int id;														
	struct estacionCDT * next;
}estacionCDT;

typedef struct lineaCDT
{
	char nombre;
	struct lineaCDT * next;
	long int total;						// Total de pasajeros de la línea
	struct estacionCDT * first;				// Puntero a la primer estacion de la línea
	long int max_pas;					// Máxima cantidad de pasajeros que paso por una estación
	char * est;						// Estación donde pasaron mas pasajeros
}lineaCDT;

typedef struct redSubteCDT
{
	lineaADT first;
	long int total_pasajeros;				// Cantidad total de pasajeros de todas las lineas (se usa para calcular el porcentaje)
	long int pasajeros[7][2];   				// Cantidad de pasajeros, dividida en cada dia de la semana y diurno/nocturno 	

}redSubteCDT;

// Armado de listas /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

redSubteADT newRed(){
	return calloc(1, sizeof(redSubteCDT));
}

static void freeEst(tEstacion * est){
	if(est == NULL)
		return;
	freeEst(est->next);
	free(est);
}

static void freeLinea(tLinea * linea){
	if (linea == NULL)
	{
		return;
	}
	freeEst(linea->first);
	freeLinea(linea->next);
	freeLinea(linea);
}

void freeRed(redSubteADT r){
	freeLinea(r->first);
	free(r);
}

static estacionADT agregar(infoADT e, estacionADT est){					// Agrega la estación a la linea correspondiente
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
	if (l == NULL || l -> nombre > e -> linea)					// La lista esta ordenada en forma ascendente
	{										// según valor ASCII de la línea 
		lineaADT nueva = calloc(1, sizeof(lineaCDT));
		nueva -> nombre = e -> linea;
		nueva -> next = l;
		return nueva;
	}
	if (l -> nombre != e -> linea) 							// Si no es la línea que estoy agregando
	{
		l -> next = agregarEstacionRec(e, l -> next);
	}
	else 										// Si es la línea que estoy agregando
	{
		l -> first = agregar(e, l -> first);					// Cada linea tiene una lista de estaciones
	}
	return l;
}

void agregarEstacion(infoADT e, redSubteADT red){					// Agrega la estación e a la red de subte
	red -> first = agregarEstacionRec(e, red -> first);				// Se hará de forma recursiva

}

// ...

// Otras funciones ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void cantPasRec(lineaADT l, FILE * query1){					// Función recursiva que recorre cada línea e imprime la cant de pasajeros
	if (l == NULL)
	{
		return;
	}
	fprintf(query1, "%c, %ld\n", l -> nombre, l -> total);
	cantPasRec(l -> next, query1);
}

void pasajerosLinea(redSubteCDT * h){							// Imprime la cantidad de pasajeros de cada línea
	FILE * query1 = fopen("./query1.csv", "wt");
	cantPasRec(h -> first, query1);
	fclose(query1);
}

void pasajerosPorDia(redSubteCDT * h){											// Pasajeros segun día de la semana, diurno/nocturno
	FILE * query2 = fopen("./query2.csv", "wt");
	char * dias[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
	for (int i = 0; i < 7; ++i)											// Recorre la matriz segun el día
	{
		long int tot = 0;
		fprintf(query2, "%s,", dias[i]);
		for (int j = 0; j < 2; ++j)										// Recorre la matriz segun período
		{
			tot += h -> pasajeros[i][j];
			fprintf(query2,"%ld,", h -> pasajeros[i][j]);
		}
		fprintf(query2, "%ld\n", tot);
		tot = 0;
	}
	fclose(query2);
}

static void porcRec(lineaADT l, long int total, FILE * query3){								// Recorre cada línea indicando el porcentaje de
	if (l == NULL)													// pasajeros en base al total
	{
		return;
	}
	int porc = l -> total * 100 / total;
	fprintf(query3,"%c, %%%d", l-> nombre, porc);
	porcRec(l -> next, total, query3);
}

void porcPasajeros(redSubteCDT * h){											// Imprime porcentaje de pasajeros en cada línea
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

void maxEst(redSubteCDT * h){								// Máxima cantidad de pasajeros de cada estación 
	FILE * query4 = fopen("./query4.csv", "wt");
	maxEstRec(h -> first, query4);							// se utiliza una funcion recursiva
	fclose(query4);
}
