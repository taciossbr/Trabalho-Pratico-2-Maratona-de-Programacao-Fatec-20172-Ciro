/* main.c
Autores:
Gabriel Ciccotti Monteiro da Silva
Tacio dos Santos Souza     
Vinícius dos Santos Rocha
*/

#include <stdio.h>
#include <string.h>
#include "maratona.h"
#define CADASTRAR_TIME      1
#define CONSULTAR_TIME      2
#define LISTAR_TIMES        3
#define	LISTAR_COMPETIDORES 4
#define GERAR_EMAILS        5
#define GERAR_ETIQUETAS     6
#define SAIR                7
#define NUM_OP              7

int menu(int, char *[]);

int main() {
    char * opcoes[NUM_OP] = { "Cadastrar Time", "Consultar Time",
           "Listar Times", "Listar Competidores", "Gerar E-mails",
           "Gerar Etiquetas", "Sair do Programa" };
    int op;
    do {
        op = menu(NUM_OP, opcoes);
        switch(op) {
        case CADASTRAR_TIME:
            cadastrar_time();
            break;
        case CONSULTAR_TIME:
            consultar_time();
            break;
        case LISTAR_TIMES:
            listar_times();
            break;
        case LISTAR_COMPETIDORES:
            listar_competidores();
            break;
        case GERAR_EMAILS:
            gerar_emails();
            break;
        case GERAR_ETIQUETAS:
            gerar_etiquetas();
            break;
        case SAIR:
            break;
        default:
            printf( "\n\tOpção inválida!" );
        }
    } while (op != SAIR);
    return 0;
}
/*  menu
    int n: número de opções do menu
    char * ops[]: vetor com as opções
*/
int menu(int n, char * ops[]){
    printf("----------------------------------\n");
    printf("               Menu\n");
    printf("----------------------------------\n\n");

    // imprime o menu
    int i;
    for (i = 0; i < n; i++){
        printf("%d-%s\n", i + 1, ops[i]);
    }

    // recebe input do usuário
    int op;
    printf("\nEscolha a opção desejada: ");
    scanf(" %d", &op);
    return op;
}

