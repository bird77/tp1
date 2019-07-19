#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include "Menu.h"

// falta: reworkear menú, optimizar funciones, guardado en archivos y testear a fondo

int main(void)
{
	// automatizar
	agregar_cliente("test1", "t1", 21, 4000, "test1@gmail.com");
	agregar_cliente("test2", "t2", 24, 5000, "test2@gmail.com");
	agregar_cliente("test3", "t3", 37, 6000, "test3@gmail.com");
	agregar_cliente("test4", "t4", 23, 7000, "test4@gmail.com");
	agregar_cliente("test5", "t6", 45, 8000, "test5@gmail.com");
	agregar_cliente("test4", "t5", 32, 9000, "test6@gmail.com");
	menu_principal();
	return 0;
}