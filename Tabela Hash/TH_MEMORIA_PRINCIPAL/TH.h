#include <stdio.h>
#include <stdlib.h>

#define TAM_VET 101

typedef struct aluno{
  int mat;
  float cr;
  struct aluno *prox;
}TA;

typedef struct inteiro{
  int numero;
  struct inteiro *prox;
}N_INT;

typedef TA* TH[TAM_VET];
typedef N_INT* TH2[TAM_VET];

// Biblioteca de Funções para Tabelas Hash
int TH_hash(int mat, int n);
void TH_inicializa(TH tab, int n);
TA* TH_busca(TH tab, int n, int mat);
void TH_insere(TH tab, int n, int mat, float cr);
void TH_libera(TH tab, int n);
float TH_retira(TH tab, int n, int mat);
void TH_imprime(TH tab, int n);

// Funções criadas para resolução dos exercícios
void TH_inicializa_inteiros(TH2 tab, int n);
N_INT* TH_busca_inteiros(TH2 tab, int n, int mat);
N_INT* TH_aloca_inteiros(int mat);
void TH_insere_inteiros(TH2 tab, int n, int mat);
void TH_retira_inteiros(TH2 tab, int n, int mat);
void TH_libera_inteiros(TH2 tab, int n);
void inter(int* vet1, int qtd_vet1, int* vet2, int qtd_vet2, int* vet_saida);
void dif_sim(int* vet1, int qtd_vet1, int* vet2, int qtd_vet2, int* vetSaida);
void uniao(int* vet1, int qtd_vet1, int* vet2, int qtd_vet2, int* vetSaida);
