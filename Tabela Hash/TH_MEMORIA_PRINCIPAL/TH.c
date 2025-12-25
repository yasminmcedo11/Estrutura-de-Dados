#include <float.h>
#include "TH.h"

int TH_hash(int mat, int n){
  return mat % n;
}

void TH_inicializa(TH tab, int n){
  int i;
  for(i = 0; i < n; i++)tab[i] = NULL;
}

TA* TH_busca(TH tab, int n, int mat){
  int h = TH_hash(mat, n);
  TA *p = tab[h];
  while((p) && (p->mat < mat)) p = p->prox;
  if((p) && (p->mat == mat)) return p;
  return NULL;
}

TA* TH_aloca(int mat, float cr){
  TA *novo = (TA*) malloc (sizeof (TA));
  novo->mat = mat;
  novo->cr = cr;
  novo->prox = NULL;
  return novo;
}

void TH_insere(TH tab, int n, int mat, float cr){
  int h = TH_hash(mat, n); 
  TA *p = tab[h],*ant = NULL;
  while((p) && (p->mat < mat)){
    ant = p;
    p = p->prox;
  }
  if((p) && (p->mat == mat)){
    p->cr = cr;
    return;
  }
  TA *novo = TH_aloca(mat, cr);
  novo->prox = p;
  if(!ant)tab[h] = novo;
  else ant->prox = novo;
}

void TH_libera(TH tab, int n){
  int i;
  for(i = 0; i < n; i++)
    if(tab[i]){
      TA *p = tab[i], *q;
      while(p){
        q = p;
        p = p->prox;
        free(q);
      }
    }
}

float TH_retira(TH tab, int n, int mat){
  int h = TH_hash(mat, n);
  if(!tab[h]) return FLT_MIN;
  TA *p = tab[h],*ant = NULL;
  float cr = FLT_MIN;
  while((p) && (p->mat < mat)){
    ant = p;
    p = p->prox;
  }
  if((!p) || (p->mat != mat)) return cr;
  if(!ant) tab[h] = p->prox;
  else ant->prox = p->prox;
  cr = p->cr;
  free(p);
  return cr;
}

void TH_imprime(TH tab, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("%d: ", i);
    if(tab[i]){
      TA *p = tab[i];
      printf("\n");
      while(p){
        printf("\t%d\t%f\t%p\n", p->mat, p->cr, p->prox);
        p = p->prox;
      }
    }
    else printf("NULL\n");
  }
}

// ------------------------------------------------------------------------------------------- //
void TH_inicializa_inteiros(TH2 tab, int n){
  int i;
  for(i = 0; i < n; i++)tab[i] = NULL;
}

N_INT* TH_busca_inteiros(TH2 tab, int n, int mat) {
  int h = TH_hash(mat, n);
  N_INT *p = tab[h];
  while((p) && (p->numero < mat)) p = p->prox;
  if((p) && (p->numero == mat)) return p;
  return NULL;
}

N_INT* TH_aloca_inteiros(int mat){
  N_INT *novo = (N_INT*) malloc (sizeof (N_INT));
  novo->numero = mat;
  novo->prox = NULL;
  return novo;
}

void TH_insere_inteiros(TH2 tab, int n, int mat){
  int h = TH_hash(mat, n); 
  N_INT *p = tab[h],*ant = NULL;
  while((p) && (p->numero < mat)){
    ant = p;
    p = p->prox;
  }
  if((p) && (p->numero == mat)) return;
  
  N_INT *novo = TH_aloca_inteiros(mat);
  novo->prox = p;
  if(!ant)tab[h] = novo;
  else ant->prox = novo;
}

void TH_retira_inteiros(TH2 tab, int n, int mat){
  int h = TH_hash(mat, n);
  if(!tab[h]) return;
  N_INT *p = tab[h],*ant = NULL;
  while((p) && (p->numero < mat)){
    ant = p;
    p = p->prox;
  }
  if((!p) || (p->numero != mat)) return;
  if(!ant) tab[h] = p->prox;
  else ant->prox = p->prox;
  free(p);
}

void TH_libera_inteiros(TH2 tab, int n){
  int i;
  for(i = 0; i < n; i++)
    if(tab[i]){
      N_INT *p = tab[i], *q;
      while(p){
        q = p;
        p = p->prox;
        free(q);
      }
    }
}

void inter(int* vet1, int qtd_vet1, int* vet2, int qtd_vet2, int* vet_saida) {
  TH2 tab;
  int n = 7, pos = 0;
  TH_inicializa_inteiros(tab, n);

  for(int i = 0; i < qtd_vet1; i++) {
    TH_insere_inteiros(tab, n, vet1[i]);
  }
  for(int i = 0; i < qtd_vet2; i++) {
    if(TH_busca_inteiros(tab, n, vet2[i])) {
      vet_saida[pos] = vet2[i];
      pos++;
    }
  }
  TH_libera_inteiros(tab, n);
}

void dif_sim(int* vet1, int qtd_vet1, int* vet2, int qtd_vet2, int* vetSaida) {
  TH2 tab;
  int n = 7, pos = 0;
  TH_inicializa_inteiros(tab, n);

  for(int i = 0; i < qtd_vet1; i++) {
    TH_insere_inteiros(tab, n, vet1[i]);
  }
  for(int i = 0; i < qtd_vet2; i++) {
    if(!TH_busca_inteiros(tab, n, vet2[i])) {
      vetSaida[pos] = vet2[i];
      pos++;
    } else TH_retira_inteiros(tab, n, vet2[i]);
  }

  for(int i = 0; i < n; i++) {
    if(tab[i]) {
      N_INT *p = tab[i];
      while(p) {
        vetSaida[pos] = p->numero;
        pos++;
        p = p->prox;
      }
    }
  }
  TH_libera_inteiros(tab, n);
}

void uniao(int* vet1, int qtd_vet1, int* vet2, int qtd_vet2, int* vetSaida) {
  TH2 tab;
  int n = 7, pos = 0;
  TH_inicializa_inteiros(tab, n);

  for(int i = 0; i < qtd_vet1; i++) {
    TH_insere_inteiros(tab, n, vet1[i]);
    vetSaida[pos] = vet1[i];
    pos++;
  }
  for(int i = 0; i < qtd_vet2; i++) {
    if(!TH_busca_inteiros(tab, n, vet2[i])) {
      vetSaida[pos] = vet2[i];
      pos++;
    }
  }
  TH_libera_inteiros(tab, n);
}





