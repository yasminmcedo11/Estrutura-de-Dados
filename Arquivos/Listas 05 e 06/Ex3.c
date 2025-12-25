#include <stdio.h>
#include <stdlib.h>

typedef struct numero{
    int numero;
    int qtd_repeticoes;
}NumRep;

typedef struct lse{
    NumRep numero;
    struct lse *prox;
}TLSE;

void resumo(char *Arq);
TLSE* TLSE_inicializa(void);
TLSE* TLSE_insere_ini(TLSE *l, NumRep elem);
TLSE* TLSE_busca(TLSE *l, int elem);
void TLSE_libera(TLSE *l);

int main() {
    char entrada[] = "valores_teste.txt";

    resumo(entrada);
    printf("Procedimento Realizado com sucesso");

    return 0;
}

TLSE* TLSE_inicializa(void){
  return NULL;
}

TLSE* TLSE_insere_ini(TLSE *l, NumRep elem){
  TLSE *novo = (TLSE *) malloc(sizeof(TLSE));
  novo->prox = l;
  novo->numero = elem;
  return novo;
}

TLSE* TLSE_busca(TLSE *l, int elem){
  TLSE *p = l;
  while((p) && (p->numero.numero != elem)) p = p->prox; 
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

void resumo(char *Arq) {
    FILE *arq = fopen(Arq, "r");
    if(!arq) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int numero;
    TLSE *lista_numeros = TLSE_inicializa();
    TLSE *p = lista_numeros;
    while(fscanf(arq, "%d", &numero) == 1) {
        p = TLSE_busca(lista_numeros, numero);
        if(!p) {
            NumRep numeroEst;
            numeroEst.numero = numero;
            numeroEst.qtd_repeticoes = 1;
            lista_numeros = TLSE_insere_ini(lista_numeros, numeroEst);
        } else {
            p->numero.qtd_repeticoes++;
        }
    }
    while(lista_numeros) {
        printf("Numero %d: %d repeticoes.\n", lista_numeros->numero.numero, lista_numeros->numero.qtd_repeticoes);
        lista_numeros = lista_numeros->prox;
    }
    TLSE_libera(lista_numeros);
    fclose(arq);
}