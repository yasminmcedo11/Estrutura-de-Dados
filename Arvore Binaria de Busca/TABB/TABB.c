#include "TABB.h"

TABB *TABB_inicializa(void){
  return NULL;
}

TLSE* TLSE_inicializa(void){
  return NULL;
}

TLSE* TLSE_insere_ini(TLSE *l, int elem){
  TLSE *novo = (TLSE *) malloc(sizeof(TLSE));
  novo->prox = l;
  novo->info = elem;
  return novo;
}

TLSE* TLSE_insere_fim(TLSE *l, int x) {
    if (!l) return TLSE_insere_ini(l, x);
    TLSE *p = l;
    while(p->prox) {
        p = p->prox;
    }
    p->prox = TLSE_insere_ini(NULL, x);
    return l;
}

void TLSE_imprime(TLSE *l){
  TLSE *p = l;
  while(p){
    printf("%d ", p->info);
    p = p->prox;
  } 
}

TLSE* TLSE_retira(TLSE *l, int elem){
  TLSE *p = l, *ant = NULL;
  while((p) && (p->info != elem)){
    ant = p;
    p = p->prox;
  }
  if(!p) return l;
  if(!ant) l = l->prox;
  else ant->prox = p->prox;
  free(p);
  return l;
}

TLSE* TLSE_busca(TLSE *l, int elem){
  TLSE *p = l;
  while((p) && (p->info != elem)) p = p->prox; 
  return p;
}

void TLSE_libera(TLSE *l){
  TLSE *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}

TABB *TABB_cria(int raiz, TABB *esq, TABB *dir){
  TABB *novo = (TABB *) malloc(sizeof(TABB));
  novo->info = raiz;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

void TABB_imp_pre(TABB *a){
  if(a){
    printf("%d ", a->info);
    TABB_imp_pre(a->esq);
    TABB_imp_pre(a->dir);
  }
}

void TABB_imp_pos(TABB *a){
  if(a){
    TABB_imp_pos(a->esq);
    TABB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TABB_imp_sim(TABB *a){
  if(a){
    TABB_imp_sim(a->esq);
    printf("%d ", a->info);
    TABB_imp_sim(a->dir);
  }
}

void imp_aux(TABB *a, int andar){
  int j;
  if(a){
    imp_aux(a->dir, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->info);
    imp_aux(a->esq, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TABB_imp_ident(TABB *a){
  imp_aux(a, 0);
}

void TABB_libera(TABB *a){
  if(a){
    TABB_libera(a->esq);
    TABB_libera(a->dir);
    free(a);
  }
}

TABB *TABB_busca(TABB *a, int elem){
  if((!a) || (a->info == elem)) return a;
  if(a->info > elem) return TABB_busca(a->esq, elem);
  return TABB_busca(a->dir, elem);
}

TABB *TABB_insere(TABB *a, int elem){
  if(!a) return TABB_cria(elem, NULL, NULL);
  if(a->info > elem) a->esq = TABB_insere(a->esq, elem);
  else if (a->info < elem) a->dir = TABB_insere(a->dir, elem);
  return a;
}

TABB *TABB_retira(TABB *a, int info){
  if(!a) return a;
  if(info < a->info) 
    a->esq = TABB_retira(a->esq, info);
  else if(info > a->info) 
    a->dir = TABB_retira(a->dir, info);
  else{ //info encontrada
    if((!a->esq) && (!a->dir)){ //CASO (1)
      free(a);
      a = NULL;
    }
    else if((!a->esq) || (!a->dir)){ //CASO (2)
      TABB *temp = a;
      if(!a->esq) a = a->dir;
      else a = a->esq;
      free(temp); 
    }
    else{ //CASO (3)
      TABB *filho = a->esq;
      while(filho->dir) filho = filho->dir;
      a->info = filho->info;
      filho->info = info;
      a->esq = TABB_retira(a->esq, info);
    }
  }
  return a; 
}

TABB* maior(TABB *a) {
  if(!a) return NULL;
  if (!(a->dir)) return a;
  return maior(a->dir);
}

TABB* menor(TABB *a) {
  if(!a) return NULL;
  if (!(a->esq)) return a;
  return menor(a->esq);
}

TABB* retira_impares(TABB* a) {
  if(!a) return NULL;
  if(a->esq) a->esq = retira_impares(a->esq);
  if(a->dir) a->dir = retira_impares(a->dir);
  if(a->info % 2 != 0) {
    a = TABB_retira(a, a->info);
  } 
  return a;
}

int contar_menores(TABB*a, int n) {
  if(!a) return 0;
  int qtd = 0;
  
  if(a->info <= n) {
    qtd++;
    qtd += contar_menores(a->esq, n);
    qtd += contar_menores(a->dir, n);
  } else qtd = contar_menores(a->esq, n);

  return qtd;
}

void percorre_arvore(TABB *a, int n, int *vet, int *i) {
  if(!a) return;
  if(a->info <= n) {
    vet[*i] = a->info;
    (*i)++;
    percorre_arvore(a->esq, n, vet, i);
    percorre_arvore(a->dir, n, vet, i);
  } else percorre_arvore(a->esq, n, vet, i);
}

int* mN(TABB*a, int N, int *qtd) {
  if(!a) return NULL;

  int *vet, indice = 0;
  *qtd = contar_menores(a, N);
  vet = (int*) malloc (*qtd*sizeof(int));
  percorre_arvore(a, N, vet, &indice);

  return vet;
}

int TABB_nivel(TABB *a, int valor, int nivelAtual) {
  if (!a) return -1;
  if (a->info == valor) return nivelAtual;
  int nivel_esq = TABB_nivel(a->esq, valor, nivelAtual+1);
  if (nivel_esq != -1) return nivel_esq;
  return TABB_nivel(a->dir, valor, nivelAtual+1);
}



