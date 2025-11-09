#include "TABB.c"
#include "TLSE.c"

// Q3 - 2,0 PONTOS 
// Imprimir uma árvore binária de busca em forma de zigzag

// Funções criadas para resolver a questão
TLSE* TLSE_insere_fim(TLSE *l, int x) {
    TLSE *novo = (TLSE*) malloc(sizeof(TLSE));
    novo->info = x;
    novo->prox = NULL;
    if (!l) return novo; 
    TLSE *p = l;
    while (p->prox) p = p->prox; 
    p->prox = novo;              
    return l;    
}

int TLSE_tamanho(TLSE *elementos) {
  TLSE *p = elementos;
  int qtd = 0;
  while(p){
    qtd++;
    p = p->prox;
  }
  return qtd;
}

void imp_zz(TABB* a){
  if(!a) return;

  TLSE *fila = TLSE_inicializa();
  fila = TLSE_insere_fim(fila, a->info);
  int nivel = 0;

  while(fila) {
    int atual = fila->info; 

    int n = TLSE_tamanho(fila);
    int *nivel_atual = malloc(n*sizeof(int));

    for (int i = 0; i < n; i++) {
      int atual = fila->info;
      fila = TLSE_retira(fila, atual);
      nivel_atual[i] = atual;

      TABB *no_atual = TABB_busca(atual, a);
      if (!no_atual) continue;
      if (no_atual->esq) {
        TABB *no_esq = no_atual->esq;
        fila = TLSE_insere_fim(fila, no_esq->info);
      }
      if (no_atual->dir) {
        TABB *no_dir = no_atual->dir;
        fila = TLSE_insere_fim(fila, no_dir->info);
      }
    }

    if (nivel % 2 == 0) { 
      for (int i = 0; i < n; i++) 
        printf("%d ", nivel_atual[i]);
    } else { 
      for (int i = n - 1; i >= 0; i--) 
        printf("%d ", nivel_atual[i]);
    }

    printf("\n");
    nivel++;
    free(nivel_atual);
  }
  TLSE_libera(fila);
}

// Main para teste
int main(void){
  int n, m;
  TABB *a = NULL;
  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_insere(n, a);
  }
  TABB_imprime(a);
  
  imp_zz(a);
  TABB_libera(a);
  return 0;
}
