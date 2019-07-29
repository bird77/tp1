#include <stdio.h>
#include "Credito.h"
#include "Cliente.h"

void pedir_credito(int id, int dni)
{
	
	struct Cliente *cliente;
	if((cliente = buscar_cliente(id)) != NULL) { // si encuentra el usuario con la id pasada como parametro
		if(cliente->dni != dni) {
			printf("Error: DNI invalido.\n");
			return;
		}
		if(cliente->creditos_usados == MAX_CREDITOS) {
			printf("Error: No le quedan creditos disponibles.\n");
			return;
		}
		int monto;
		printf("Ingrese el monto solicitado: ");
		while(1) {
			if(!scanf("%d", &monto)) return;
			if(monto > MAX_MONTO || monto < MIN_MONTO)
				printf("Error: Monto invalido, intente de nuevo.\nMontos validos: [%d-%d]\n", MIN_MONTO, MAX_MONTO);
			else if((sumar_creditos(cliente) + monto) > MAX_MONTO)
				printf("Error: El prestamo total no puede ser mayor a %d", MAX_MONTO);
			else
				break;
		}
		for(int i = 0; i < MAX_CREDITOS; ++i) {
			if(cliente->credito[i].monto == 0) {
				cliente->credito[i].monto = monto;
				cliente->creditos_usados += 1;
				printf("Credito de %d agregado con exito.\n", monto);
				break;
			}
		}
	}
}

void pagar_credito(int id, int monto)
{
	struct Cliente *aux = NULL;
	if((aux = buscar_cliente(id)) != NULL) {
		if(!mostrar_creditos(aux)) {
			printf("Error: Este cliente no tiene creditos activos.\n");
			return;
		}
		int index = 0;
		printf("Ingrese el indice del credito a pagar o 0 para cancelar: ");
		if(!scanf("%d", &index)) return;
		if(index == 0) { // crear funcion?
			printf("Operacion cancelada.\n");
			return;
		}
		if(index < 1 || index > MAX_CREDITOS) {
			printf("Error: Indice invalido. El rango es [1-%d]\n", MAX_CREDITOS);
			return;
		}
		if(aux->credito[index-1].monto == 0) {
			printf("Error: El indice ingresado no contiene un credito activo.\n");
			return;
		}
		if(aux->credito[index-1].monto - monto < 0) {
			printf("Error: El monto ingresado es mayor que el monto del credito a pagar.\n");
			return;
		}
		aux->credito[index-1].monto -= monto;
		printf("%d descontado satisfactoriamente. Nueva deuda: %d\n", monto, aux->credito[index-1].monto);
	}
}

void cancelar_credito(int id, int index) // testear
{
	struct Cliente *aux = NULL;
	if((aux = buscar_cliente(id)) != NULL) {
		if(!mostrar_creditos(aux)) {
			printf("Error: Este cliente no tiene creditos activos.\n");
			return;
		}
		if(index == 0) {
			int count = 0;
			for(int i = 0; i < MAX_CREDITOS; ++i) {
				if(aux->credito[i].monto > 0) {
					aux->credito[i].monto = 0;
					++count;
				}
			}
			printf("%d creditos cancelados con exito.\n", count);
		}
		else if(index >= 1 && index <= MAX_CREDITOS) {
			if(aux->credito[index-1].monto > 0)
				aux->credito[index-1].monto = 0;
			printf("Credito cancelado con exito.\n");
		}
		else {
			printf("Error: Indice invalido. El rango es [1-%d]\n", MAX_CREDITOS);
			return;
		}
	}
}

int mostrar_creditos(struct Cliente *cliente)
{
	int count = 0;
	printf("ID: %d\n", cliente->id);
	for(int i = 0; i < MAX_CREDITOS; ++i) {
		if(cliente->credito[i].monto > 0) {
			printf("%d) $%d\n", i + 1, cliente->credito[i].monto);
			++count;
		}
	}
	if(count > 0) {
		printf("Creditos activos: %d\n", count);
		return 1;
	}
	else {
		return 0;
	}
}

int sumar_creditos(struct Cliente *cliente)
{
	int aux = 0;
	for(int i = 0; i < MAX_CREDITOS; ++i) {
		if(cliente->credito[i].monto > 0)
			aux += cliente->credito[i].monto;
	}
	return aux;
}