#include "TABB.h"

int main(void){
  TABB *a = TABB_inicializa(); 
  int n, qtd, *vet;

  while(1){
    scanf("%d", &n);
    if(n < 0) break;
    a = TABB_insere(a, n);
  }
  TABB_imp_ident(a);

  //while(1){
  //  scanf("%d", &n);
  //  if(n < 0) break;
  //  a = TABB_retira(a, n);
  //  TABB_imp_ident(a);
  //}
  //TABB *ma = maior(a);
  //TABB *me = menor(a);
  //printf("Maior valor = %d\n", ma->info);
  //printf("Menor valor = %d\n", me->info);
//  a = retira_impares(a);
  //printf("\n");
  //TABB_imp_ident(a);
  //qtd = contar_menores(a, 12);
  //printf("Existem %d elementos menor(es) que 12.\n", qtd);
  //vet = mN(a, 12, &qtd);
  //for (int i = 0; i < qtd; i++) {
  //  printf("%d ", vet[i]);
  //}
  imp_zigzag(a);
  
  TABB_libera(a);
  //free(vet);
  return 0;
} 
