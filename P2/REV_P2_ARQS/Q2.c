#include "TARVB.c"

void inverte(TARVB *a){
  if(!a) return; // adicionado o caso base que eu tinha esquecido na prova

  // Mudança na forma de calcular os indices para fazer as trocas entre os elementos
  for(int i = 0; i < a->nchaves/2; i++) {
    int tmp = a->chave[i];
    a->chave[i] = a->chave[a->nchaves-1-i];
    a->chave[a->nchaves-1-i] = tmp;
  }

  // Mudança na forma de calcular os indices para fazer as trocas entre os elementos
  for(int i = 0; i < (a->nchaves+1)/2; i++) {
    TARVB *tmp = a->filho[i];
    a->filho[i] = a->filho[a->nchaves-i];
    a->filho[a->nchaves-i] = tmp;
  }

  for(int i = 0; i <= a->nchaves; i++) {
    // adicionando if para somente chamar a inverte para o filho se ele existir
    if(a->filho[i]) inverte(a->filho[i]); 
  }
}

int main(){
  TARVB *arvore = TARVB_Inicializa();
  int t;
  printf("Digite o grau minimo. Se o valor digitado for menor que 2, t sera considerado igual a 2...\n");
  scanf("%d", &t);
  if(t < 2) t = 2;
  int num = 0;
  while(num != -1){
    printf("Digite um numero para adicionar. 0 para imprimir. -9 para realizar a operacao e -1 para sair\n");
    scanf("%d", &num);
    if(num == -9){ // Opção para inverter a árvore
      //printf("invertendo...\n");
      inverte(arvore);
      TARVB_Imprime(arvore);
    }
    else if(num == -1){
      printf("\n");
      TARVB_Imprime(arvore);
      TARVB_Libera(arvore);
      return 0;
    }
    else if(!num){
      printf("\n");
      TARVB_Imprime(arvore);
    }
    else arvore = TARVB_Insere(arvore, num, t);
    printf("\n\n");
  }

}
