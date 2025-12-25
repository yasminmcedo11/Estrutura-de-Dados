#include "TARVB.h"

TARVB *TARVB_Cria(int t){
  TARVB* novo = (TARVB*)malloc(sizeof(TARVB)); // cria novo nó
  novo->nchaves = 0; // incializa o nó com 0 chaves (será alterado depois)
  novo->chave =(int*)malloc(sizeof(int)*((t*2)-1)); // incializa o vetor de chaves com o tam max)
  novo->folha = 1;  // define o nó como folha (pode ser alterado depois também)
  novo->filho = (TARVB**)malloc(sizeof(TARVB*)*t*2); // inicializa o vetor de ponteiros para filhos
  int i;
  for(i = 0; i < (t*2); i++) novo->filho[i] = NULL; // atribui inicialmente todos os filhos como NULL
  return novo; // retorna o nó criado
}


TARVB *TARVB_Libera(TARVB *a){
  if(a){
    if(!a->folha){
      int i;
      for(i = 0; i <= a->nchaves; i++) TARVB_Libera(a->filho[i]);
    }
    free(a->chave);
    free(a->filho);
    free(a);
    return NULL;
  }
}


void imp_rec(TARVB *a, int andar){
  if(a){
    int i,j;
    for(i=0; i<=a->nchaves-1; i++){
      imp_rec(a->filho[i],andar+1);
      for(j=0; j<=andar; j++) printf("\t");
      printf("%d\n", a->chave[i]);
    }
    imp_rec(a->filho[i],andar+1);
  }
}


void TARVB_Imprime(TARVB *a){
  imp_rec(a, 0);
}

void imp_rec2(TARVB *a, int andar){
  if(a){
    int i,j;
    imp_rec2(a->filho[a->nchaves],andar+1);
    for(i=a->nchaves-1; i>=0; i--){
      for(j=0; j<=andar; j++) printf("\t");
      printf("%d\n", a->chave[i]);
      imp_rec2(a->filho[i],andar+1);
    }
  }
}


void TARVB_Imprime2(TARVB *a){
  imp_rec2(a, 0);
}

TARVB *TARVB_Busca(TARVB* x, int ch){
  if(!x) return NULL; // se o nó não existe retorna NULL
  int i = 0;
  while(i < x->nchaves && ch > x->chave[i]) i++; // controla o valor da chave procurada
  // se a chave procurada for ch = 2 num nó com as chaves 3, 5, 7. i = 0.
  if(i < x->nchaves && ch == x->chave[i]) return x; // achou a chave retorna o nó onde ela está
  if(x->folha) return NULL; // se não achou a chave, mas o nó de bsuca é filho retorna NULL
  // para essa caso o nó não existe na árvore, já que não da pra descer pra continuar a busca
  return TARVB_Busca(x->filho[i], ch); // caso o nó não seja folha, continua a busca no filho correto.
  // pro caso do exemplo acima. busca da chave ch = 2, i = 0. então ele desce no filho[0]
  // filho da esquerda do 3 (faz sentido)
}


TARVB *TARVB_Inicializa(){
  return NULL;
}


TARVB *Divisao(TARVB *x, int i, TARVB* y, int t){
  // minha raiz vai ser dividida em 3: (inicialmente minha raiz era o nó y)
  // o nó x passa a ser o pai de y e z (y sendo filho da esquerda e z filho da direita)
  // x vai receber a mediana do nó raiz y inicial. z recebe os valores pós mediana
  // ex: chaves c0, c1, c2, c3, c4 (para t=3)
  // c2 = mediana => sobe para x. c3 e c4 vão para z. fica x:{c2}, y:{c0, c1}, z:{c3, c4}
  TARVB *z=TARVB_Cria(t);
  z->nchaves= t - 1; //cria o novo nó z com o número mínimo de chaves t-1 (para t=3, 2 chaves)
  z->folha = y->folha; // como ambos y e z estão no mesmo nível, se y é folha z também.
  int j;
  for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t]; // copiando as chaves c3 e c4 de y para z
  if(!y->folha){ // se y não for folha e sim nó intermediário, precisa repassar os ponteiros pros filhos
    for(j=0;j<t;j++){
      z->filho[j] = y->filho[j+t];  // repassando os filhos corretamente
      y->filho[j+t] = NULL; // 
    }
  }
  y->nchaves = t-1; // atualizando valor de chaves de y. Deixa de ter 5 para ter 2 igual a z
  for(j=x->nchaves; j>=i; j--) x->filho[j+1]=x->filho[j];
  x->filho[i] = z; // filho[1] recebe o novo nó z
  for(j=x->nchaves; j>=i; j--) x->chave[j] = x->chave[j-1];
  x->chave[i-1] = y->chave[t-1]; // a mediana do nó cheio sobre pra pai(raiz). c2 vai para o nó x (pai)
  x->nchaves++; //atualizo número de chaves do novo nó pai x
  return x; // retorno o novo nó pai x
}


