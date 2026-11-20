#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../lib/Aluno.h"
#include "../lib/TabelaHash.h"
#include "../lib/ArvoreBinaria.h"
#include "../lib/FilaDin.h"
#include "../lib/FilaPrioridade.h"
#include "../lib/PilhaDin.h"
#include "../lib/ListaDinEncadDupla.h"


int main(){
    
    return 0;
}

//funções 5 -> 9
//Lê a matrícula. Se ela não está na árvore, recusa. Caso contrário, busca o aluno na tabela hash e o insere na fila.
int chegadaAtendimento(ArvBin *raiz, int mat, Hash* ha, Fila* fi){
    struct aluno al;

    if(!consulta_ArvBin(raiz, mat)){
        printf("Matricula: %d nao encontrada na arvore\n", mat);
        return 0;
    }

    if(buscaHash_EnderAberto(ha, mat, &al) && insere_Fila(fi, al)){
        printf("Aluno: %s inserido na fila\n", al.nome);
        return 1;
    }
    return 0;
}

//Lê matrícula e prioridade. Se a matrícula não está na árvore, recusa.Caso contrário, busca o aluno na tabela hash e insere nome e prioridade na fila de prioridade.
int RegistrarUrgencia(ArvBin *raiz, int mat, int prio, Hash* ha, FilaPrio* fi){
    struct aluno al;
    if(prio < 1 || prio > 5){
        printf("Prioridade: %d inválida", prio);
        return 0;
    }

    if(!consulta_ArvBin(raiz, mat)){
        printf("Matricula: %d nao encontrada na arvore\n", mat);
        return 0;
    }

    if(buscaHash_EnderAberto(ha, mat, &al) && insere_FilaPrio(fi, al.nome, prio)){
        printf("%s Entrou na fila de prioridade com prioridade: %d\n", al.nome, prio);
        return 1;
    }
    return 0;
}

//Se a fila de prioridade não está vazia, mostra o nome do primeiro e o remove; a urgência é resolvida no balcão. Se está vazia, consulta o primeiro da fila, remove-o e insere o aluno na pilha de requerimentos.
void atenderProximo(FilaPrio* fiPrio, struct fila* fi, Pilha* pi){
    char nome[30];
    struct aluno al;
    if(!estavazia_FilaPrio(fiPrio)){
        consulta_FilaPrio(fiPrio, nome);
        printf("Fila de prioridade\n");
        printf("Nome: %s\n", nome);
        printf("Urgencia resolvida no balcao\n");
        remove_FilaPrio(fiPrio);
    }
    else if(consulta_Fila(fi, &al)){
        remove_Fila(fi);
        insere_Pilha(pi, al);
        printf("Requerimento do aluno %s inserido na pilha de requerimentos\n", al.nome);
    }
    else{
        printf("Nao ha ninguem na fila para atendimento\n");
    }
}

//Acessa o topo da pilha, remove-o e insere o aluno no final da lista de concluídos.
void despacharRequerimento(Pilha* pi, Lista* li){
    struct aluno al;
    if(acessa_topo_Pilha(pi, &al)){
        remove_Pilha(pi);
        printf("Inserindo requerimento do aluno: %s na lista de concluidos", al.nome);
        insere_lista_final(li,al);
    }
    else{
        printf("Nao ha nenhum requerimento");
    }
}

//Mostra os alunos da lista de concluídos, do primeiro ao último.
void relatorio(Lista* li){
    struct aluno al;
    printf("=== Requerimentos Concluidos ===\n");
    for(int i = 0; i <= tamanho_lista(li); i++){
        busca_lista_pos(li, i, &al);
        printf("Matricula %d | Nome: %s \n",al.matricula, al.nome);
    }
}

//Libera todas as estruturas.
void sair(Hash*ha, ArvBin* arvBi, Fila* fi, FilaPrio* fiPrio ,Pilha* pi, Lista* li){
    liberaHash(ha);
    libera_ArvBin(arvBi);
    libera_Fila(fi);
    libera_FilaPrio(fiPrio);
    libera_Pilha(pi);
    libera_lista(li);
}