#include <stdio.h>
#include <stdlib.h>


typedef struct arvbm{
  int nchaves, folha, *chave;
  struct arvbm **filho, *prox;
}TARVBM;

// Biblioteca de Funções de Árvore B+
TARVBM *TARVBM_cria(int t);
TARVBM *TARVBM_inicializa(void);
TARVBM *TARVBM_busca(TARVBM *a, int mat);
TARVBM *TARVBM_insere(TARVBM *T, int mat, int t);
TARVBM* TARVBM_retira(TARVBM* arv, int k, int t);
void TARVBM_libera(TARVBM *a);
void TARVBM_imprime(TARVBM *a);
void TARVBM_imprime_chaves(TARVBM *a);

// Funções desenvolvidas para resolução dos exercícios
int suc (TARVBM *a, int elem);
int aux_sucessor(TARVBM *a, int elem);
TARVBM *maior(TARVBM *a);
TARVBM *menor(TARVBM *a);
int descobrir_t(TARVBM *no);
TARVBM *retira_pares(TARVBM *arv);
int ni(TARVBM *a);
int nf(TARVBM *a);

