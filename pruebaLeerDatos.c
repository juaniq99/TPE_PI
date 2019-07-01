#include <stdio.h>
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
	info prueba;
	char texto[20];
	char texto2[20];
	char texto3[20];
	char * token;
	f = fopen("./estaciones.csv","rt");				//ABRO ARCHIVO
	if (f == NULL)									//VERIFICA QUE SE ABRIO
	{
		printf("ERROR DE ARCHIVO\n");
		return 1;
	}
	
	while(fscanf(f, "%s\n", texto) != EOF){
		token = strtok(texto, ",");						//STRTOK LEE HASTA ENCONTRAR UNA , Y GUARDA EL CONTENIDO EN TOKEN
		if (token == NULL)								//SI ES NULL YA NO HAY NADA QUE LEER DE TEXTO					
		{
			return -1;
		}
		do{
			printf("%s \n", token);
			token = strtok(NULL, ",");
		}while(token != NULL);
	}

	fclose(f);
	return 0;
}
