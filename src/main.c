#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TABELA_HASH 11
#define TAMANHO_NOME 30

#include "../lib/Aluno.h"
#include "../lib/TabelaHash.h"
#include "../lib/ArvoreBinaria.h"
#include "../lib/FilaDin.h"
#include "../lib/FilaPrioridade.h"
#include "../lib/PilhaDin.h"
#include "../lib/ListaDinEncadDupla.h"

void templateMenuDeOpcoes(void);

int obterMat(){
    int mat;

    printf("Matricula:  ");
    scanf("%d", &mat);

    return mat;
}

char* obterNome(char *nome){
    printf("Nome:  ");
    scanf(" %99[^\n]", nome);

    return nome;
}

float obterNota(int *contador){
    float nota;

    printf("%d.o Nota:  ", *contador);
    scanf("%f", &nota);

    (*contador)++;
    return nota;
}

struct aluno criarAluno(struct aluno aluno, int matriculaDoAluno, char *nomeDoAluno, float primeiraNotaDoAluno, float segundaNotaDoAluno, float terceiraNotaDoAluno){
    aluno.matricula = matriculaDoAluno;
    strcpy(aluno.nome, nomeDoAluno);
    aluno.n1 = primeiraNotaDoAluno;
    aluno.n2 = segundaNotaDoAluno;
    aluno.n3 = terceiraNotaDoAluno;

    return aluno;
}

void foiCadastrado(int i){
    i == 1? printf("Aluno cadastrado !!!") : printf("Aluno não pode ser cadastrado.");
}

void cadastrarAluno(Hash *tabelaHash, ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas, int *quantidadeAlunosCadastrados){
    int matriculaDoAluno;
    int contador = 1;
    char nomeDoAluno[TAMANHO_NOME];
    float primeiraNotaDoAluno, segundaNotaDoAluno, terceiraNotaDoAluno; 

    // Leitura dos dados do usuário;
    matriculaDoAluno = obterMat(); 
    strcpy(nomeDoAluno, obterNome(nomeDoAluno));
    primeiraNotaDoAluno = obterNota(&contador);
    segundaNotaDoAluno = obterNota(&contador);
    terceiraNotaDoAluno = obterNota(&contador);

    // Criação de aluno;
    struct aluno aluno;
    aluno = criarAluno(aluno, matriculaDoAluno, nomeDoAluno, primeiraNotaDoAluno, segundaNotaDoAluno, terceiraNotaDoAluno);
    

    // verificação se a matrícula já está cadastrada;
    if(buscaHash_EnderAberto(tabelaHash, matriculaDoAluno, &aluno) == 1){
        printf("Matricula já cadastrada.\n");
        return;
    }
    
    // Adição do aluno na tabela hash e matrícula na árvore binária;
    int i = insereHash_EnderAberto(tabelaHash, aluno);
    insere_ArvBin(arvoreBinaria, matriculaDoAluno);
    (*quantidadeDeMatriculasAtivas)++;
    (*quantidadeAlunosCadastrados)++;
    contador = 0;

    foiCadastrado(i);
   
}

void exibirAluno(struct aluno aluno){
    // Exibição dos dados da tabela hash;
    printf("\n\nMatricula:  %d", aluno.matricula);
    printf("\nNome:  %s", aluno.nome);
    printf("\n1.o Nota:  %.2f", aluno.n1);
    printf("\n2.o Nota:  %.2f", aluno.n2);
    printf("\n3.o Nota:  %.2f ", aluno.n3);
}

// Função que busca dado aluno na tabela hash;
void consultarAluno(Hash *tabelaHash){
    struct aluno alAux;
    int matriculaDoAluno = 0;

    // Leitura dos dados;
    matriculaDoAluno = obterMat();

    // Verificação se o aluno não existe na tabela hash;
    if(buscaHash_EnderAberto(tabelaHash,  matriculaDoAluno, &alAux) != 1){
        printf("Nada foi encontrado !!!\n");
        return;
    }

    exibirAluno(alAux);
}

// Função que lista todos as matrículas ativas na árvore;
void listagemDeMatriculasAtivas(ArvBin *arvoreBinaria){
    printf("      < MATRICULAS ATIVAS >\n");
    printf("-----------------------------------\n");
    exibirArvBinEmOrdem(arvoreBinaria);
    printf("\n-----------------------------------\n");

}

// Função que remove matrícula ativa da árvore; 
void trancarMatriculaAtiva(ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas ){
    int matriculaDoAluno = 0;

    // Leitura dos dados;
    matriculaDoAluno = obterMat();

    // Verificação se a matrícula existe;
    if(consulta_ArvBin(arvoreBinaria, matriculaDoAluno != 1)){
        printf("Matricula não existe ou nao esta ativa.\n");
        return;
    }

    // Remoção da matrícula;
    remove_ArvBin(arvoreBinaria, matriculaDoAluno);
    (*quantidadeDeMatriculasAtivas)--;

    printf("Matricula trancada com sucesso !!!\n");

}

void menuSistemaSecretariaAcademica(Hash *tabelaHash, ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas, int *quantidadeAlunosCadastrados){
    int opcao;

    do{
        templateMenuDeOpcoes();
        printf("Opcao (0 a 9):  ");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                break;
            case 1:
                // Verificação se o cadastro de alunos alcançou o limite máximo da tabela hash;
                if((*quantidadeAlunosCadastrados > 11)){
                    printf("Limite maximo alcançado !!! \n");
                }
                else{
                    cadastrarAluno(tabelaHash, arvoreBinaria, quantidadeDeMatriculasAtivas, quantidadeAlunosCadastrados);
                }
               ;
                break;
            case 2:
                consultarAluno(tabelaHash);
                break;
            case 3:
                listagemDeMatriculasAtivas(arvoreBinaria);
                break;
            case 4:
                // Verificação se a há matrículas cadastradas;
                if((*quantidadeDeMatriculasAtivas) <= 0){
                    printf("Sem matriculas ativas. \n");                   
                }
                else{
                    trancarMatriculaAtiva(arvoreBinaria, quantidadeDeMatriculasAtivas );
                }
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                printf("Opcao invalida !!!\n");
                break;
        }

    }while(opcao != 0);
}

void templateMenuDeOpcoes(){
    printf("\n        <--- SISTEMA DE GESTAO DA SECRETARIA ACADEMICA ---> \n");
    printf("---------------------------------------------------------------------\n");
    printf("[1] - Cadastrar aluno\n");
    printf("[2] - Consultar aluno\n");
    printf("[3] - Listagem de matriculas ativas\n");
    printf("[4] - Trancar matricula\n");
    printf("[5] - Chegada para atendimento\n");
    printf("[6] - Registrar urgencia\n");
    printf("[7] - Atender proximo\n");
    printf("[8] - Despachar requerimento\n");
    printf("[9] - Relatorio\n");
    printf("[0] - Sair\n");
    printf("---------------------------------------------------------------------\n");
}

int main(){
    Hash *tabelaHash = criaHash(MAX_TABELA_HASH);
    ArvBin *arvoreBinaria = cria_ArvBin();
    int quantidadeDeMatriculasAtivas = 0;
    int quantidadeAlunosCadastrados = 0;
    menuSistemaSecretariaAcademica(tabelaHash, arvoreBinaria, &quantidadeDeMatriculasAtivas, &quantidadeAlunosCadastrados);

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