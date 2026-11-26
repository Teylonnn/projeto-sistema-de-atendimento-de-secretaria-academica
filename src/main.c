#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TABELA_HASH 11 
#define TAMANHO_NOME 30

/*Projeto Final da matéria de Estrutura de Dados 1 - Bloco 3 - UESPI - CTU
  Dupla: - THEILLON ARAUJO DOS SANTOS 
         - JESUS EMANUEL ALVES DAS NEVES


  OBS: para execução as vezes tem que executar o comando antes:
  gcc -Wall -Wextra -g3 -I lib src/main.c lib/ArvoreBinaria.c lib/FilaDin.c lib/FilaPrioridade.c lib/ListaDinEncadDupla.c lib/PilhaDin.c lib/TabelaHash.c -o src/output/main.exe
*/

#include "../lib/Aluno.h"
#include "../lib/TabelaHash.h"
#include "../lib/ArvoreBinaria.h"
#include "../lib/FilaDin.h"
#include "../lib/FilaPrioridade.h"
#include "../lib/PilhaDin.h"
#include "../lib/ListaDinEncadDupla.h"

//--------------------------------- Protótitpos De Funções ---------------------------------
    // Leitura de dados
        int   obterMat(void);
        char* obterNome(char *nome);
        float obterNota(int *contador);
        int   obterPrioridade(void);

    // Aluno
        struct aluno criarAluno(struct aluno aluno, int matriculaDoAluno, char *nomeDoAluno, float primeiraNotaDoAluno, float segundaNotaDoAluno, float terceiraNotaDoAluno);
        void foiCadastrado(int i);
        void exibirAluno(struct aluno aluno);

    // Opções 1 a 4
        void cadastrarAluno(Hash *tabelaHash, ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas, int *quantidadeAlunosCadastrados);
        void consultarAluno(Hash *tabelaHash);
        void listagemDeMatriculasAtivas(ArvBin *arvoreBinaria);
        void trancarMatriculaAtiva(ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas);

    // Opções 5 a 9
        int  chegadaAtendimento(ArvBin *raiz, Hash *ha, Fila *fi);
        int  RegistrarUrgencia(ArvBin *raiz, Hash *ha, FilaPrio *fi);
        void atenderProximo(FilaPrio *fiPrio, Fila *fi, Pilha *pi);
        void despacharRequerimento(Pilha *pi, Lista *li);
        void relatorio(Lista *li);

    // Menu e encerramento
        void templateMenuDeOpcoes(void);
        void menuSistemaSecretariaAcademica(Hash *tabelaHash, ArvBin *arvoreBinaria, Fila *fi, FilaPrio *fiPrio, Pilha *pi, Lista *li, int *quantidadeDeMatriculasAtivas, int *quantidadeAlunosCadastrados);
        void sair(Hash *ha, ArvBin *arvBi, Fila *fi, FilaPrio *fiPrio, Pilha *pi, Lista *li);



// --------------------------------- FUNÇÕES ---------------------------------

//Função Princiapal 
int main(){
    Hash *tabelaHash = criaHash(MAX_TABELA_HASH);
    ArvBin *arvoreBinaria = cria_ArvBin();
    Fila *fi = cria_Fila();
    FilaPrio *fiPrio = cria_FilaPrio();
    Pilha *pi = cria_Pilha();
    Lista *li = cria_lista();

    int quantidadeDeMatriculasAtivas = 0;
    int quantidadeAlunosCadastrados = 0;
    menuSistemaSecretariaAcademica(tabelaHash, arvoreBinaria, fi, fiPrio, pi, li, &quantidadeDeMatriculasAtivas, &quantidadeAlunosCadastrados);

    //caso opcao = 0(sair)
    sair(tabelaHash, arvoreBinaria, fi, fiPrio, pi, li);

    return 0;
}

