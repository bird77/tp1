#ifndef CREDITO_H
#define CREDITO_H

#define MAX_CREDITOS 5

#define MIN_MONTO 5000
#define MAX_MONTO 500000

enum { PERSONAL, HIPOTECARIO, COMERCIAL };

struct Credito { // a agregar: tipos de cr�dito, cuotas (con o sin inter�s?),
	int monto;
};

void pedir_credito(int id, int dni); // solicita un cr�dito dada la id y el dni del cliente
void iniciar_creditos(struct Cliente* cliente); // inicializa (con valores por defecto) los cr�ditos del cliente pasado como par�metro
void pagar_credito(int id, int monto); // paga parte o el total de un cr�dito del cliente id
void cancelar_credito(int id, int index); // elimina uno o todos los cr�ditos del cliente id
int mostrar_creditos(struct Cliente *cliente); // imprime los cr�ditos del cliente pasado como par�metro, asumiendo que existan

#endif