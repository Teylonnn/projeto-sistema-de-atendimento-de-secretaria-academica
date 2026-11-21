/* lib/ArvoreBinaria.c */
#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBinaria.h"

struct NO {
    int info;
    struct NO *esq;
    struct NO *dir;
};

/* Funções auxiliares internas */
static void libera_NO(struct NO* no) {
    if (no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

static struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if (atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while (no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }
    if (no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}

ArvBin* cria_ArvBin() {
    ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
    if (raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_ArvBin(ArvBin* raiz) {
    if (raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

int insere_ArvBin(ArvBin* raiz, int valor) {
    if (raiz == NULL)
        return 0;

    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if (novo == NULL)
        return 0;

    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;

    if (*raiz == NULL) {
        *raiz = novo;
    } else {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while (atual != NULL) {
            ant = atual;
            if (valor == atual->info) {
                free(novo);
                return 0; // elemento já existe
            }
            if (valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if (valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

int remove_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL)
        return 0;

    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info) {
            if (atual == *raiz)
                *raiz = remove_atual(atual);
            else {
                if (ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if (valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

int consulta_ArvBin(ArvBin *raiz, int valor) {
    if (raiz == NULL)
        return 0;

    struct NO* atual = *raiz;
    while (atual != NULL) {
        if (valor == atual->info)
            return 1;
        if (valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

void emordem_ArvBin(ArvBin *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        emordem_ArvBin(&((*raiz)->esq));
        printf("%d ", (*raiz)->info);
        emordem_ArvBin(&((*raiz)->dir));
    }
}

void exibirArvBinEmOrdem(ArvBin *raiz) {
    if (raiz == NULL)
        return;
    if (*raiz != NULL) {
        emordem_ArvBin(&((*raiz)->esq));
        printf("{ %d } ", (*raiz)->info);
        emordem_ArvBin(&((*raiz)->dir));
    }
}