/* lib/ListaDinEncadDupla.c */
#include <stdlib.h>
#include "ListaDinEncadDupla.h"

struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;

    no->dados = al;
    no->prox = NULL;

    if ((*li) == NULL) { // lista vazia: insere início
        no->ant = NULL;
        *li = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}