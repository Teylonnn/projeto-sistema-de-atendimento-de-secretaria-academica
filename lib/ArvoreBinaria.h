/* lib/ArvoreBinaria.h */
#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

typedef struct NO* ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
int consulta_ArvBin(ArvBin *raiz, int valor);
void emordem_ArvBin(ArvBin *raiz);
void exibirArvBinEmOrdem(ArvBin *raiz);

#endif