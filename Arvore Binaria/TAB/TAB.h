#include <stdio.h>
#include <stdlib.h>

typedef struct arvbin{
  int info, cor;
  struct arvbin *esq, *dir;
}TAB;

// Biblioteca de funções fornecidas para resolver as questões
TAB *TAB_inicializa(void);
TAB *TAB_cria(int raiz, TAB *esq, TAB *dir);
void TAB_imp_pre(TAB *a);
void TAB_imp_pos(TAB *a);
void TAB_imp_sim(TAB *a);
void TAB_imp_ident(TAB *a);
void imp_aux_cor(TAB *a, int andar);
void TAB_imp_ident_cor(TAB *a);
void TAB_libera(TAB *a);
TAB *TAB_busca(TAB *a, int elem);
int TAB_altura(TAB *a);

// Lista 01 - Árvores Binárias
TAB* copia (TAB *a);
TAB* espelho (TAB *a);
TAB* maior_elemento(TAB *a);
TAB* menor_elemento(TAB *a);
int arvores_iguais (TAB* a1, TAB* a2);
TAB* retira(TAB* arv);
TAB* retira_pares (TAB* arv);
void colore (TAB* arv);
int ni(TAB *a);
int nf(TAB *a);
// Listas de Revisao para P1
int teste_arv(TAB* a);