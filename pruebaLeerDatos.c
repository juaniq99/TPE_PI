#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct info
{
	int id;
	char linea;
	char * estacion;
}info;
FILE * f;

int main(void)
{
	info prueba;									//SE CREA UNA ESTRUCTURA CON LOS DATOS A LEVANTAR
	char texto[200];								//VECTOR EN DONDE SE GUARDARA LA INFORMACION (SERIA MEJOR USAR VEC. DINAMICO?)
	char * token;									//TOKEN DONDE SE GUARDA LA LECTURA
	f = fopen("./estaciones.csv","rt");				//ABRO ARCHIVO
	if (f == NULL)									//VERIFICA QUE SE ABRIO
	{
		printf("ERROR DE ARCHIVO\n");
		return 1;
	}
	fgets(texto, sizeof(texto), f);						//LEE LA PRIMER LINEA CON EL NOMBRE DE CADA COLUMNA(NO CONTIENE INFORMACION RELEVANTE)
														//DEBE HABER ALGUNA FORMA MEJOR DE SALTEAR ESA LINEA
	while(fgets(texto,sizeof(texto), f) != NULL){		//RECORRE HASTA LLEGAR A LA ULTIMA LINEA
		token = strtok(texto,",");						//STRTOK LEE HASTA ENCONTRAR UNA , Y GUARDA EL CONTENIDO EN TOKEN
		prueba.id = atoi(token);						//PASA EL TOKEN A ENTERO Y LO GUARDA, HACE LO MISMO CON CADA CAMPO
		printf("id: %d\n", prueba.id);					//SE IMPRIMIO PARA VERIFICAR QUE FUNCIONE
		token = strtok(NULL,",");						
		prueba.linea = *token;
		printf("Linea: %c\n", prueba.linea);
		token = strtok(NULL,",");						
		prueba.estacion = malloc(sizeof(texto));		//DEBERIA USARSE ALGO MAS EFICIENTE
		prueba.estacion = strcpy(prueba.estacion,token);
		printf("%s\n", prueba.estacion);
		
	}

	fclose(f);
	return 0;
}
