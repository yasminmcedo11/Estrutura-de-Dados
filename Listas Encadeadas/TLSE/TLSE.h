#include <stdio.h>
#include <stdlib.h>

typedef struct lse{
  int info;
  struct lse *prox;
}TLSE;

// Bibliotece de funções de lista encadeada disponibilizadas para resolver as questões
TLSE* TLSE_inicializa(void);
TLSE* TLSE_insere_ini(TLSE *l, int elem);
TLSE* TLSE_insere_fim(TLSE *l, int elem);
void TLSE_imprime(TLSE *l);
void TLSE_libera(TLSE *l);
TLSE* TLSE_retira(TLSE *l, int elem);
TLSE* TLSE_busca(TLSE *l, int elem);
void TLSE_imp_rec(TLSE *l);
void TLSE_imp_rec_rev(TLSE *l);
void TLSE_lib_rec(TLSE *l);
TLSE* TLSE_busca_rec(TLSE *l, int elem);
TLSE* TLSE_retira_rec(TLSE *l, int elem);

// Lista de Revisão - Listas Encadeadas
TLSE* inverte(TLSE *l);
TLSE* inverte_nova_lista (TLSE* l);
TLSE* desloca (TLSE* l, int n);
TLSE *copia (TLSE *l);
TLSE* rto (TLSE* l, int elem);
TLSE* i_p (TLSE *l);
void i_p_void (TLSE *l);
int igual(TLSE *l1, TLSE *l2);
TLSE* junta_listas (TLSE* l1, TLSE* l2);
int Contrario (TLSE *l1, TLSE *l2);
TLSE* ordena (TLSE* l);

