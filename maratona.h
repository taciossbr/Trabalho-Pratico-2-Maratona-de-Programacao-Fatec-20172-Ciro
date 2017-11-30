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
