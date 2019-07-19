#ifndef CREDITO_H
#define CREDITO_H

#define MAX_CREDITOS 5

#define MIN_MONTO 5000
#define MAX_MONTO 500000

enum { PERSONAL, HIPOTECARIO, COMERCIAL };

struct Credito { // a agregar: tipos de crédito, cuotas (con o sin interés?),
	int monto;
};

void pedir_credito(int id, int dni); // solicita un crédito dada la id y el dni del cliente
void iniciar_creditos(struct Cliente* cliente); // inicializa (con valores por defecto) los créditos del cliente pasado como parámetro
void pagar_credito(int id, int monto); // paga parte o el total de un crédito del cliente id
void cancelar_credito(int id, int index); // elimina uno o todos los créditos del cliente id
int mostrar_creditos(struct Cliente *cliente); // imprime los créditos del cliente pasado como parámetro, asumiendo que existan

#endif