#include "TG.c"

//Q5 - 3,0 PONTOS
// Checar se um grafo colorido é tripartido e ligado por k arestas

// Funções criadas para resolver a questão
int eh_tripartido(TG *g) {
 if (!g) return 0;
 TG *p = g;
 while(p) {
   if(p->prim_viz) {
     TVIZ *vizinhos = p->prim_viz;
     while(vizinhos) {
       TG *adjacente = TG_busca_no(g, vizinhos->id_viz);
       if(p->cor_no == adjacente->cor_no) return 0;
       vizinhos = vizinhos->prox_viz;
     }
   }
   p = p->prox_no;
 }
 return 1;
}

int conta_arestas(TG *g, int cor1, int cor2) {
 TG *p = g;
 int qtd = 0;
 while(p) {
   if (p->prim_viz) {
     TVIZ *vizinhos = p->prim_viz;
     while(vizinhos) {
       TG *adjacencias = TG_busca_no(g, vizinhos->id_viz);
       if(adjacencias->cor_no == cor2 && p->cor_no == cor1) qtd++;
       vizinhos = vizinhos->prox_viz;
     }
   }
   p = p->prox_no;
 }
 return qtd;
}

int tem_k_arestas(TG *g, int k) {
  int arestas1 = conta_arestas(g, 1, 2);
  int arestas2 = conta_arestas(g, 2, 3);
  int arestas3 = conta_arestas(g, 3, 1);
  if (arestas1 == arestas2 && arestas2 == arestas3 && arestas3 == k) return 1;
  return 0;
}

int tripartido_k_arestas (TG* g, int k){
  int tripartido = eh_tripartido(g);
  int k_arestas = tem_k_arestas(g, k);
  if(tripartido == 1 && k_arestas == 1) return 1;
  return 0;
}

// Main para teste
int main(void){
  TG *g = TG_inicializa();
  printf("Digite o no do grafo e sua cor (pare quando um numero menor ou igual a zero for fornecido para o no)...\n");
  int no1, no2, cor;
  while(1){
    scanf("%d", &no1);
    if(no1 <= 0) break;
    scanf("%d", &cor);
    g = TG_ins_no(g, no1, cor);    
  }
 
  printf("Digite as arestas (pare quando um dos nos nao pertencer ao grafo)...\n");
  while(1){
    scanf("%d%d", &no1, &no2);
    if(!TG_busca_no(g, no1) || !TG_busca_no(g, no2)) break;
    TG_ins_aresta(g, no1, no2);
  }
  TG_imprime(g);
   
  printf("Digite o valor de k... ");
  int k;
  scanf("%d", &k);
  printf("%d\n", tripartido_k_arestas (g, k));
  
  TG_libera(g);
  return 0;
}

