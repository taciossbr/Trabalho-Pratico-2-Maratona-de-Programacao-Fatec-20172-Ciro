#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "maratona.h"

void cadastrar_time(void){
    FILE * times;
    time t;
    
    if ((times = fopen(ARQ_TIME, "ab")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_TIME);
        return;
    }
    // desloca o indicador de posição para o final do arquivo
    fseek(times, 0, SEEK_END);
    
    t.id = ftell(times) / sizeof(time) + 1; // gera o id do time
    
    sprintf(t.login, "team%d", t.id); // gera o login do time
    
    puts("\nNovo cliente");
    printf("ID do time: %d\n", t.id); 
    printf("Login do time: %s\n", t.login);
    printf("Digite uma senha: ");
    scanf(" %20[^\n]", t.senha);
    printf("Digite um nome para o time: ");
    scanf(" %30[^\n]", t.nome);
    fwrite(&t, sizeof(time), 1, times);
    fclose(times);
    puts("Time cadastrado com sucesso!\n");
    
    printf("Cadastro de competidores do time: %s\n\n", t.nome);
    FILE * competidores;
    competidor c[3];
    
    if ((competidores = fopen(ARQ_COMP, "ab")) == NULL){
        fprintf(stderr, "\nErro: não foi possivel abrir o arquivo %s!\n",
                ARQ_COMP);
        return;
    }
    // desloca o indicador de posição para o final do arquivo
    fseek(competidores, 0, SEEK_END);
    
    int i;
    for (i = 0; i < 3; i++){
        // gera o id do competidor
        c[i].id = ftell(competidores) / sizeof(competidor) + 1; 
        c[i].id_time = t.id; // grava o id do time
        printf("ID do competidor: %d\n", c[i].id);
        printf("Digite o nome do competidor: ");
        scanf(" %60[^\n]", c[i].nome);
        printf("Digite um email do competidor: ");
        scanf(" %40[^\n]", c[i].email);
        printf("Digite a data de nascimento do competidor(dd/mm/aaaa): "); 
        scanf(" %d/%d/%d",
               &(c[i].nasc.dia),
               &(c[i].nasc.mes),
               &(c[i].nasc.ano));
        
        fwrite(&c[i], sizeof(competidor), 1, competidores);
        puts("Competidor cadastrado com sucesso!\n\n");
    }
    fclose(competidores);
}


void consultar_time(void){
    FILE * times, * competidores;
    
    if ((times = fopen(ARQ_TIME, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_TIME);
        return;
    }
    if ((competidores = fopen(ARQ_COMP, "rb")) == NULL){
        fprintf(stderr, "\nErro: não foi possivel abrir o arquivo %s!\n",
                ARQ_COMP);
        return;
    }
    
    printf("\n\nConsulta de Times\n\n");
    
    competidor c[3];
    time t;
    char t_nome[8];
    int id;
    printf("Digite o login do time que deseja consultar: ");
    scanf(" %8[^\n]", t_nome);
    // scanf(" %s%d", nome, &id);
    id = atoi(&t_nome[4]);

    // verifica se o indice é valido
    fseek(times, 0, SEEK_END);
    int tam = ftell(times);
    if (id * sizeof(time) > tam){
        fprintf(stderr, "O Time que você procura não esta cadastrado.\n");
    } else {
        // printf("\n\n\n\n%d\n\n\n\n\n", id);
        // desloca o indicador de posição para a posição do registro do time
        // printf("\n\n\n\n%d\n\n\n\n\n", (id - 1) * sizeof(time));
        fseek(times, (id - 1) * sizeof(time), SEEK_SET);
        fread(&t, sizeof(time), 1, times);
        fclose(times);
        
        printf("\n\nID:\t%d\n", t.id);
        printf("Login:\t%s\n", t.login);
        printf("Nome:\t%s\n", t.nome);
        printf("Senha:\t%s\n", t.senha);
        
        printf("\n\nCompetidores do time\n\n");
        fseek(competidores, (t.id - 1) * sizeof(competidor) * 3, SEEK_SET);
        fread(&c, sizeof(competidor), 3, competidores);
        fclose(competidores);
        
        int i;
        for (i = 0; i < 3; i++){
            printf("ID:                    %d\n", c[i].id);
            printf("Nome:                  %s\n", c[i].nome);
            printf("Email:                 %s\n", c[i].email);
            printf("Data de Nascimento:    %d/%d/%d\n",
                c[i].nasc.dia,
                c[i].nasc.mes,
                c[i].nasc.dia);
            puts("\n");
        } 
    
    }


            
    
}

void listar_times(void){
    FILE * times;
    times = fopen(ARQ_TIME, "rb"); // abre o arquivo para leitura

    // imprime cabeçalho da tabela
    int i;
    // imprime uma linha no começo do cabeçalho
    for (i = 0; i < 51; i++){
        putchar('-');
    }
    putchar('\n');
    printf("|%-35.31s| %-12.8s|\n", "Nome", "Login");
    // imprime uma linha no final do cabeçalho
    for (i = 0; i < 51; i++){
        putchar('-');
    }
    putchar('\n');

    // imprime o corpo da tabela
    time t;
    while(fread(&t, sizeof(time), 1, times) > 0){
        printf("|%-35.31s| %-12.8s|\n", t.nome, t.login);
        
    }
    // imprime uma linha no final da tabela
    for (i = 0; i < 51; i++){
        putchar('-');
    }
    putchar('\n');
}
