#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Archivo.h"

int line_count = 0;

void guardar_cliente(struct Cliente *cliente)
{
	FILE *archivo = fopen("clientes.csv", "a");
	if(archivo != NULL) {
		fprintf(archivo, "%s,%s,%d,%d,%s,%d,%d,%d,%d,%d\n" 
			,cliente->nombre, cliente->apellido, cliente->edad, cliente->dni, cliente->mail
			,cliente->credito[0].monto, cliente->credito[1].monto, cliente->credito[2].monto, cliente->credito[3].monto
			,cliente->credito[4].monto);
		fclose(archivo);
		++line_count;
	}
	else {
		printf("Error: No se pudo abrir el archivo deseado.\n");
		exit(1);
	}
}

void cargar_clientes(void)
{
	int id;
	char nombre[24];
	char apellido[24];
	int edad;
	int dni;
	char mail[24];
	int credito[MAX_CREDITOS];
	////////////////////
	char* token;
	char line[128];
	char s[2] = ",";
	FILE* archivo = fopen("clientes.csv", "r");
	if(archivo != NULL) {
		while(!feof(archivo)) {
			fgets(line, 128, archivo);
			token = strtok(line, ",");
			id = atoi(token);
			token = strtok(line, ",");
			strcpy(nombre, token);
			token = strtok(line, ",");
			strcpy(apellido, token);
			token = strtok(line, ",");
			edad = atoi(token);
			token = strtok(line, ",");
			dni = atoi(token);
			token = strtok(line, ",");
			strcpy(mail, token);
			token = strtok(line, ",");
			credito[0] = atoi(token);
			token = strtok(line, ",");
			credito[1] = atoi(token);
			token = strtok(line, ",");
			credito[2] = atoi(token);
			token = strtok(line, ",");
			credito[3] = atoi(token);
			token = strtok(line, ",");
			credito[4] = atoi(token);
			agregar_cliente(nombre, apellido, edad, dni, mail);
		}
		fclose(archivo);
	}
	else {
		return;
	}
}