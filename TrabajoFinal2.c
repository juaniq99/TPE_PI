#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "redSubteADT.h"

FILE * molinetes;
FILE * estaciones;

void leeEstaciones(FILE * arch, redSubteADT r)
{ 								
	char texto [10000];
	fgets(texto, sizeof(texto), arch);					//Lee la linea con los nombres de los campos
	while(fgets(texto, sizeof(texto), arch) != NULL)
	{
		infoADT nuevaInfo = newInfo();
		nuevaInfo = guardarDato(nuevaInfo, texto);
		r = agregarEstacion(nuevaInfo, r);

	}
}

void leeMolinetes(FILE * arch, redSubteADT r){
	char texto[10000];
	fgets(texto, sizeof(texto), arch);
	while(fgets(texto, sizeof(texto), arch) != NULL){
		infoMolineteADT nuevaInfo = newInfoMolinete();
		nuevaInfo = guardarDatoMolinete(nuevaInfo, texto);
		agregarDato(nuevaInfo, r);
	}
}

int main(void)
{
	redSubteADT subte = newRed();
	infoADT est = newInfo();

	estaciones = fopen("./estaciones.csv", "rt");
	if (estaciones == NULL)
	{
		printf("ERROR EN ARCHIVO ESTACIONES\n");
		return 1;
	}
	molinetes = fopen("./molinetes.csv", "rt"); 
	if (molinetes == NULL)
	{
		printf("ERROR EN ARCHIVO MOLINETES\n");
		return 1;
	}
	leeEstaciones(estaciones, subte);
	leeMolinetes(molinetes, subte);
	pasajerosLinea(subte);
	//pasajerosPorDia(subte);
	porcPasajeros(subte);
	maxEst(subte);
	return 0;
}