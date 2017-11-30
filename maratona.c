#include <stdio.h>
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