//Função do menu
void menuSistemaSecretariaAcademica(Hash *tabelaHash, ArvBin *arvoreBinaria, Fila *fi, FilaPrio *fiPrio, Pilha *pi, Lista *li, int *quantidadeDeMatriculasAtivas, int *quantidadeAlunosCadastrados){
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
                if((*quantidadeAlunosCadastrados >= 11)){
                    printf("Limite maximo alcançado !!! \n");
                }
                else{
                    cadastrarAluno(tabelaHash, arvoreBinaria, quantidadeDeMatriculasAtivas, quantidadeAlunosCadastrados);
                }
                break;
            case 2:
                // Verificação se o cadastro de alunos alcançou o limite máximo da tabela hash;
                if((*quantidadeAlunosCadastrados <= 0)){
                    printf("Sem alunos cadastrados!!! \n");
                }
                else{
                    consultarAluno(tabelaHash);
                }
                break;
            case 3:
                // Verificação se a há matrículas cadastradas;
                if((*quantidadeDeMatriculasAtivas) <= 0){
                    printf("Sem matriculas ativas. \n");                   
                }
                else{
                    listagemDeMatriculasAtivas(arvoreBinaria);
                }
                break;
            case 4:
                // Verificação se a há matrículas cadastradas;
                if((*quantidadeDeMatriculasAtivas) <= 0){
                    printf("Sem matriculas ativas. \n");                   
                }
                else{
                    trancarMatriculaAtiva(arvoreBinaria, quantidadeDeMatriculasAtivas);
                }
                break;
            case 5:
                chegadaAtendimento(arvoreBinaria, tabelaHash, fi);
                break;
            case 6:
                RegistrarUrgencia(arvoreBinaria, tabelaHash, fiPrio);
                break;
            case 7:
                atenderProximo(fiPrio, fi, pi);
                break;
            case 8:
                despacharRequerimento(pi, li);
                break;
            case 9:
                relatorio(li);
                break;
            default:
                printf("Opcao invalida !!!\n");
                break;
        }

    }while(opcao != 0);
}

// Função de template do menu de opções
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

//Função para obter matrícula
int obterMat(){
    int mat;

    printf("Matricula:  ");
    scanf("%d", &mat);

    return mat;
}

//Função para obter nome
char* obterNome(char *nome){
    printf("Nome:  ");
    scanf(" %29[^\n]", nome);

    return nome;
}

//Função para obter nota
float obterNota(int *contador){
    float nota;

    printf("%d.o Nota:  ", *contador);
    scanf("%f", &nota);

    (*contador)++;
    return nota;
}

//Função para obter prioridade
int obterPrioridade(){
    int prioridade;

    printf("Prioridade: ");
    scanf("%d", &prioridade);

    return prioridade;
}


//Função para criação do Aluno
struct aluno criarAluno(struct aluno aluno, int matriculaDoAluno, char *nomeDoAluno, float primeiraNotaDoAluno, float segundaNotaDoAluno, float terceiraNotaDoAluno){
    aluno.matricula = matriculaDoAluno;
    strcpy(aluno.nome, nomeDoAluno);
    aluno.n1 = primeiraNotaDoAluno;
    aluno.n2 = segundaNotaDoAluno;
    aluno.n3 = terceiraNotaDoAluno;

    return aluno;
}

//Função verifica se aluno foi cadastrado
void foiCadastrado(int i){
    i == 1? printf("Aluno cadastrado !!!") : printf("Aluno não pode ser cadastrado.");
}

//Lê matrícula, nome e três notas. Se a matrícula já existe na tabela hash, recusa. Caso contrário, insere o aluno na tabela hash e a matrícula na árvore.
void cadastrarAluno(Hash *tabelaHash, ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas, int *quantidadeAlunosCadastrados){
    int matriculaDoAluno;
    int contador = 1;
    char nomeDoAluno[TAMANHO_NOME];
    float primeiraNotaDoAluno, segundaNotaDoAluno, terceiraNotaDoAluno; 

    // Leitura dos dados do usuário;
    matriculaDoAluno = obterMat(); 
    obterNome(nomeDoAluno);
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

//Função exibir um aluno
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
    emordem_ArvBin(arvoreBinaria);
    printf("\n-----------------------------------\n");

}

// Função que remove matrícula ativa da árvore; 
void trancarMatriculaAtiva(ArvBin *arvoreBinaria, int *quantidadeDeMatriculasAtivas ){
    int matriculaDoAluno = 0;

    // Leitura dos dados;
    matriculaDoAluno = obterMat();

    // Verificação se a matrícula existe;
    if(!consulta_ArvBin(arvoreBinaria, matriculaDoAluno)){
        printf("Matricula não existe ou nao esta ativa.\n");
        return;
    }

    // Remoção da matrícula;
    remove_ArvBin(arvoreBinaria, matriculaDoAluno);
    (*quantidadeDeMatriculasAtivas)--;

    printf("Matricula trancada com sucesso !!!\n");

}

//Lê a matrícula. Se ela não está na árvore, recusa. Caso contrário, busca o aluno na tabela hash e o insere na fila.
int chegadaAtendimento(ArvBin *raiz, Hash* ha, Fila* fi){
    struct aluno al;
    int mat = obterMat();

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
int RegistrarUrgencia(ArvBin *raiz, Hash* ha, FilaPrio* fi){
    struct aluno al;
    int mat = obterMat();
    int prio = obterPrioridade();

    if(prio < 1 || prio > 5){
        printf("Prioridade: %d invalida\n", prio);
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
    int tamanhoLista = tamanho_lista(li);
    for(int i = 1; i <= tamanhoLista; i++){
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