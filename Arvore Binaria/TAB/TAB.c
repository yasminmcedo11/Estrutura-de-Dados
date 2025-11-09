#include "TAB.h"

TAB *TAB_inicializa(void){
  return NULL;
}

TAB *TAB_cria(int raiz, TAB *esq, TAB *dir){
  TAB *novo = (TAB *) malloc(sizeof(TAB));
  novo->info = raiz;
  novo->esq = esq;
  novo->dir = dir;
  return novo;
}

TAB *TAB_busca(TAB *a, int elem){
  if((!a) || (a->info == elem)) return a;
  TAB *resp = TAB_busca(a->esq, elem);
  if(resp) return resp;
  return TAB_busca(a->dir, elem);
}

void TAB_imp_pre(TAB *a){
  if(a){
    printf("%d ", a->info);
    TAB_imp_pre(a->esq);
    TAB_imp_pre(a->dir);
  }
}

void TAB_imp_pos(TAB *a){
  if(a){
    TAB_imp_pos(a->esq);
    TAB_imp_pos(a->dir);
    printf("%d ", a->info);
  }
}

void TAB_imp_sim(TAB *a){
  if(a){
    TAB_imp_sim(a->esq);
    printf("%d ", a->info);
    TAB_imp_sim(a->dir);
  }
}

void imp_aux(TAB *a, int andar){
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

void TAB_imp_ident(TAB *a){
  imp_aux(a, 0);
}

void imp_aux_cor(TAB *a, int andar) {
  int j;
  if(a){
    imp_aux_cor(a->dir, andar + 1);
    for(j = 0; j <= andar; j++) printf("\t"); //printf("   ");
    printf("%d\n", a->cor);
    imp_aux_cor(a->esq, andar + 1);
  }
  else{
   for(j = 0; j <= andar; j++) printf("\t");
   printf("N\n");
  }
}

void TAB_imp_ident_cor(TAB *a) {
  imp_aux_cor(a, 0);
}

void TAB_libera(TAB *a){
  if(a){
    TAB_libera(a->esq);
    TAB_libera(a->dir);
    free(a);
  }
}

int maior(int x, int y){
  if(x >= y) return x;
  return y;
}

int TAB_altura(TAB *a){
  if(!a) return -1;
  return maior(TAB_altura(a->esq), TAB_altura(a->dir)) + 1;
}

TAB* copia (TAB *a) {
  if (!a) return NULL; //arvore nao existe

  TAB* novo = (TAB*) malloc (sizeof(TAB));
  novo->info = a->info;
  novo->esq = copia(a->esq);
  novo->dir = copia(a->dir);
  return novo;
}

TAB* espelho (TAB *a) {
  if (!a) return NULL; //arvore nao existe

  TAB *novo = (TAB*) malloc (sizeof(TAB));
  novo->info = a->info;
  novo->esq = espelho(a->dir);
  novo->dir = espelho(a->esq);
  return novo;
}

TAB* maior_elemento(TAB *a) {
  if (!a) return a;

  TAB *esq = maior_elemento(a->esq);
  TAB *dir = maior_elemento(a->dir);
  TAB *resp = a;

  if(esq && esq->info > a->info) resp = esq;
  if(dir && dir->info > a->info) resp = dir;
  
  return resp;
}

TAB* menor_elemento(TAB *a) {
  if (!a) return a;

  TAB *esq = menor_elemento(a->esq);
  TAB *dir = menor_elemento(a->dir);
  TAB *resp = a;

  if(esq && esq->info < a->info) resp = esq;
  if(dir && dir->info < a->info) resp = dir;
  
  return resp;
}

int arvores_iguais (TAB* a1, TAB* a2) {
  int resultado = 1;
  if (!a1 && !a2) return 1;
  if (a1 && !a2 || !a1 && a2) return 0;
  if (a1->info != a2->info) return 0; 
  else {
    resultado = arvores_iguais(a1->esq, a2->esq);
    if (resultado != 0) resultado = arvores_iguais(a1->dir, a2->dir);
  }
  return resultado;
}

TAB* retira(TAB* arv) {
  if (!arv) return NULL;
  if(arv->esq == NULL && arv->dir == NULL) { // remocao de folha
    free(arv); 
    return NULL;
  }
  if(arv->esq == NULL && arv->dir != NULL) { // remocao com 1 filho na direita
    TAB *aux = arv->dir;
    free(arv);
    return aux; 
  }
  if (arv->dir == NULL && arv->esq != NULL) { // remocao com 1 filho na esquerda
    TAB *aux = arv->esq;
    free(arv);
    return aux;
  }
  if (arv->dir != NULL && arv->esq != NULL) { // remocao com 2 filhos (filho da esquerda vira pai)
    TAB *aux1 = arv->esq;
    TAB *aux2 = arv->dir;
    free(arv);
    // Encontrar o nó mais à direita da subárvore esquerda
    TAB *temp = aux1;
    while (temp->dir) temp = temp->dir;
    temp->dir = aux2;
    return aux1;
    }
}

TAB* retira_pares (TAB* arv) {
  if(!arv) return NULL;

  arv->esq = retira_pares(arv->esq);
  arv->dir = retira_pares(arv->dir);

  if(arv->info % 2 == 0) {
    arv = retira(arv);
  } 
  
  return arv;
}

void colore (TAB* arv) {
  if (!arv) return;

  if(arv->esq) colore(arv->esq);
  if(arv->dir) colore(arv->dir);

  int altura = TAB_altura(arv);
  if (altura % 2 == 0) arv->cor = 1;
  else arv->cor = 0;
}

int ni(TAB *a) {
  if(!a) return 0;
  int contador = 0;

  if(a->esq) contador += ni(a->esq);
  if(a->dir) contador += ni(a->dir);

  if(!(a->esq == NULL && a->dir == NULL)) {
    contador++;
  }  
  return contador;
}

int nf(TAB *a) {
  if(!a) return 1;
  int contador = 0;

  if(a->esq) contador += nf(a->esq);
  if(a->dir) contador += nf(a->dir);

  if(a->esq == NULL && a->dir == NULL) {
    contador++;
  }  
  return contador;
}


