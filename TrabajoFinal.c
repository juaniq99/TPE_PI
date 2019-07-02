#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "redSubteADT.h"

FILE * molinetes;
FILE * estaciones;


void leeEstaciones(FILE * arch, redSubteADT r)
{ 								//El fopen y fclose se hacen en el main. Tambien la validacion de que existan? SI
	char texto [200];
	fgets(texto, sizeof(texto), arch);					//Lee la linea con los nombres de los campos
	while(fgets(texto, sizeof(texto), arch) != NULL)
	{
		infoADT nuevaInfo = newInfo();
		nuevaInfo = guardarDato(nuevaInfo, texto);
		agregarEstacion(nuevaInfo, r);
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


	return 0;
}