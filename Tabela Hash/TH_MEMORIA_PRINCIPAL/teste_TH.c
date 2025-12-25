#include "TH.h"

int main(void){
 // int n;
 // printf("Digite n (quantidade de matriculas)... ");
 // scanf("%d", &n);

 // if((n <= 1) || (n > TAM_VET)) return 0;

 // TH tab;
  //TH_inicializa(tab, n);

 // int i, mat;
 // float cr;
 // for(i = 0; i < n; i++){
 //  printf("Digite a matricula e o cr...\n");
 //   scanf("%d", &mat);
  //  scanf("%f", &cr);
 //   TH_insere(tab, n, mat, cr);
 // }
 // TH_imprime(tab, n);

 // char resp;
 // do{
 //   printf("Digite a matricula a ser removida... ");
 //   scanf("%d", &mat);
 //   cr = TH_retira(tab, n, mat);
 //   if(cr != -1) printf("%d\t%f saiu\n", mat, cr);
 //   printf("Quer continuar? ");
 //   scanf(" %c", &resp);
 // }while((resp != 'N') && (resp != 'n'));
 // TH_imprime(tab, n);

  /*
  do{
    printf("Digite a matricula a ser procurada... ");
    scanf("%d", &mat);
    TA *p = TH_busca(tab, n, mat);
    if(!p) printf("Elemento nao encontrado!\n");
    else printf("%d\t%f\n", p->mat, p->cr);
    printf("Quer continuar? ");
    scanf(" %c", &resp);
  }while((resp != 'N') && (resp != 'n'));
  TH_imprime(tab, n);
  */
  int vet1[] = {1, 2, 5, 6, 8, 10, 22, 34, 12, 9, 11};
  int vet2[] = {3, 4, 5, 10, 14, 32, 12, 1};
  int *vet_saida = (int*) malloc(sizeof(int) * 8);
  int *vet_saida2 = (int*) malloc(sizeof(int) * 15);
  int *vet_saida3 = (int*) malloc(sizeof(int) * 20);
  int qtd_vet1 = 11, qtd_vet2 = 8;
  
  inter(vet1, qtd_vet1, vet2, qtd_vet2, vet_saida);
  printf("Intersecao: ");
  for(int i = 0; i < 8; i++) {
    printf("%d ", vet_saida[i]);
  }
  printf("\n");

  dif_sim(vet1, qtd_vet1, vet2, qtd_vet2, vet_saida2);
  printf("Diferenca simetrica: ");
  for(int i = 0; i < 15; i++) {
    printf("%d ", vet_saida2[i]);
  }
  printf("\n");

  uniao(vet1, qtd_vet1, vet2, qtd_vet2, vet_saida3);
  printf("Uniao: ");
  for(int i = 0; i < 20; i++) {
    printf("%d ", vet_saida3[i]);
  }
  printf("\n");

  free(vet_saida);
  free(vet_saida2);
  free(vet_saida3);

 // TH_libera(tab, n);
  return 0;
}
