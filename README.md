# Trabalho Pratico 2 Maratona de Programacao - Fatec 20172 Ciro

2º Trabalho Prático da disciplina de linguagem de programação, professor Ciro, Fatec Carapicuiba, 2017 2º Semestre

Professor:         |Ciro Cirne Trindade
-------------------|-------------------------------------
Disciplina:        |Linguagem de Programação
Curso:             |Análise e Desenvolvimento de Sistemas
Data de entrega:   |07/12/2017
Grupos:            |3 alunos


## Descrição

A FATEC de Carapicuíba promove semestralmente sua Maratona de Programação. Os
organizadores da competição tiveram muito trabalho para cadastrar e gerar algumas listagens
de todos os times, devido a grande quantidade de competidores que participam da
competição. Para o ano de 2018 é esperado um número ainda maior de times, por isso, os
organizadores da Maratona de Programação lhe pediram para escrever um programa em C
para gerenciar as informações da próxima edição do evento.

Os organizadores definiram já definiram estrutura básica do programa e fonrceram os
arquivos main.c e maratona.h, mostrados abaixo:

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



    /* maratona.h */
    #ifndef _MARATONA_H
    #define _MARATONA_H
    #define ARQ_TIME        "time.dat"
    #define ARQ_COMP        "competidor.dat"
    #define ARQ_EMAILS      "emails.txt"
    #define ARQ_ETIQUETAS   "etiquetas.txt"
    #define ARQ_LISTAGEM    "listagem.txt"

    typedef struct {
        int id;
        char login[8];
        char senha[21];
        char nome[31];
    } time;

    typedef struct {
        int dia;
        int mes;
        int ano;
    } data;

    typedef struct {
        int id;
        int id_time;
        char nome[61];
        char email[41];
        data nasc;
    } competidor;

    void cadastrar_time(void);
    void consultar_time(void);
    void listar_times(void);
    void listar_competidores(void);
    void gerar_emails(void);
    void gerar_etiquetas(void);
    void imprimir_primeiro_nome(const char *);

    #endif


Você deve fornecer a implementação da função menu() do programa main.c e
desenvolver um arquivo chamado maratona.c com a implementação das funções cujos
protótipos são mostrados no arquivo maratona.h.

A função menu() deve exibir as opções do menu do sistema que são passadas como
parâmetro através do vetor de strings opcoes e devolver a opção selecionada pelo usuário.

O sistema deve possuir as seguintes funcionalidades:

a) Cadastrar Time: esta funcionalidade deve ser implementada através da função
cadastrar_time() . Através dessa opção é possível cadastrar um time de três
competidores na Maratona de Programação. A chave primária da tabela onde os times
serão cadastrados é o identificador do time (membro id da estrutura time) que é um
número sequencial gerado automaticamente, sendo assim, o identificador do primeiro
time será igual a 1, o do segundo time igual a 2, e assim por diante. Os times possuem
um login (membro login da estrutura time) utilizado para autenticação no sistema de
submissão das soluções da prova da Maratona (BOCA). O login também é gerado
automaticamente pelo sistema. O login de todos os times começa com “team” seguido
por seu identificador, portanto, o login do primeiro time será “team1”, o do segundo
time “team2”, e assim por diante (Dica: utilize a função sprintf() para gerar o login). O
usuário deve fornecer a senha (membro senha da estrutura time) utilizada na
autenticação no BOCA e o nome do time (membro nome da estrutura time). Depois o
usuário deve fornecer o nome (membro nome da estrutura competidor), e-mail
(membro email da estrutura competidor) e data de nascimento (membro nasc da
estrutura competidor) dos três competidores do time. Os competidores são associados
a um time através de membro id_time da estrutura competidor que deve possuir o
mesmo valor do membro id da estrutura time ao qual ele pertence. Ou seja, o id_time
dos três competidores do time com id igual a 1 deve ser igual a 1, o id_time dos três
competidores do time com id igual a 2 deve ser igual a 2, e assim por diante. A chave
primária da tabela onde os competidores serão cadastrados é seu identificador
(membro id da estrutura competidor) que, assim como o identificador dos times, é um
número sequencial gerado automaticamente. As informações relativas a um time
(estrutura time) devem ser armazenadas em um arquivo cujo nome é definido pela
constante ARQ_TIME, e as informações relativas aos competidores de um time
(estrutura competidor) devem ser armazenadas em um outro arquivo cujo nome é
definido pela constante ARQ_COMP.

b) Consultar Time: esta funcionalidade deve ser implementada através da função
consultar_time() . Através dessa função o usuário pode consultar os dados de um
determinado time, dado seu login. Se for encontrado um time com o login fornecido
pelo usuário, o sistema deverá exibir os dados completos do time: nome, login, senha,
e o nome, e-mail e data de nascimento dos seus três competidores. Caso contrário,
exibir uma mensagem.

c) Listar Times: esta funcionalidade deve ser implementada através da função
listar_times() . O sistema deverá exibir no vídeo o nome e login de todos os times
cadastrados no formato de tabela.

d) Listar Competidores: esta funcionalidade deve ser implementada através da função
listar_competidores() . O sistema deverá exibir no vídeo em formato de tabela
uma listagem dos competidores cadastrados exibindo o nome, e-mail, data de
nascimento e o nome do time de cada competidor. Depois o sistema deverá perguntar
ao usuário se ele deseja gerar a mesma listagem em um arquivo do tipo texto, caso o
usuário responda que sim, o sistema deve gerar a listagem em um arquivo do tipo
texto, cujo nome é definido pela constante ARQ_LISTAGEM.

e) Gerar E-mails: esta funcionalidade deve ser implementada através da função
gerar_emails() . Através dela deve ser possível gerar um arquivo do tipo texto, cujo
nome é definido pela constante ARQ_EMAILS, contendo uma lista separada por
vírgula dos e-mails de todos os competidores cadastrados.

f) Gerar Etiquetas: esta funcionalidade deve ser implementada através da função
gerar_etiquetas() . Através dessa opção deve ser possível gerar um arquivo do
tipo texto, cujo nome é definido pela constante ARQ_ETIQUETAS, com etiquetas que
identificam cada time. Cada etiqueta deve possuir quatro linhas: na primeira linha
deve aparecer o nome do time, na segunda linha o login do time, na terceira a senha e
na quarta linha, entre parênteses e separados por vírgulas, o primeiro nome dos
competidores do time. Para imprimir o primeiro nome do competidor, utilize a função
imprimir_primeiro_nome() . Deve haver uma linha em branco entre as etiquetas de
cada time.

g) Sair do Programa: esta opção encerra a execução do programa.

## Informações importantes sobre o trabalho

1. Critérios de avaliação:
a) Corretude: 70%
b) Interface: 20%
c) Legibilidade: 10%

2. Todos os trabalhos devem possuir no cabeçalho a identificação dos autores.

3. Trabalhos copiados (com ou sem eventuais disfarces) terão nota dividida pelo número
de cópias (inclusive o original).

4. Trabalhos atrasados não serão aceitos.

5. Trabalhos com erros de sintaxe (ou seja, erros de compilação) receberão nota ZERO.

6. É muito importante que seu programa tenha comentários e esteja bem indentado, ou
seja, digitado de maneira a ressaltar a estrutura de subordinação dos comandos do
programa. A legibilidade do código será levada em consideração pelo critério de
avaliação do trabalho.

7. Você deve enviar os arquivos fonte (.c e .h) da aplicação para o seguinte e-mail:
ciroct@gmail.com

8. Guarde uma cópia do seu trabalho pelo menos até o final do semestre. Este material
pode ser solicitado pelo professor em caso de extravio.
