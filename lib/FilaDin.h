/* lib/FilaDin.h */
#ifndef FILADIN_H
#define FILADIN_H

#include "Aluno.h"

typedef struct fila Fila;

Fila* cria_Fila();
void libera_Fila(Fila* fi);
int consulta_Fila(Fila* fi, struct aluno *al);
int insere_Fila(Fila* fi, struct aluno al);
int remove_Fila(Fila* fi);
int Fila_vazia(Fila* fi);

#endif