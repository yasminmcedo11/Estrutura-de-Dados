#include "TARVB.h"

int main(int argc, char *argv[]){
  TARVB *arvore = TARVB_Inicializa();
  //TARVB *arvore2 = TARVB_Inicializa();
  int t, s;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0, from, to;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){
      scanf("%d", &from);
      arvore = TARVB_Retira(arvore, from, t);
      TARVB_Imprime2(arvore);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime2(arvore);
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime2(arvore);
    }
    else arvore = TARVB_Insere(arvore, num, t);
    printf("\n\n");
  }

  //printf("Digite o grau minimo(arv2). Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  //scanf("%d", &t);
  //if(t < 2) t = 2;
  //int num2 = 0, from2, to2;
  //while(num2 != -1){
  //  printf("Digite um numero para adicionar. 0 para imprimir. -9 para remover e -1 para sair\n");
   // scanf("%d", &num2);
   // if(num2 == -9){
   //   scanf("%d", &from2);
   //   arvore2 = TARVB_Retira(arvore2, from2, t);
   //   TARVB_Imprime2(arvore2);
   // }
    //else if(num2 == -1){
    //  printf("\n");
    //  TARVB_Imprime2(arvore2);
   // }
   // else if(!num2){
   //   printf("\n");
    //  TARVB_Imprime2(arvore2);
   // }
   // else arvore2 = TARVB_Insere(arvore2, num2, t);
   // printf("\n\n");
 // }

  //int elem, sucessor;
  //printf("Digite o elemento que deseja descobrir o sucessor: \n");
  //scanf("%d", &elem);
  //sucessor = suc (arvore, elem);
  //printf("O sucessor de %d e: %d", elem, sucessor);
  //TARVB *max = maior(arvore);
  //printf("Maior elemento: %d\n", max->chave[max->nchaves-1]);
  //TARVB *min = menor(arvore);
  //printf("Menor elemento: %d\n", min->chave[0]);

  //int identica = igual(arvore, arvore2);
  //printf("Resultado = %d\n", identica);
  //arvore = retira_pares(arvore);
  //TARVB_Imprime2(arvore);
  //int qtd = ni(arvore);
  //int qtd2 = nf(arvore);
  //printf("Quantidade de nos internos: %d. Quantidade de nos folha: %d\n", qtd, qtd2);
  inverte(arvore);
  printf("Imprimindo invertida\n");
  TARVB_Imprime2(arvore);

  TARVB_Libera(arvore);
  //TARVB_Libera(arvore2);
  
  return 0;
}
