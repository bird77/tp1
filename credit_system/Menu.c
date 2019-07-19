#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"
#include "Cliente.h"

void menu_principal(void) // a reworkear --- implementar opcion para cancelar creditos
{
	enum { REGISTRAR = 1, MOSTRAR, BUSCAR_NOMBRE, BUSCAR_RANGO_EDAD, PEDIR_CREDITO, PAGAR_CREDITO, BORRAR, LIMPIAR, SALIR };
	int salir = 0;
	printf("%d) Registrar cliente\n%d) Mostrar clientes\n%d) Buscar cliente por nombre\n%d) Buscar por edad\n%d) Pedir credito\n%d) Pagar credito\n%d) Eliminar cliente\n%d) Limpiar consola\n%d) Salir\n",
		REGISTRAR, MOSTRAR, BUSCAR_NOMBRE, BUSCAR_RANGO_EDAD, PEDIR_CREDITO, PAGAR_CREDITO, BORRAR, LIMPIAR, SALIR);
	while(salir == 0) {
		int opcion = 0;
		if(scanf("%d", &opcion) < 1) {
			printf("Entrada invalida.\n");
			return;
		}
		switch(opcion) {
		case REGISTRAR:
			pedir_datos();
			break;
		case MOSTRAR:
			listar_clientes();
			break;
		case BUSCAR_NOMBRE: {
			char nombre[24];
			char apellido[24];
			printf("Ingrese el nombre del cliente: ");
			if(scanf("%s", nombre))
				printf("[Opcional] Ingrese el apellido del cliente o 0 para omitir: ");
			if(scanf("%s", apellido))
				buscar_nombre(nombre, apellido);
			break;
		}
		case BUSCAR_RANGO_EDAD: {
			int edad_inicial, edad_final;
			printf("Ingrese la edad inicial: ");
			if(scanf("%d", &edad_inicial))
				printf("Ingrese la edad final: ");
			if(scanf("%d", &edad_final))
				buscar_edad(edad_inicial, edad_final);
			break;
		}
		case PEDIR_CREDITO: {
			int id, dni;
			printf("Ingrese su id: ");
			if(scanf("%d", &id))
				printf("Ingrese su dni: ");
			if(scanf("%d", &dni))
				pedir_credito(id, dni);
			break;
		}
		case PAGAR_CREDITO: {
			int id = 0;
			int monto = 0;
			printf("Ingrese su ID: ");
			if(scanf("%d", &id))
				printf("Ingrese el monto a pagar: ");
			if(scanf("%d", &monto))
				pagar_credito(id, monto);
			break;
		}
		case BORRAR: {
			int id = 0;
			printf("Introduzca la ID del cliente a eliminar.\n");
			if(scanf("%d", &id))
				borrar_cliente(id);
			break;
		}
		case LIMPIAR:
			system("cls");
			printf("%d) Registrar cliente\n%d) Mostrar clientes\n%d) Buscar cliente por nombre\n%d) Buscar por edad\n%d) Pedir credito\n%d) Pagar credito\n%d) Eliminar cliente\n%d) Limpiar consola\n%d) Salir\n",
				REGISTRAR, MOSTRAR, BUSCAR_NOMBRE, BUSCAR_RANGO_EDAD, PEDIR_CREDITO, PAGAR_CREDITO, BORRAR, LIMPIAR, SALIR);
			break;
		case SALIR:
			salir = 1;
			break;
		default:
			printf("Error: opcion invalida.\n");
			break;
		}
	}
}
