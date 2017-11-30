/* main.c */
 
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

