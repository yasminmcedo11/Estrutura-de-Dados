#include <stdio.h>
#include <stdlib.h>

// Biblioteca de Funções de Árvore Binária de Busca

typedef struct arvbinbusca{
    int info;
    struct arvbinbusca *esq, *dir;
}TABB;

TABB* TABB_cria(int x, TABB* e, TABB* d);
void TABB_imprime(TABB *t);
void TABB_libera(TABB* t);
TABB* TABB_busca(int e, TABB* t);
TABB* TABB_insere(int e, TABB* t);
TABB* TABB_retira(int e, TABB *t);




