#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Archivo.h"

void guardar_clientes(void)
{
	struct Cliente *cliente = head;
	if(cliente == NULL) {
		printf("Error: No hay clientes registrados.\n");
		return;
	}
	FILE* archivo = fopen("clientes.csv", "w");
	int count = 0;
	if(archivo != NULL) {
		while(cliente != NULL) {
			fprintf(archivo, "%s,%s,%d,%d,%s,%d,%d,%d\n"
				, cliente->nombre, cliente->apellido, cliente->edad, cliente->dni, cliente->mail
				, cliente->credito[0].monto, cliente->credito[1].monto, cliente->credito[2].monto);
			++count;
			cliente = cliente->next;
		}
		fclose(archivo);
	}
	else {
		printf("Error: No se pudo abrir el archivo deseado.\n");
		exit(1);
	}
	printf("Clientes guardados: %d\n", count);
}

void cargar_clientes(void)
{
	//int id;
	char nombre[24];
	char apellido[24];
	int edad;
	int dni;
	char mail[24];
	int credito[MAX_CREDITOS];
	//////////////////////////////
	char *token;
	char line[128];
	char s[] = ",";
	FILE *archivo = fopen("clientes.csv", "r");
	if(archivo != NULL) {
		while(fgets(line, sizeof(line), archivo) != NULL) {
			if(line[0] != '\n') {
				token = strtok(line, s); // nombre
				strcpy(nombre, token);
				token = strtok(NULL, s); // apellido
				strcpy(apellido, token);
				token = strtok(NULL, s); // edad
				edad = atoi(token);
				token = strtok(NULL, s); // dni
				dni = atoi(token);
				token = strtok(NULL, s); // mail.
				strcpy(mail, token);
				token = strtok(NULL, s); // primer credito
				credito[0] = atoi(token);
				token = strtok(NULL, s); // segundo credito
				credito[1] = atoi(token);
				token = strtok(NULL, "\n"); // tercer credito. delimitador cambia a \n para evitar errores.
				credito[2] = atoi(token);
				agregar_cliente(nombre, apellido, edad, dni, mail, credito[0], credito[1], credito[2]);
			}
			else { // si la línea está vacía pasa a la siguiente
				continue;
			}
		}
		fclose(archivo);
	}
}