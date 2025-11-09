#include "TG.h"

int main(void){
  TG *g1 = TG_inicializa();
  TG *g2 = TG_inicializa();
  int n, m;
  int qtd_nos1, qtd_arestas1;
  int qtd_nos2, qtd_arestas2;
  int resultado;

  printf("=== CRIACAO DO GRAFO 1 ===\n");
  do {
    printf("Digite o no que deseja inserir (<=0 para parar): ");
    scanf("%d", &n);
    if(n <= 0) break;
    g1 = TG_ins_no(g1, n);
    TG_imprime(g1);
  } while(1);

  do {
    printf("Digite os 2 nos que vao se ligar (<=0 para parar): ");
    scanf("%d%d", &n, &m);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g1, n, m);
    TG_imprime(g1);
  } while(1);

  printf("\n=== CRIACAO DO GRAFO 2 ===\n");
  do {
    printf("Digite o no que deseja inserir (<=0 para parar): ");
    scanf("%d", &n);
    if(n <= 0) break;
    g2 = TG_ins_no(g2, n);
    TG_imprime(g2);
  } while(1);

  do {
    printf("Digite os 2 nos que vao se ligar (<=0 para parar): ");
    scanf("%d%d", &n, &m);
    if((n <= 0) || (m <= 0)) break;
    TG_ins_aresta(g2, n, m);
    TG_imprime(g2);
  } while(1);

  // --- Exibe informações dos dois grafos ---
  qtd_nos1 = nn(g1);
  qtd_arestas1 = na(g1);
  qtd_nos2 = nn(g2);
  qtd_arestas2 = na(g2);

  printf("\nGrafo 1: %d nos e %d arestas.\n", qtd_nos1, qtd_arestas1);
  printf("Grafo 2: %d nos e %d arestas.\n", qtd_nos2, qtd_arestas2);

  // --- Comparação ---
  resultado = ig(g1, g2); // sua função de comparação
  if(resultado == 1)
    printf("\n✅ Os grafos são iguais.\n");
  else if (resultado == 0)
    printf("\n❌ Os grafos são diferentes.\n");

  TG_libera(g1);
  TG_libera(g2);
  return 0;
}

