#include "TLSE.h"

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

void TLSE_imp_rec(TLSE *l){
  if(l){
    printf("%d ", l->info);
    TLSE_imp_rec(l->prox);
  }
}

void TLSE_imp_rec_rev(TLSE *l){
  if(l){
    TLSE_imp_rec_rev(l->prox);
    printf("%d ", l->info);
  }
}

void TLSE_libera(TLSE *l){
  TLSE *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}

void TLSE_lib_rec(TLSE *l){
  if(l){
    TLSE_lib_rec(l->prox);
    printf("liberando o elemento %d...\n", l->info);
    free(l);
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

TLSE* TLSE_retira_rec(TLSE *l, int elem){
  if(!l) return l;
  if(l->info == elem){
    TLSE *p = l;
    l = l->prox;
    free(p);
  }
  else l->prox = TLSE_retira_rec(l->prox, elem);
  return l;
}

TLSE* TLSE_busca(TLSE *l, int elem){
  TLSE *p = l;
  while((p) && (p->info != elem)) p = p->prox; 
  return p;
}

TLSE* TLSE_busca_rec(TLSE *l, int elem){
  if((!l) || (l->info == elem)) return l;
  return TLSE_busca_rec(l->prox, elem);
}

TLSE* inverte(TLSE *l) {
  TLSE *p = l, *proximo = l, *ant = NULL;
  
  while (p != NULL) {
    proximo = p->prox;
    p->prox = ant;
    ant = p;
    p = proximo;
  }

  return ant;  
}

TLSE* inverte_nova_lista (TLSE* l) {
  TLSE *p = l, *ant = NULL, *nova_lista;
  nova_lista = TLSE_inicializa();

  while(p) {
    nova_lista = TLSE_insere_ini(nova_lista, p->info);
    p = p->prox;
  }
  return nova_lista;
}

TLSE* desloca (TLSE* l, int n) {
  TLSE* p = l, *primeiro = l, *ant = NULL;
  if (n % 2 == 0) {
    //se for par, o elemento que esta na primeira posicao passa para o ultimo
    while(p->prox) {
      p = p->prox;
    }
    p->prox = primeiro;
    l = primeiro->prox;
    primeiro->prox = NULL;
  } else {
    // se for impar, elemento que esta na ultima posicao passa pra primeira
    while(p->prox) {
      ant = p;
      p = p->prox;
    }
    l = p;
    p->prox = primeiro;
    ant->prox = NULL;
  }
  return l;
}

TLSE *copia (TLSE *l) {
  TLSE* p = l, *novo;
  novo = TLSE_inicializa();
  while(p) {
    novo = TLSE_insere_fim(novo, p->info);
    p = p->prox;
  } 
  return novo;
}

TLSE* rto (TLSE* l, int elem) {
  TLSE *p = l, *ant = NULL, *aux;
  while(p) {
    if (p->info == elem) {
      aux = p;
      if(ant) ant->prox = p->prox;
      else l = p->prox; 
      p = p->prox;
      free(aux);
    } else {
      ant = p;
      p = p->prox;
    }
  }
  return l;
}

TLSE* i_p (TLSE *l) {
  TLSE *p = l, *q = l, *r = l, *novo = TLSE_inicializa();
  int qtd = 0, *vet, indice = 0;
  while(p) {
    p = p->prox;
    qtd++;
  }
  vet = (int*) malloc (qtd*sizeof(int));
  while(q) {
    if (q->info % 2 != 0) {
      vet[indice] = q->info;
      indice++;
    }
    q = q->prox;
  }
  while(r) {
    if (r->info % 2 == 0) {
      vet[indice] = r->info;
      indice++;
    }
    r = r->prox;
  }
  for (int i = 0; i < qtd; i++) {
    novo = TLSE_insere_fim(novo, vet[i]);
  }
  free(vet);
  return novo;
}

void i_p_void (TLSE *l) {
  TLSE *p = l, *q = l, *r = l;
  int qtd = 0, *vet, indice = 0;
  while(p) {
    p = p->prox;
    qtd++;
  }
  vet = (int*) malloc (qtd*sizeof(int));
  while(q) {
    if (q->info % 2 != 0) {
      vet[indice] = q->info;
      indice++;
    }
    q = q->prox;
  }
  while(r) {
    if (r->info % 2 == 0) {
      vet[indice] = r->info;
      indice++;
    }
    r = r->prox;
  }
  indice = 0;
  for (TLSE *aux = l; aux != NULL; aux = aux->prox) {
    aux->info = vet[indice++];
  } 
  free(vet);
}

int igual(TLSE *l1, TLSE *l2) {
  if (!l1 && !l2) return 1;
  if (!l1 || !l2) return 0;
  if (l1->info != l2->info) return 0;
  return igual(l1->prox, l2->prox);
}

TLSE* junta_listas (TLSE* l1, TLSE* l2) {
  TLSE *p = l1;
  if (!l1) return l2;
  while(p->prox) {
    p = p->prox;
  }
  p->prox = l2;
  return l1;
}

int Contrario (TLSE *l1, TLSE *l2) {
  TLSE *p1 = l1, *p2 = l2, *p2_ = l2;
  int *vet, qtd = 0, indice = 0, resultado = 0;

  while(p2) {
    p2 = p2->prox;
    qtd++;
  }
  vet = (int*) malloc (qtd*(sizeof(int)));
  while(p2_) {
    vet[indice] = p2_->info;
    p2_ = p2_->prox;
    indice++;
  }
  indice--;
  while(p1) {
    if(p1->info == vet[indice]) {
      resultado = 1;
    } else {
      resultado = 0;
      break;
    }
    p1 = p1->prox;
    indice--;
  }
  free(vet);
  return resultado;
}

static int comp_int(const void *p1, const void *p2) {
  int *f1 = (int*)p1;
  int *f2 = (int*)p2;

  if (*f1 > *f2) return 1;
  else if (*f1 < *f2) return -1;
  else if (*f1 == *f2) return 0;
}

TLSE* ordena (TLSE* l) {
  TLSE *p = l, *p2 = l, *novo = TLSE_inicializa();
  int qtd = 0, *vet, indice = 0;

  while(p) {
    p = p->prox;
    qtd++;
  }
  vet = (int*) malloc (qtd*sizeof(int));
  while(p2) {
    vet[indice] = p2->info;
    p2 = p2->prox;
    indice++;
  }

  qsort(vet, qtd, sizeof(int), comp_int);
  for(int i = 0; i < qtd; i++) {
    novo = TLSE_insere_fim(novo, vet[i]);
  }
  free(vet);
  return novo;
  }

void ordena_sem_nova_lista (TLSE *l) {
  TLSE *p = l, *aux = l;
  
  while(p) {
    while(p->prox) {

    }
  }
}

void bubble_sort(TLSE *l) {
    if (!l) return;  // lista vazia, nada a fazer

    int trocou;
    TLSE *p, *ultimo = NULL;

    do {
        trocou = 0;
        p = l;

        while (p->prox != ultimo) { // percorre até o último elemento já ordenado
            if (p->info > p->prox->info) {
                // troca apenas os valores (não mexe nos ponteiros)
                int temp = p->info;
                p->info = p->prox->info;
                p->prox->info = temp;
                trocou = 1;
            }
            p = p->prox;
        }

        // após cada passada, o último já está no lugar certo
        ultimo = p;
    } while (trocou);
}


