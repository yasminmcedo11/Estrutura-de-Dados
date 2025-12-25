#include <stdio.h>
#include <stdlib.h>

typedef struct aluno{
  int mat, prox, status;
  float cr;
}TA;

typedef struct inteiro{
  int numero, prox, status;
}N_INT;

// Biblioteca de Funções para Tabelas Hash em Memória Secundária
void TH_inicializa(char *tabHash, char *dados, int n);
TA* TH_busca(char *tabHash, char *dados, int n, int mat);
float TH_retira(char *tabHash, char *arq, int n, int mat);
void TH_insere(char *tabHash, char *arq, int n, int mat, float cr);
void TH_imprime (char *nome_hash, char *nome_dados, int m);

// Funções criadas para resolução dos exercícios
void TH_insere_inteiros(char *tabHash, char *arq, int n, int mat);
N_INT* TH_aloca_inteiros(int mat);
N_INT* TH_busca_inteiros(char *tabHash, char *dados, int n, int mat);
void TH_retira_inteiros(char *tabHash, char *arq, int n, int mat);
void inter(char* arq1, char* arq2, char* saida);
void dif_sim(char* arq1, char* arq2, char* saida);
void uniao(char* arq1, char* arq2, char* saida);
