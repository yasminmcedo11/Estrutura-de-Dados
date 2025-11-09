#include <string.h>
#include "TAB.h"

TAB *maior_elem(TAB *a){
  if(!a) return a;
  TAB *esq = maior_elem(a->esq), *dir = maior_elem(a->dir), *resp = a;
  if((esq) && (resp->info < esq->info)) resp = esq;
  if((dir) && (resp->info < dir->info)) resp = dir;
  return resp;
}

int main(void){
  int no, pai, i, f, resultado;
  printf("Digite a raiz da arvore... ");
  scanf("%d", &no);
  TAB *a = TAB_cria(no, NULL, NULL), *resp;
  char repete;
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido na arvore e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a, pai);
    if(!resp){
      TAB_libera(a);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a);
  printf("\n");

  //TAB *b = menor_elemento(a);
  //printf("\nMenor elemento da arvore: %d", b->info);
  //TAB_imp_ident(b);
  //int teste = arvores_iguais(a, b);
  //printf("resultado = %d", teste);
  //a = retira_pares(a);
  //colore(a);
  //printf("\n");
  //i = ni(a);
  //f = nf(a);
  //printf("Numero de nos internos = %d\n", i);
  //printf("Numero de nos folhas = %d\n", f);
  //TAB_imp_ident(a);
  resultado = teste_arv(a);
  printf("Resultado = %d\n", resultado);

    
  TAB_libera(a);
  //TAB_libera(b);
  return 0;
}
