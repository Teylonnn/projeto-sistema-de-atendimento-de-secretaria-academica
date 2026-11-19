/* lib/ListaDinEncadDupla.h */
#ifndef LISTADINENCADDUPLA_H
#define LISTADINENCADDUPLA_H

#include "Aluno.h"

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct aluno al);
int tamanho_lista(Lista* li);
int busca_lista_pos(Lista* li, int pos, struct aluno *al);

#endif