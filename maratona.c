/* maratona.c 
Autores:
Gabriel Ciccotti Monteiro da Silva
Tacio dos Santos Souza     
Vinícius dos Santos Rocha
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "maratona.h"

/*  cadastrar_time

    função responsável por receber os dados dos times e dos competidores,
e grava-los em seus respectivos arquivos.
*/
void cadastrar_time(void){
    FILE * times;
    time t;
    
    // verifica  se o arquivo foi aberto corretamente
    if ((times = fopen(ARQ_TIME, "ab")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_TIME);
        return;
    }
    // desloca o indicador de posição para o final do arquivo
    fseek(times, 0, SEEK_END);
    
    t.id = ftell(times) / sizeof(time) + 1; // gera o id do time
    
    sprintf(t.login, "team%d", t.id); // gera o login do time
    
    puts("\nCadastro de time\n\n");
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
    // verifica se o arquivo foi aberto corretamente
    if ((competidores = fopen(ARQ_COMP, "ab")) == NULL){
        fprintf(stderr, "\nErro: não foi possivel abrir o arquivo %s!\n",
                ARQ_COMP);
        return;
    }
    competidor c[3];

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
/*  consultar_time

    le o login do time, verifica se é válido, e imprime as informações 
referentes ao time

*/
void consultar_time(void){
    FILE * times, * competidores;
    // verifica  se o arquivos foram abertos corretamente
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
        // desloca o indicador de posição para a posição do registro do time
        fseek(times, (id - 1) * sizeof(time), SEEK_SET);
        fread(&t, sizeof(time), 1, times);
        fclose(times);
        
        printf("\n\nID:\t%d\n", t.id);
        printf("Login:\t%s\n", t.login);
        printf("Nome:\t%s\n", t.nome);
        printf("Senha:\t%s\n", t.senha);
        
        printf("\n\nCompetidores do time\n\n");
        // desloca o indicador de posição para a posição do registro dos competidores
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

/*  listar_times

    exibe na tela uma tabela com a listagem de todos os times cadastrados
*/
void listar_times(void){
    FILE * times;
    // verifica  se o arquivo foi aberto corretamente
    if ((times = fopen(ARQ_TIME, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_TIME);
        return;
    }
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
    fclose(times);
}

void listar_competidores(void){
    /* Obs.:
         Por questões de melhor legibilidade da tabela em telas pequenas 
        decidimos exibir apenas os caracteres iniciais das strings contendo o nome dos competidores
    */
    FILE * competidores;
    
    if ((competidores = fopen(ARQ_COMP, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_COMP);
        return;
    }
    FILE * times;
    if ((times = fopen(ARQ_TIME, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_TIME);
        return;
    }
    
    puts("Lista de Competidores\n");
    int i;
    for (i = 0; i < 132; i++){
        putchar('-');
    }
    putchar('\n');
    printf("|%-51.50s| %-31.30s| %-11.10s| %-31.30s|\n",
           "Nome", "Email", "Nascimento", "Time");
    for (i = 0; i < 132; i++){
        putchar('-');
    }
    putchar('\n');

    competidor c;
    while(fread(&c, sizeof(competidor), 1, competidores) > 0){
        time t;
        fseek(times, (c.id_time - 1) * sizeof(time), SEEK_SET);
        fread(&t, sizeof(time), 1, times);
        printf("|%-51.50s| %-31.30s| %02d/%02d/%04d | %-31.30s|\n",
               c.nome,
               c.email,
               c.nasc.dia,
               c.nasc.mes,
               c.nasc.ano,
               t.nome);
    }
    for (i = 0; i < 132; i++){
        putchar('-');
    }
    printf("\n\n");

    

    // pergunta se o usario deseja gravar um arquivo com a listagem
    printf("Você deseja salvar esta tabela em um arquivo? ");
    char o;
    scanf(" %c", &o);

    if (o == 'S' || o == 's'){
        rewind(competidores);
        // grava o arquivo de listagem
        FILE * listagem;
        if ((listagem = fopen(ARQ_LISTAGEM, "w")) == NULL) {
            fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                    ARQ_COMP);
            return;
        }

        fputs("Lista de Competidores\n", listagem);
        // imprime uma linha no cabeçalho
        for (i = 0; i < 142; i++){
            fprintf(listagem, "-");
        }
        fprintf(listagem, "\n");
        fprintf(listagem, "|%-61.60s| %-31.30s| %-11.10s| %-31.30s|\n",
            "Nome", "Email", "Nascimento", "Time");
        for (i = 0; i < 142; i++){
            fprintf(listagem, "-");
        }
        fprintf(listagem, "\n");

        competidor c;

        while(fread(&c, sizeof(competidor), 1, competidores) > 0){
            time t;
            fseek(times, (c.id_time - 1) * sizeof(time), SEEK_SET);
            fread(&t, sizeof(time), 1, times);
            fprintf(listagem, "|%-61.60s| %-31.30s| %02d/%02d/%04d | %-31.30s|\n",
                c.nome,
                c.email,
                c.nasc.dia,
                c.nasc.mes,
                c.nasc.ano,
                t.nome);
        }
        for (i = 0; i < 142; i++){
            fprintf(listagem, "-");
        }
        fprintf(listagem, "\n\n");
        printf("\nA tabela foi salva no arquivo %s.\n", ARQ_LISTAGEM);
        fclose(listagem);
    }
    fclose(competidores);
    fclose(times);
}

void gerar_emails(void){
    FILE * competidores, * times, * emails;
    if ((competidores = fopen(ARQ_COMP, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_COMP);
        return;
    }
    
    if ((times = fopen(ARQ_TIME, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_TIME);
        return;
    }
    if ((emails = fopen(ARQ_EMAILS, "w")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_EMAILS);
        return;
    }
    
    // obtem a quantidade de competidores cadastrados
    fseek(competidores, 0, SEEK_END);
    int q = ftell(competidores) / sizeof(competidor);
    rewind(competidores);

    int i = 0;
    competidor c[q];
    while(fread(&c[i], sizeof(competidor), 1, competidores) > 0){
        i++; 
    }
    for (i = 0; i < q; i++){
        fprintf(emails, "%s", c[i].email);
        if (i != q - 1){
            fputc(',', emails);
        }
    }

    printf("\n\nLista de emails gravada no arquivo %s.\n\n", ARQ_EMAILS);
    fclose(competidores);
    fclose(emails);
}

void gerar_etiquetas(void){
    FILE * etiquetas, * times, *competidores;

    if ((competidores = fopen(ARQ_COMP, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_COMP);
        return;
    }
    
    if ((times = fopen(ARQ_TIME, "rb")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_TIME);
        return;
    }
    if ((etiquetas = fopen(ARQ_ETIQUETAS, "w")) == NULL) {
        fprintf(stderr, "\nErro: não foi possível abrir o arquivo %s!\n", 
                ARQ_ETIQUETAS);
        return;
    }
    time t;
    competidor c[3];
    while(fread(&t, sizeof(time), 1, times) > 0){
        fread(&c, sizeof(competidor), 3, competidores);
        fprintf(etiquetas, "%s\n", t.nome);
        fprintf(etiquetas, "%s\n", t.login);
        fprintf(etiquetas, "%s\n", t.senha);
        
        fprintf(etiquetas, "(");
        int i;
        for (i = 0; i < 3; i++){
            fclose(etiquetas);
            imprimir_primeiro_nome(c[i].nome);
            etiquetas = fopen(ARQ_ETIQUETAS, "a");
            if (i + 1 != 3){
                fprintf(etiquetas, ", ");
            } else {
                fprintf(etiquetas, ")\n\n");
            }
        }
    }
    fclose(etiquetas);
    fclose(times);
    fclose(competidores);
}

void imprimir_primeiro_nome(const char * nome){
    FILE * etiquetas;
    etiquetas = fopen(ARQ_ETIQUETAS, "a");
    int i;
    for (i = 0; nome[i] != ' ' && nome[i] != '\0'; i++){
    //putchar(nome[i]);
    }
    char primeiro[61];
    strncpy(primeiro, nome, i);
    primeiro[i] = '\0';
    fprintf(etiquetas, "%s", primeiro);
    fclose(etiquetas);
}


