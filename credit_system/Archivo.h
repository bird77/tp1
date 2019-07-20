#ifndef ARCHIVO_H
#define ARCHIVO_H

extern int line_count;

void guardar_cliente(struct Cliente *cliente); // guarda el cliente pasado como parámetro en el archivo clientes.csv
void cargar_clientes(void); // carga los clientes archivados -- ARREGLAR

#endif