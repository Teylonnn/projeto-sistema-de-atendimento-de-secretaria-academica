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

void menuSistemaSecretariaAcademica(){
    int opcao;

    do{
        printf("Opcao (0 a 9):  ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                break;
            case 2:
                break;
            case 3:
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
                printf("Opcao invalida !!!");
                break;
        }

    }while(opcao != 0);
}

void templateMenuDeOpcoes(){
    printf("        <--- SISTEMA DE GESTÃO DA SECRETARIA ACADÊMICA ---> \n");
    printf("---------------------------------------------------------------------\n");
    printf("[1] - Cadastrar aluno\n");
    printf("[2] - Consultar aluno\n");
    printf("[3] - Listagem de matrículas ativas\n");
    printf("[4] - Trancar matrícula\n");
    printf("[5] - Chegada para atendimento\n");
    printf("[6] - Registrar urgência\n");
    printf("[7] - Atender próximo\n");
    printf("[8] - Despachar requerimento\n");
    printf("[9] - Relatório\n");
    printf("[0] - Sair\n");
    printf("---------------------------------------------------------------------\n");
}

int main(){

    return 0;
}