TARVB *Insere_Nao_Completo(TARVB *x, int k, int t){
  // Como a inserção é feita de forma ordenada, ele percorre o vetor de chaves do final para o inicio
  int i = x->nchaves-1; // aqui ele puxa a ultima chave do vetor de chaves pra iniciar a busca
  if(x->folha){ // se o nó é folha
    while((i>=0) && (k<x->chave[i])){ // começa do ultimo elemento e compara pra ver o valor k é menor
      x->chave[i+1] = x->chave[i]; // se for menor => desloca o ultimo elemento pra frente
      i--; // atualiza valor de i
      // Ex: inserir chave 15 no nó [5, 12, 20]
      // i = 2 (posicao do ultimo elemento [20]) => começa o while chave[2] = 20
      // Como 15 < 20 e i > 0 => entra no while e a chave 20 passa pra posicao 3 e decrementa valor de i
      // i = 1 (posicao de 1 [12]) => 15 > 20, logo ele sai do while
      // o vetor fica dessa forma => [5, 12, 20, 20] com i = 1
    }
    x->chave[i+1] = k; // chave[2] = k (12) => chaves = [5, 12, 15, 20]
    x->nchaves++; // atualiza o numero de chaves
    return x;
  } // se o nó é interno
  while((i>=0) && (k<x->chave[i])) i--; // buscar o filho correto pra descer a busca
  i++;
  if(x->filho[i]->nchaves == ((2*t)-1)){ // se nó filho estiver cheio => chamar a funcao de divisao
    x = Divisao(x, (i+1), x->filho[i], t);
    if(k>x->chave[i]) i++; // atualizar k com base nos novos nós (k pode estar no filho da esq ou dir)
  }
  x->filho[i] = Insere_Nao_Completo(x->filho[i], k, t); // chama recursivamente pros filhos
  return x;
}


TARVB *TARVB_Insere(TARVB *T, int k, int t){
  if(TARVB_Busca(T,k)) return T; // se o nó já existe retorna ele pra evitar duplicatas
  if(!T){ // se a árvore estiver vazia, cria o nó como raiz (só vai ter uma chave associada)
    T=TARVB_Cria(t);
    T->chave[0] = k;
    T->nchaves=1;
    return T; // retorna o nó novo inserido
  }
  if(T->nchaves == (2*t)-1){ // caso a raiz esteja cheia, será preciso fazer a divisao antes de inserir
    TARVB *S = TARVB_Cria(t); // cria o novo nó que será o novo pai da raiz
    S->nchaves=0;
    S->folha = 0; // nó sera raiz
    S->filho[0] = T; // T passa a ser filho da esquerda desse novo nó
    S = Divisao(S,1,T,t); // algoritmo de divisão para dividir corretamente a raiz em seus filhos
    S = Insere_Nao_Completo(S,k,t);
    return S;
  }
  T = Insere_Nao_Completo(T,k,t);
  return T;
}


TARVB *TARVB_Libera_Remocao(TARVB *a){
  free(a->chave);
  free(a->filho);
  free(a);
  return NULL;
}


