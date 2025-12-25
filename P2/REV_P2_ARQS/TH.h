#include <stdio.h>
#include <stdlib.h>

typedef struct num{
  int num, prox, qtde;
}TNUM;

int TH_hash(int mat, int tam);
void TH_inicializa(char *tabDados, char *tabHash, int tam);
TNUM* TH_busca(char *tabHash, char *dados, int tam, int num);
void TH_retira(char *tabHash, char *dados, int tam, int num);
void TH_insere(char *tabHash, char *dados, int tam, int num);
void TH_imprime (char *tabHash, char *dados, int tam);
