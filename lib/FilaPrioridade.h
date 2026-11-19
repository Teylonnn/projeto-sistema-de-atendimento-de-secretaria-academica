/* lib/FilaPrioridade.h */
#ifndef FILAPRIORIDADE_H
#define FILAPRIORIDADE_H

#define MAX 100

typedef struct fila_prioridade FilaPrio;

FilaPrio* cria_FilaPrio();
void libera_FilaPrio(FilaPrio* fp);
int consulta_FilaPrio(FilaPrio* fp, char* nome);
int insere_FilaPrio(FilaPrio* fp, char *nome, int prio);
int remove_FilaPrio(FilaPrio* fp);
int estavazia_FilaPrio(FilaPrio* fp);

#endif