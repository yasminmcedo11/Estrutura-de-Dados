#include <stdio.h>
#include <stdlib.h>

typedef struct arvbinbusca{
  int info;
  struct arvbinbusca *esq, *dir;
}TABB;

typedef struct lse{
  int info;
  struct lse *prox;
}TLSE;

// Biblioteca de funções disponibilizadas para resolver as questões
TABB *TABB_inicializa(void);
TABB *TABB_cria(int raiz, TABB *esq, TABB *dir);
void TABB_imp_pre(TABB *a);
void TABB_imp_pos(TABB *a);
void TABB_imp_sim(TABB *a);
void TABB_imp_ident(TABB *a);
void TABB_libera(TABB *a);
TABB *TABB_busca(TABB *a, int elem);
TABB *TABB_insere(TABB *a, int elem);
TABB *TABB_retira(TABB *a, int info);

// Biblioteca de Listas Encadeadas
TLSE* TLSE_inicializa(void);
TLSE* TLSE_insere_ini(TLSE *l, int elem);
TLSE* TLSE_insere_fim(TLSE *l, int x);
void TLSE_imprime(TLSE *l);
TLSE* TLSE_retira(TLSE *l, int elem);
TLSE* TLSE_busca(TLSE *l, int elem);
void TLSE_libera(TLSE *l);

// Lista 02 - Árvore Binária de Busca
TABB* maior(TABB *a);
TABB* menor(TABB *a);
TABB* retira_impares(TABB* a);
int contar_menores(TABB*a, int n);
void percorre_arvore(TABB *a, int n, int *vet, int *i);
int* mN(TABB*a, int N, int *qtd);
int TABB_nivel(TABB *a, int valor, int nivelAtual);