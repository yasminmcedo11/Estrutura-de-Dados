#include <string.h>
#include "TAB.c"
#include "TLSE.c"

// Q4 - 2,0 PONTOS
// Checar se duas árvores binárias possuem os mesmos elementos (sem contar repetição)
// Por ex: as árvores 2-1-2 e 1-2 são iguais pois possuem os mesmos elementos

// Funções criadas para resolver a questão
TLSE *elementos_A(TAB *a, TLSE *elementos) {
 if(!a) return elementos;
 elementos = TLSE_insere(elementos, a->info);
 if(a->esq) elementos = elementos_A(a->esq, elementos);
 if(a->dir) elementos = elementos_A(a->dir, elementos);
 return elementos;
}

int mesmos_elementos (TAB* a1, TAB* a2){
  TLSE *elementos_a1 = TLSE_inicializa();
  TLSE *elementos_a2 = TLSE_inicializa();

  elementos_a1 = elementos_A(a1, elementos_a1);
  elementos_a2 = elementos_A(a2, elementos_a2);
  TLSE *p1 = elementos_a1;
  TLSE *p2 = elementos_a2;
  if(elementos_a1 && !(elementos_a2) || !(elementos_a1) && elementos_a2) return 0;
  if (!(elementos_a1) && !(elementos_a2)) return 1;
  while(p1) {
    if (!(TLSE_busca(elementos_a2, p1->info))) return 0;
    p1 = p1->prox;
  }
  while(p2) {
    if(!(TLSE_busca(elementos_a1, p2->info))) return 0;
    p2 = p2->prox;
  }
  TLSE_libera(elementos_a1);
  TLSE_libera(elementos_a2);
  return 1;
}

// Main para teste
int main(void){
  int no, pai;
  printf("Digite a raiz da PRIMEIRA arvore... ");
  scanf("%d", &no);
  TAB *a1 = TAB_cria(no, NULL, NULL), *resp;
  char repete;
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a1, pai);
    if(!resp){
      TAB_libera(a1);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a1);
  printf("\n");
 
  printf("Digite a raiz da SEGUNDA arvore... ");
  scanf("%d", &no);
  TAB *a2 = TAB_cria(no, NULL, NULL);
  do{
    char lado[2];
    printf("Quer continuar inserindo nos na árvore (digite N ou n para parar)? ");
    scanf(" %c", &repete);
    if((repete == 'N') || (repete == 'n')) break;
    printf("Digite o pai (que deve existir), o filho a ser inserido e a posição E(ESQ) ou D(DIR)... ");
    scanf("%d%d%s", &pai, &no, lado);
    resp = TAB_busca(a2, pai);
    if(!resp){
      TAB_libera(a2);
      TAB_libera(a1);
      return 0;
    }
    if(strcmp(lado, "E") == 0) resp->esq = TAB_cria(no, NULL, NULL);
    else resp->dir = TAB_cria(no, NULL, NULL);
  }while(1);
  TAB_imp_ident(a2);
  printf("\n");
 
  printf("%d\n", mesmos_elementos (a1, a2));
  
  TAB_libera(a1);
  TAB_libera(a2);
  return 0;
}
