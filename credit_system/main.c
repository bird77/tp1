#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Menu.h"
#include "Archivo.h"

int main(void)
{
	cargar_clientes();
	mostrar_menu(PRINCIPAL);
	return 0;
}