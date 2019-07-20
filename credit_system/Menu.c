#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Menu.h"
#include "Cliente.h"


void mostrar_menu(Menu menu)
{
	switch(menu) {
	case PRINCIPAL:
		system("cls");
		menu_principal();
		break;
	case CLIENTE:
		system("cls");
		menu_cliente();
		break;
	case CREDITO:
		system("cls");
		menu_credito();
		break;
	default:
		printf("Error: Menu invalido.\n");
		break;
	}
}

void menu_principal(void)
{
	int salir = 0;
	while(!salir) {
		system("cls");
		printf("1) Clientes\n2) Creditos\n3) Salir\n");
		int opcion = 0;
		if(scanf("%d", &opcion) < 1) {
			printf("Entrada invalida.\n");
			return;
		}
		switch(opcion) {
		case 1:
			mostrar_menu(CLIENTE);
			break;
		case 2:
			mostrar_menu(CREDITO);
			break;
		case 3:
			salir = 1;
			system("pause");
			break;
		default:
			printf("Error: Opcion invalida, intente de nuevo.\n");
			break;
		}
	}
}

void menu_cliente(void)
{
	int volver = 0;
	printf("1) Registrar cliente\n2) Mostrar clientes\n3) Eliminar cliente\n4) Buscar cliente\n5) Volver al menu principal\n");
	while(!volver) {
		int opcion = 0;
		if(scanf("%d", &opcion) < 1) {
			printf("Entrada invalida.\n");
			exit(1);
		}
		switch(opcion) {
		case 1:
			pedir_datos();
			break;
		case 2: {
			int n = 0;
			printf("Ingrese el numero de clientes a mostrar (min 1, max %d): ", client_count);
			if(scanf("%d", &n)) {
				if(n > client_count || n < 1) {
					printf("Error: El numero de clientes a mostrar no puede ser menor a 1 o mayor al total de clientes (%d)\n", client_count);
					break;
				}
			}
			listar_clientes(n);
			break;
		}
		case 3: {
			int id = 0;
			printf("Introduzca la ID del cliente a eliminar: ");
			if(scanf("%d", &id))
				borrar_cliente(id);
			break;
		}
		case 4:
			menu_busqueda_cliente();
			break;
		case 5:
			volver = 1; // detiene el loop del men� de clientes y retorna autom�ticamente al men� principal
			break;
		default:
			printf("Error: Opcion invalida, intente de nuevo.\n");
			break;
		}
	}
}

void menu_credito(void)
{
	int volver = 0;
	printf("1) Pedir credito\n2) Pagar credito\n3) Cancelar credito\n4) Volver al menu principal\n");
	while(!volver) {
		int opcion = 0;
		if(!scanf("%d", &opcion)) return;
		switch(opcion) {
		case 1: {
			int id, dni;
			printf("Ingrese la ID: ");
			if(scanf("%d", &id))
				printf("Ingrese el DNI: ");
			if(scanf("%d", &dni))
				pedir_credito(id, dni);
			break;
		}
		case 2: {
			int id, monto;
			printf("Ingrese la ID: ");
			if(scanf("%d", &id))
				printf("Ingrese el monto a pagar: ");
			if(scanf("%d", &monto))
				pagar_credito(id, monto);
			break;
		}
		case 3: {
			int id, index;
			printf("Ingrese la ID: ");
			if(scanf("%d", &id))
				printf("Ingrese el indice del credito a cancelar, o 0 para cancelar todos los creditos activos: ");
			if(scanf("%d", &index))
				cancelar_credito(id, index);
			break;
		}
		case 4:
			volver = 1;
			break;
		default:
			printf("Error: Opcion invalida, intente de nuevo.\n");
			break;
		}
	}
}

void menu_busqueda_cliente(void)
{
	int volver = 0;
	while(!volver) {
		printf("Escoja el metodo de busqueda a utilizar: 1- Buscar por nombre, 2- Buscar por rango de edad. Ingrese 3 para volver atras.\n");
		int opcion = 0;
		if(!scanf("%d", &opcion)) return;
		switch(opcion) {
		case 0:
			volver = 1;
			break;
		case 1: {
			char nombre[24];
			char apellido[24];
			printf("Ingrese el nombre del cliente: ");
			if(scanf("%s", nombre))
				printf("[Opcional] Ingrese el apellido del cliente o 0 para omitir: ");
			if(scanf("%s", apellido))
				buscar_nombre(nombre, apellido);
			break;
		}
		case 2: {
			int edad_inicial, edad_final;
			printf("Ingrese la edad inicial: ");
			if(scanf("%d", &edad_inicial))
				printf("Ingrese la edad final: ");
			if(scanf("%d", &edad_final))
				buscar_edad(edad_inicial, edad_final);
			break;
		}
		case 3:
			printf("Operacion cancelada.\n");
			volver = 1;
			break;
		default:
			printf("Error: Opcion invalida, intente de nuevo.\n");
			break;
		}
	}
}