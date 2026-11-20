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

void cadastrarAluno(Hash *tabelaHash, ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas, int *quantidadeAlunosCadastrados){
    int matriculaDoAluno;
    char nomeDoAluno[TAMANHO_NOME];
    float primeiraNotaDoAluno, segundaNotaDoAluno, terceiraNotaDoAluno;

    // Leitura dos dados do usuário;
    printf("Matricula:  ");
    scanf("%d", &matriculaDoAluno);
    printf("Nome:  ");
    scanf(" %99[^\n]", nomeDoAluno);
    printf("1.o Nota:  ");
    scanf("%f", &primeiraNotaDoAluno);
    printf("2.o Nota:  ");
    scanf("%f", &segundaNotaDoAluno);
    printf("3.o Nota:  ");
    scanf("%f", &terceiraNotaDoAluno);

    // Criação de aluno;
    struct aluno aluno;
    aluno.matricula = matriculaDoAluno;
    strcpy(aluno.nome, nomeDoAluno);
    aluno.n1 = primeiraNotaDoAluno;
    aluno.n2 = segundaNotaDoAluno;
    aluno.n3 = terceiraNotaDoAluno;

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

    i == 1? printf("Aluno cadastrado !!!") : printf("Aluno não pode ser cadastrado.");
   
}

// Função que busca dado aluno na tabela hash;
void consultarAluno(Hash *tabelaHash){
    struct aluno alAux;
    int matriculaDoAluno = 0;

    // Leitura dos dados;
    printf("Matricula:  ");
    scanf(" %d", &matriculaDoAluno);

    // Verificação se o aluno não existe na tabela hash;
    if(buscaHash_EnderAberto(tabelaHash,  matriculaDoAluno, &alAux) == 0){
        printf("Nada foi encontrado !!!\n");
        return;
    }

    // Exibição dos dados da tabela hash;
    printf("\n\nMatricula:  %d", alAux.matricula);
    printf("\nNome:  %s", alAux.nome);
    printf("\n1.o Nota:  %.2f", alAux.n1);
    printf("\n2.o Nota:  %.2f", alAux.n2);
    printf("\n3.o Nota:  %.2f ", alAux.n3);
}

// Função que lista todos as matrículas ativas na árvore;
void listagemDeMatriculasAtivas(ArvBin *arvoreBinaria){
    printf("      < MATRICULAS ATIVAS >\n");
    printf("-----------------------------------\n");
    emordem_ArvBin(arvoreBinaria);
    printf("\n-----------------------------------\n");

}

// Função que remove matrícula ativa da árvore; 
void trancarMatriculaAtiva(ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas ){
    int matriculaDoAluno = 0;

    // Leitura dos dados;
    printf("Matricula:  ");
    scanf(" %d", &matriculaDoAluno);

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