TARVB* remover(TARVB* arv, int ch, int t){
  if(!arv) return arv;
  int i;
  printf("Removendo %d...\n", ch);
  for(i = 0; i<arv->nchaves && arv->chave[i] < ch; i++);
  if(i < arv->nchaves && ch == arv->chave[i]){ //CASOS 1, 2A, 2B e 2C
    if(arv->folha){ //CASO 1
      printf("\nCASO 1\n");
      int j;
      for(j=i; j<arv->nchaves-1;j++) arv->chave[j] = arv->chave[j+1];
      arv->nchaves--;
      if(!arv->nchaves){ //ultima revisao: 04/2020
        TARVB_Libera(arv);
        arv = NULL;
      }
      return arv;      
    }
    if(!arv->folha && arv->filho[i]->nchaves >= t){ //CASO 2A
      printf("\nCASO 2A\n");
      TARVB *y = arv->filho[i];  //Encontrar o predecessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[y->nchaves];
      int temp = y->chave[y->nchaves-1];
      arv->filho[i] = remover(arv->filho[i], temp, t); 
      //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves >= t){ //CASO 2B
      printf("\nCASO 2B\n");
      TARVB *y = arv->filho[i+1];  //Encontrar o sucessor k' de k na árvore com raiz em y
      while(!y->folha) y = y->filho[0];
      int temp = y->chave[0];
      y = remover(arv->filho[i+1], temp, t); //Eliminar recursivamente K e substitua K por K' em x
      arv->chave[i] = temp;
      return arv;
    }
    if(!arv->folha && arv->filho[i+1]->nchaves == t-1 && arv->filho[i]->nchaves == t-1){ //CASO 2C
      printf("\nCASO 2C\n");
      TARVB *y = arv->filho[i];
      TARVB *z = arv->filho[i+1];
      y->chave[y->nchaves] = ch;          //colocar ch ao final de filho[i]
      int j;
      for(j=0; j<t-1; j++)                //juntar chave[i+1] com chave[i]
        y->chave[t+j] = z->chave[j];
      for(j=0; j<t; j++){                 //juntar filho[i+1] com filho[i]
        y->filho[t+j] = z->filho[j];
        z->filho[j] = NULL; //ultima revisao: 04/2020
      }
      y->nchaves = 2*t-1;
      for(j=i; j < arv->nchaves-1; j++)   //remover ch de arv
        arv->chave[j] = arv->chave[j+1];
      for(j=i+1; j < arv->nchaves; j++)  
        arv->filho[j] = arv->filho[j+1]; //remover ponteiro para filho[i+1]
      arv->filho[j] = NULL;
      TARVB_Libera_Remocao(z);
      arv->nchaves--;
      if(!arv->nchaves){ //ultima revisao: 04/2020
        TARVB *temp = arv;
        arv = arv->filho[0];
        temp->filho[0] = NULL;
        TARVB_Libera_Remocao(temp);
        arv = remover(arv, ch, t);
      }
      else arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;   
    }   
  }

  TARVB *y = arv->filho[i], *z = NULL;
  if (y->nchaves == t-1){ //CASOS 3A e 3B
    if((i < arv->nchaves) && (arv->filho[i+1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i menor que nchaves\n");
      z = arv->filho[i+1];
      y->chave[t-1] = arv->chave[i];   //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i] = z->chave[0];     //dar a arv uma chave de z
      int j;
      for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        z->chave[j] = z->chave[j+1];
      y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
      for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        z->filho[j] = z->filho[j+1];
      z->nchaves--;
      arv->filho[i] = remover(arv->filho[i], ch, t);
      return arv;
    }
    if((i > 0) && (!z) && (arv->filho[i-1]->nchaves >=t)){ //CASO 3A
      printf("\nCASO 3A: i igual a nchaves\n");
      z = arv->filho[i-1];
      int j;
      for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
        y->chave[j] = y->chave[j-1];
      for(j = y->nchaves+1; j>0; j--)             //encaixar lugar dos filhos da nova chave
        y->filho[j] = y->filho[j-1];
      y->chave[0] = arv->chave[i-1];              //dar a y a chave i da arv
      y->nchaves++;
      arv->chave[i-1] = z->chave[z->nchaves-1];   //dar a arv uma chave de z
      y->filho[0] = z->filho[z->nchaves];         //enviar ponteiro de z para o novo elemento em y
      z->nchaves--;
      arv->filho[i] = remover(y, ch, t);
      return arv;
    }
    if(!z){ //CASO 3B
      if(i < arv->nchaves && arv->filho[i+1]->nchaves == t-1){
        printf("\nCASO 3B: i menor que nchaves\n");
        z = arv->filho[i+1];
        y->chave[t-1] = arv->chave[i];     //pegar chave [i] e coloca ao final de filho[i]
        y->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          y->chave[t+j] = z->chave[j];     //passar filho[i+1] para filho[i]
          y->nchaves++;
        }
        if(!y->folha){
          for(j=0; j<t; j++){
            y->filho[t+j] = z->filho[j];
            z->filho[j] = NULL; //ultima revisao: 04/2020
          }
        }
        TARVB_Libera(z);
        for(j=i; j < arv->nchaves-1; j++){ //limpar referências de i
          arv->chave[j] = arv->chave[j+1];
          arv->filho[j+1] = arv->filho[j+2];
        }
        arv->filho[arv->nchaves] = NULL;
        arv->nchaves--;
        if(!arv->nchaves){ //ultima revisao: 04/2020
          TARVB *temp = arv;
          arv = arv->filho[0];
          temp->filho[0] = NULL;
          TARVB_Libera(temp);
        }
        arv = remover(arv, ch, t);
        return arv;
      }
      if((i > 0) && (arv->filho[i-1]->nchaves == t-1)){ 
        printf("\nCASO 3B: i igual a nchaves\n");
        z = arv->filho[i-1];
        if(i == arv->nchaves)
          z->chave[t-1] = arv->chave[i-1]; //pegar chave[i] e poe ao final de filho[i-1]
        else
          z->chave[t-1] = arv->chave[i];   //pegar chave [i] e poe ao final de filho[i-1]
        z->nchaves++;
        int j;
        for(j=0; j < t-1; j++){
          z->chave[t+j] = y->chave[j];     //passar filho[i+1] para filho[i]
          z->nchaves++;
        }
        if(!z->folha){
          for(j=0; j<t; j++){
            z->filho[t+j] = y->filho[j];
            y->filho[j] = NULL; //ultima revisao: 04/2020
          }
        }
        TARVB_Libera(y);
        arv->filho[arv->nchaves] = NULL;
        arv->nchaves--;
        if(!arv->nchaves){ //ultima revisao: 04/2020
          TARVB *temp = arv;
          arv = arv->filho[0];
          temp->filho[0] = NULL;
          TARVB_Libera(temp);
        }
        else arv->filho[i-1] = z;
        arv = remover(arv, ch, t);
        return arv;
      }
    }
  }  
  arv->filho[i] = remover(arv->filho[i], ch, t);
  return arv;
}


TARVB* TARVB_Retira(TARVB* arv, int k, int t){
  if(!arv || !TARVB_Busca(arv, k)) return arv;
  return remover(arv, k, t);
}


int suc (TARVB *a, int elem) {
  if(!a || !(TARVB_Busca(a, elem))) return INT_MAX; 
  return aux_sucessor(a, elem);
}

int aux_sucessor(TARVB *a, int elem) {
  int i = 0;

  while(i < a->nchaves && elem > a->chave[i]) i++;

  if(i < a->nchaves && a->chave[i] == elem) {
    if(!a->folha) { // se não for folha, procura o menor elemento da arvore à direita
      // Menor elemento da árvore direita => elemento mais a esquerda da folha final
      TARVB *p = a->filho[i+1];
      while(!p->folha) p = p->filho[0];
      return p->chave[0];
    }
    // se for folha retorna o elemento que vem após no vetor de chaves da folha (se existir)
    // se o elemento após não existir na folha retornar int_max
    if(i+1 < a->nchaves) return a->chave[i+1]; 
    return INT_MAX;
  }

  if(a->folha) return INT_MAX; 
  int candidato = INT_MAX;
  if(i < a->nchaves) candidato = a->chave[i]; // guarda o primeiro candidato a sucessor
  int sub = aux_sucessor(a->filho[i], elem);

  if(sub < candidato) return sub;
  return candidato;
}

TARVB* maior(TARVB *a) {
  if (!a) return NULL;
  TARVB *p = a;
  while(!p->folha) p = p->filho[p->nchaves];
  return p;
}

TARVB* menor(TARVB *a) {
  if(!a) return NULL;
  TARVB *p = a;
  while(!p->folha) p = p->filho[0];
  return p;
}

int igual (TARVB* a1, TARVB* a2) {
  int res1, res2;
  res1 = aux_igual(a1, a2);
  res2 = aux_igual(a2, a1);
  if(res1 == 1 && res2 == 1) return 1;
  return 0;
}

int aux_igual(TARVB *a1, TARVB *a2) {
  if(!a1 && !a2) return 1;
  if((!a1 && a2) || (a1 && !a2)) return 0;
  if(a1->nchaves != a2->nchaves) return 0;

  for(int i = 0; i < a1->nchaves; i++) {
    if(!aux_igual(a1->filho[i], a2->filho[i])) return 0;
    if(a1->chave[i] != a2->chave[i]) return 0;
  }
  if(!aux_igual(a1->filho[a1->nchaves], a2->filho[a2->nchaves])) return 0;
  return 1;
}


int descobrir_t(TARVB *no) {
    if (!no) return 0;
    // quantidade de bytes alocados no vetor filho
    size_t bytes = _msize(no->filho);
    // número total de ponteiros TARVB* armazenados
    int total_filhos = bytes / sizeof(TARVB*);
    // total de filhos = 2 * t  →  t = total_filhos / 2
    int t = total_filhos / 2;
    return t;
}

TARVB* retira_pares(TARVB *arv) {
  if(!arv) return NULL;
  int t = descobrir_t(arv);

  for(int i = 0; i <= arv->nchaves; i++) 
    arv->filho[i] = retira_pares(arv->filho[i]);

  for(int i = arv->nchaves-1; i >= 0; i--) 
    if(arv->chave[i] % 2 == 0) arv = TARVB_Retira(arv, arv->chave[i], t);

  return arv;
}

int ni(TARVB *a) {
  if(!a) return 0;
  int qtd = 0;

  if(!a->folha) qtd = 1;

  for(int i = 0; i <= a->nchaves; i++) 
    qtd += ni(a->filho[i]);
  return qtd;
}

int nf(TARVB *a) {
  if(!a) return 0;
  int qtd = 0;

  if(a->folha) qtd = 1;
  
  for(int i = 0; i <= a->nchaves; i++) 
    qtd += nf(a->filho[i]);
  return qtd;
}

//void mN_rec(TARVBM *a, int N, TLSE **lista) {
//    if(!a) return;
    // Se for folha → percorre chaves diretamente
 //   if(a->folha) {
  //      for(int i = 0; i < a->nchaves; i++) {
   //         if(a->chave[i] < N)
     //           *lista = TLSE_insere_inicio(*lista, a->chave[i]);
    //        else
      //          return;  // pode parar, pois está ordenado
     //   }
     //   return;
   // }
    // Nó interno → in-order
   // for(int i = 0; i < a->nchaves; i++) {
        // 1. visita filho[i]
    //    mN_rec(a->filho[i], N, lista);
        // 2. visita chave[i]
    //    if(a->chave[i] < N)
     //       *lista = TLSE_insere_inicio(*lista, a->chave[i]);
     //   else
     //       return;  // PARADA antecipada
   // }
    // 3. visita último filho
   // mN_rec(a->filho[a->nchaves], N, lista);
//}

//TLSE* mN(TARVBM *a, int N) {
 //   TLSE *lista = NULL;
  //  mN_rec(a, N, &lista);
  //  return lista;
//}

void inverte(TARVB *a){
  if(!a) return;

  for(int i = 0; i < a->nchaves/2; i++) {
    int tmp = a->chave[i];
    a->chave[i] = a->chave[a->nchaves-1-i];
    a->chave[a->nchaves-1-i] = tmp;
  }

  for(int i = 0; i < (a->nchaves/2)+1; i++) {
    TARVB *tmp = a->filho[i];
    a->filho[i] = a->filho[a->nchaves-i];
    a->filho[a->nchaves-i] = tmp;
  }

  for(int i = 0; i <= a->nchaves; i++) {
    if(a->filho[i]) inverte(a->filho[i]);
  }

}