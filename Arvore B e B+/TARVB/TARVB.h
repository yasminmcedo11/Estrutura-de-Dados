#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct ArvB{
  int nchaves, folha, *chave;
  struct ArvB **filho;
}TARVB;

// Biblioteca de Funções para Árvore B
TARVB *TARVB_Inicializa();
TARVB *TARVB_Cria(int t);
TARVB *TARVB_Libera(TARVB *a);
TARVB *TARVB_Busca(TARVB* x, int ch);
TARVB *TARVB_Insere(TARVB *T, int k, int t);
TARVB* TARVB_Retira(TARVB* arv, int k, int t);
void TARVB_Imprime(TARVB *a);
void TARVB_Imprime2(TARVB *a);

// Funções desenvolvidas para resolução dos exercícios da lista
int suc (TARVB *a, int elem);
int aux_sucessor(TARVB *a, int elem);
TARVB* maior(TARVB *a);
TARVB* menor(TARVB *a);
int igual (TARVB* a1, TARVB* a2);
int aux_igual(TARVB *a1, TARVB *a2);
int descobrir_t(TARVB *no);
TARVB* retira_pares(TARVB *arv);
int ni(TARVB *a);
int nf(TARVB *a);
void inverte(TARVB *a);
