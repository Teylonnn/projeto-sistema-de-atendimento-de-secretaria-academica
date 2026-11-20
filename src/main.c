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

void cadastrarAluno(Hash *tabelaHash, ArvBin *arvoreBinaria){
    int matriculaDoAluno;
    char nomeDoAluno[TAMANHO_NOME];
    float primeiraNotaDoAluno, segundaNotaDoAluno, terceiraNotaDoAluno;


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

    struct aluno aluno;
    aluno.matricula = matriculaDoAluno;
    strcpy(aluno.nome, nomeDoAluno);
    aluno.n1 = primeiraNotaDoAluno;
    aluno.n2 = segundaNotaDoAluno;
    aluno.n1 = terceiraNotaDoAluno;

    if(buscaHash_EnderAberto(tabelaHash, matriculaDoAluno, &aluno) == 1){
        printf("Matricula já cadastrada.\n");
        return;
    }
    
    int i = insereHash_EnderAberto(tabelaHash, aluno);
    insere_ArvBin(arvoreBinaria, matriculaDoAluno);

    i == 1? printf("Aluno cadastrado !!!") : printf("Aluno não pode ser cadastrado.");
   
}

void exibirMatriculasAtivas(ArvBin *arvoreBinaria){
    printf("      < MATRICULAS ATIVAS >\n");
    printf("-----------------------------------\n");
    emordem_ArvBin(arvoreBinaria);
    printf("\n-----------------------------------\n");

}

void menuSistemaSecretariaAcademica(Hash *tabelaHash, ArvBin *arvoreBinaria){
    int opcao;

    do{
        templateMenuDeOpcoes();
        printf("Opcao (0 a 9):  ");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                break;
            case 1:
            cadastrarAluno(tabelaHash, arvoreBinaria);
                break;
            case 2:
                break;
            case 3:
                exibirMatriculasAtivas(arvoreBinaria);
                break;
            case 4:
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
    printf("        <--- SISTEMA DE GESTAO DA SECRETARIA ACADEMICA ---> \n");
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
    menuSistemaSecretariaAcademica(tabelaHash, arvoreBinaria);

    return 0;
}