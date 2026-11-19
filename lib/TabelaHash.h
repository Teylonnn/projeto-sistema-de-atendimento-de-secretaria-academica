/* lib/TabelaHash.h */
#ifndef TABELAHASH_H
#define TABELAHASH_H

#include "Aluno.h"

typedef struct hash Hash;

Hash* criaHash(int tamanho);
void liberaHash(Hash* ha);
int insereHash_EnderAberto(Hash* ha, struct aluno al);
int buscaHash_EnderAberto(Hash* ha, int mat, struct aluno* al);

#endif