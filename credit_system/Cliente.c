#include <stdio.h>
#include <Windows.h> 
#include <string.h>
#include "Cliente.h"
#include "Archivo.h"

struct Cliente *head = NULL;
int client_count = 0;

void agregar_cliente(char nombre[], char apellido[], int edad, int dni, char mail[], int credito_1, int credito_2, int credito_3)
{
	struct Cliente *cliente;
	cliente = (struct Cliente*)malloc(sizeof(struct Cliente));
	if(cliente) { // si malloc consigue reservar memoria en heap
		strcpy(cliente->nombre, nombre);
		strcpy(cliente->apellido, apellido);
		cliente->edad = edad;
		cliente->dni = dni;
		cliente->id = obtener_nueva_id();
		strcpy(cliente->mail, mail);
		cliente->credito[0].monto = credito_1;
		cliente->credito[1].monto = credito_2;
		cliente->credito[2].monto = credito_3;
		// cliente se transforma en la cabeza de la lista luego de que cliente->next apunte a la cabeza anterior
		cliente->next = head; 
		head = cliente;
		++client_count;
	}
	else {
		printf("Error: out of memory\n");
		return;
	}
}

void pedir_datos(void)
{
	char nombre[24];
	char apellido[24];
	int edad = 0;
	int dni = 0;
	char mail[24];
	printf("Nombre y apellido: ");
	if(scanf("%s %s", nombre, apellido)) // mejorar para evitar overflow
		printf("Edad: ");
	if(!scanf("%d", &edad)) return;
		printf("DNI: ");
	if(!scanf("%d", &dni)) return;
		printf("Mail: ");
	if(scanf("%s", mail)) // mejorar para evitar overflow
		agregar_cliente(nombre, apellido, edad, dni, mail, 0, 0, 0); // agrega un nuevo cliente. inicializa creditos en 0
	printf("Cliente ingresado.\n");
}

void listar_clientes(int n)
{
	struct Cliente *aux = head;
	if(aux == NULL) {
		printf("Error: No hay clientes registrados.\n");
		return;
	}
	int count = 0;
	while(aux != NULL && count < n) {
		printf("%d) ", count + 1);
		mostrar_cliente(aux);
		aux = aux->next;
		++count;
	}
}

struct Cliente *buscar_cliente(int id)
{
	struct Cliente *aux = head;
	if(aux == NULL) {
		printf("Error: No hay clientes registrados\n");
		return NULL;
	}
	while(aux != NULL) {
		if(aux->id == id)
			return aux;
		aux = aux->next;
	}
	printf("Error: ID invalida.\n");
	return NULL;
}

void borrar_cliente(int id) // optimizar
{
	if(head == NULL) {
		printf("Error: No hay clientes registrados.\n");
		return;
	}
	if(!buscar_id(id)) {
		printf("Error: ID invalida.\n");
		return;
	}
	if(id == head->id) { // si la id a buscar es head guardo head->next en temp, libero head y temp se transforma en head
		struct Cliente *temp = head->next;
		//head->next = NULL; // test
		free(head);
		head = temp;
		--client_count; // reduzco el contador de clientes en 1
		printf("Cliente con ID %d eliminado.\n", id);
		return;
	}
	struct Cliente *aux = head;
	struct Cliente *temp = head->next; // aux va siempre delante de temp
	int count = 0;
	while(aux != NULL) {
		if(temp->id == id) {
			aux->next = temp->next; // temp pasa a apuntar a la referencia next de aux para mantener la lista conectada
			//aux->next = NULL; // test
			free(temp);
			--client_count;
			printf("Cliente con ID %d eliminado.\n", id);
			return;
		}
		aux = aux->next;
		temp = temp->next;
	}
}

int obtener_nueva_id()
{
	if(client_count == 0) return 1; // si la lista esta vacia la id es 1
	return head->id + 1;
}

int buscar_id(int id)
{
	if(id < 1) return 0;
	struct Cliente *aux = head;
	while(aux != NULL) {
		if(aux->id == id) return id;
		aux = aux->next;
	}
	return 0;
}

int buscar_nombre(char nombre[], char apellido[])
{
	struct Cliente *aux = head;
	int count = 0;
	if(aux == NULL) {
		printf("Error: No hay clientes registrados.\n");
		return 0;
	}
	while(aux != NULL) {
		if(apellido[0] == '0') {
			if((strcmp(aux->nombre, nombre) == 0)) {
				mostrar_cliente(aux);
				++count;
			}
		}
		else if((strcmp(aux->nombre, nombre) == 0) && strcmp(aux->apellido, apellido) == 0) {
			mostrar_cliente(aux);
			++count;
		}
		aux = aux->next;
	}
	if(count > 0) { // si count es mayor a 0 se encontro por lo menos un nombre
		printf("Cliente/s encontrado/s: %d\n", count);
		return 1;
	}
	else {
		printf("Error: No se encontraron coincidencias.\n");
		return 0;
	}
}

int buscar_edad(int edad_inicial, int edad_final)
{
	struct Cliente *aux = head;
	int count = 0;
	if(aux == NULL) {
		printf("Error: No hay clientes registrados.\n");
		return 0;
	}
	if(edad_inicial > edad_final) { // para evitar errores, intercambio las edades en caso de que la inicial sea mayor a la final
		int temp = edad_final;
		edad_final = edad_inicial;
		edad_inicial = temp;
	}
	while(aux != NULL) {
		if(aux->edad >= edad_inicial && aux->edad <= edad_final) {
			mostrar_cliente(aux);
			++count;
		}
		aux = aux->next;
	}
	if(count > 0) {
		printf("Cliente/s encontrado/s: %d\n", count);
		return 1;
	}
	else {
		printf("Error: No se encontraron clientes en el rango de edad [%d-%d]\n", edad_inicial, edad_final);
		return 0;
	}
}

void mostrar_cliente(struct Cliente *cliente)
{
	printf("nombre: %s %s, edad: %d, id: %d, dni: %d, mail: %s\n", cliente->nombre, cliente->apellido, cliente->edad, cliente->id, cliente->dni, cliente->mail);
	for(int i = 0; i < MAX_CREDITOS; ++i) {
		if(cliente->credito[i].monto > 0)
			printf("credito: %d\n", cliente->credito[i].monto);
	}
}