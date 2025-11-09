#include <stdlib.h>
#include <stdio.h>

typedef struct viz {
	int id_viz;
	struct viz *prox_viz;
}TVIZ;

typedef struct grafo{
	int id_no;
	TVIZ *prim_viz;
	struct grafo *prox_no;
}TG;

typedef struct grafo_com_cor{
	int id_no, cor;
	TVIZ *prim_viz;
	struct grafo *prox_no;
}TG_cor;

typedef struct lse{
  int info;
  struct lse *prox;
}TLSE;

// Biblioteca de funções de grafos disponibilizadas para resolver as questões
TG* TG_inicializa();
void TG_imprime(TG *g);
void TG_libera(TG *g);
TG* TG_busca_no(TG* g, int x);
TVIZ* TG_busca_aresta(TG *g, int no1, int no2);
TG* TG_ins_no(TG *g, int x);
void TG_ins_aresta(TG *g, int no1, int no2);
void TG_retira_aresta(TG *g ,int no1, int no2);
TG* TG_retira_no(TG *g, int no);

// Biblioteca de Listas Encadeadas
TLSE* TLSE_inicializa(void);
TLSE* TLSE_insere_ini(TLSE *l, int elem);
TLSE* TLSE_insere_fim(TLSE *l, int x);
void TLSE_imprime(TLSE *l);
TLSE* TLSE_retira(TLSE *l, int elem);
TLSE* TLSE_busca(TLSE *l, int elem);
void TLSE_libera(TLSE *l);

// Lista 04 - Grafos
int nn(TG *g);
int na(TG *g);
int testek(TG *g, int k);
int ig(TG *g1, TG *g2);
TLSE* menor_caminho(TG *g, int origem, int destino);
int conectado(TG *g);
int conta_caminhos(TG *g, int origem, int destino, TLSE *visitados);
int eh_ciclico(TG *g);
