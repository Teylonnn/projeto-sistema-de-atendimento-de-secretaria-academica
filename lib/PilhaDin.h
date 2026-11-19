/* lib/PilhaDin.h */
#ifndef PILHADIN_H
#define PILHADIN_H

#include "Aluno.h"

typedef struct elemento* Pilha;

Pilha* cria_Pilha();
void libera_Pilha(Pilha* pi);
int acessa_topo_Pilha(Pilha* pi, struct aluno *al);
int insere_Pilha(Pilha* pi, struct aluno al);
int remove_Pilha(Pilha* pi);
int Pilha_vazia(Pilha* pi);

#endif