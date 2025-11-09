#include "TG.h"

TG* TG_inicializa(){
  return NULL;
}

TLSE* TLSE_inicializa(void){
  return NULL;
}

TLSE* TLSE_insere_ini(TLSE *l, int elem){
  TLSE *novo = (TLSE *) malloc(sizeof(TLSE));
  novo->prox = l;
  novo->info = elem;
  return novo;
}

TLSE* TLSE_insere_fim(TLSE *l, int x) {
    if (!l) return TLSE_insere_ini(l, x);
    TLSE *p = l;
    while(p->prox) {
        p = p->prox;
    }
    p->prox = TLSE_insere_ini(NULL, x);
    return l;
}

void TLSE_imprime(TLSE *l){
  TLSE *p = l;
  while(p){
    printf("%d ", p->info);
    p = p->prox;
  } 
}

TLSE* TLSE_retira(TLSE *l, int elem){
  TLSE *p = l, *ant = NULL;
  while((p) && (p->info != elem)){
    ant = p;
    p = p->prox;
  }
  if(!p) return l;
  if(!ant) l = l->prox;
  else ant->prox = p->prox;
  free(p);
  return l;
}

TLSE* TLSE_busca(TLSE *l, int elem){
  TLSE *p = l;
  while((p) && (p->info != elem)) p = p->prox; 
  return p;
}

void TLSE_libera(TLSE *l){
  TLSE *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  } 
}


void TG_imprime(TG *g){
  while(g){
    printf("Vizinhos do No %d:\n", g->id_no);
    TVIZ *v = g->prim_viz;
    while(v){
      printf("%d ", v->id_viz);
      v = v->prox_viz;
    }
    printf("\n");
    g = g->prox_no;
  }
}

void TG_imp_rec(TG *g){
  if(g){
    printf("%d:\n", g->id_no);
    TVIZ *v = g->prim_viz;
    while(v){
      printf("%d ", v->id_viz);
      v = v->prox_viz;
    }
    TG_imp_rec(g->prox_no);
  }
}

void TG_libera_viz(TVIZ *v){
  while(v){
    TVIZ *temp = v;
    v = v->prox_viz;
    free(temp);
  }
}

void TG_libera_viz_rec(TVIZ *v){
  if(!v) return;
  TG_libera_viz_rec(v->prox_viz);
  free(v);
}

void TG_libera(TG *g){
  while(g){
    TG_libera_viz(g->prim_viz);
    TG *temp = g;
    g = g->prox_no;
    free(temp);
  }
}

void TG_libera_rec(TG *g){
  if(g){
    TG_libera_viz(g->prim_viz);
    TG_libera_rec(g ->prox_no);
    free(g);
  }
}

TG* TG_busca_no(TG* g, int x){
  if((!g) || (g->id_no == x)) return g;
  return(TG_busca_no(g->prox_no, x));
}

TVIZ* TG_busca_aresta(TG *g, int no1, int no2){
  TG *p1 = TG_busca_no(g,no1), *p2 = TG_busca_no(g,no2);
  if((!p1) || (!p2)) return NULL;
  TVIZ *resp = p1->prim_viz;
  while((resp) && (resp->id_viz != no2)) resp = resp->prox_viz;
  return resp;
}

TG* TG_ins_no(TG *g, int x){
  TG *p = TG_busca_no(g, x);
  if(!p){
    p = (TG*) malloc(sizeof(TG));
    p->id_no = x;
    p->prox_no = g;
    p->prim_viz = NULL;
    g = p;
  }
  return g;
}

void TG_ins_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1);
  TVIZ *nova = (TVIZ *) malloc(sizeof(TVIZ));
  nova->id_viz = no2;
  nova->prox_viz = p->prim_viz;
  p->prim_viz = nova;
}

void TG_ins_aresta(TG *g, int no1, int no2){
  TVIZ *v = TG_busca_aresta(g, no1, no2);
  if(v) return;
  TG_ins_um_sentido(g, no1, no2);
  TG_ins_um_sentido(g, no2, no1);
}

void TG_retira_um_sentido(TG *g, int no1, int no2){
  TG *p = TG_busca_no(g, no1);
  if(!p) return;
  TVIZ *ant = NULL, *atual = p->prim_viz;
  while((atual)&&(atual->id_viz != no2)){
    ant = atual;
    atual = atual->prox_viz;
  }
  if(!ant) p->prim_viz = atual->prox_viz;
  else ant->prox_viz = atual->prox_viz;
  free(atual);
}

void TG_retira_aresta(TG *g ,int no1, int no2){
  TVIZ* v = TG_busca_aresta(g,no1,no2);
  if(!v) return;
  TG_retira_um_sentido(g,no1,no2);
  TG_retira_um_sentido(g,no2,no1);
}

TG* TG_retira_no(TG *g, int no){
  TG *p = g, *ant = NULL;
  while((p)&& (p->id_no != no)){
    ant = p;
    p = p->prox_no;
  }
  if(!p) return g;
  while(p->prim_viz) TG_retira_aresta(g, no, p->prim_viz->id_viz);
  if(!ant) g = g->prox_no;
  else ant->prox_no = p->prox_no;
  free(p);
  return g;
}

int nn(TG *g) {
  if(!g) return 0;
  TG *p = g;
  int qtd = 0;
  while(p) {
    p = p->prox_no;
    qtd++;
  }
  return qtd;
}

int na(TG *g) {
  if(!g) return 0;
  TG *p = g;
  int qtd_nos = nn(g), qtd_arestas = 0, soma, indice = 0;
  int *vet_visitados = (int*) malloc(qtd_nos*sizeof(int));
  for (int i = 0; i < qtd_nos; i++) {
    vet_visitados[i] = 0;
  }

  while(p) {
    if(p->prim_viz) {
      TVIZ *atual = p->prim_viz;
      while(atual) {
        soma = 0;
        for(int i = 0; i < qtd_nos; i++) {
          if(atual->id_viz == vet_visitados[i]) soma = 1;
        }
        if (soma == 0) qtd_arestas++;
        atual = atual->prox_viz;
      }
    }
    vet_visitados[indice] = p->id_no;
    indice++;
    p = p->prox_no;
  }

  return qtd_arestas;
}

int testek(TG *g, int k) {
  if(!g) return 0;
  TG *p = g;
  int qtd, qtd_nova, no = 0;

  while(p) {
    qtd = 0;
    if(p->prim_viz) {
      TVIZ *atual = p->prim_viz;
      while(atual) {
        qtd++;
        atual = atual->prox_viz;
      }
    }
    if (qtd != qtd_nova && no != 0) return 0;
    qtd_nova = qtd;
    no++;
    p = p->prox_no;
  }

  return 1;
}

int aux_ig(TG *g1, TG *g2) {
  if(!g1 || !g2) return 0;
  TG *p1 = g1, *p2 = g2;

  while(p1){
    p2 = TG_busca_no(g2, p2->id_no);
    if(!p2) return 0;
    if(p1->prim_viz) {
      TVIZ *atual1 = p1->prim_viz, *atual2;
      while(atual1) {
        atual2 = TG_busca_aresta(g2, p1->id_no, atual1->id_viz);
        if(!atual2) return 0;
        atual1 = atual1->prox_viz;
      }
    } else if (p2->prim_viz) return 0;
    // ambos nao possuem o primeiro vizinho -> so continua
    p1 = p1->prox_no;
  }

  return 1;
}

int ig(TG *g1, TG *g2) {
  int resultado1, resultado2;
  resultado1 = aux_ig(g1, g2);
  resultado2 = aux_ig(g2, g1);
  if(resultado1 == 1 && resultado2 == 1) return 1;
  return 0;
}

// BFS para encontrar menor caminho
TLSE* menor_caminho(TG *g, int origem, int destino) {
  if (!g) return NULL;

  int max = 100; // tamanho máximo esperado
  int pai[max];

  TLSE *fila = TLSE_inicializa();
  fila = TLSE_insere_ini(fila, origem);
  TLSE *visitados = TLSE_inicializa();
  visitados = TLSE_insere_ini(visitados, origem);
  
  for (int i = 0; i < max; i++) { // inicializo o vetor de pais com -1 em todos os elementos
    pai[i] = -1;
  }
  
  // BFS
  while (fila) {
    int atual = fila->info; //puxo primeiro item da fila
    fila = TLSE_retira(fila, fila->info); // desempilho ele (retiro da fila)
    TG *no_atual = busca_no(g, atual);  // busco o no atual que vou comecar a busca

    // Se chegamos ao destino, para
    if (atual == destino) break;

    if(no_atual->prim_viz) {
      TVIZ *adjacencias = no_atual->prim_viz;   // lista de vizinhos do nó
      while(adjacencias) {
        if(!(TLSE_busca(visitados, adjacencias->id_viz))) {
          // descobri um novo nó -> guardo ele na minha lista de visitados
          visitados = TLSE_insere_fim(visitados, adjacencias->id_viz);
          // salvo o pai dele. Ex: pai[2] = 3. atual é o nó que procuramos os vizinhos 
          pai[adjacencias->id_viz] = atual; 
          // insere o novo nó no final da fila
          fila = TLSE_insere_fim(fila, adjacencias->id_viz);
        }
        adjacencias = adjacencias->prox_viz;
      }
    }
  }

  TLSE *visitou = TLSE_busca(visitados, destino);
  if(!visitou) return NULL;

  // inicializo minha lista do menor caminho
  TLSE *menor_caminho = TLSE_inicializa();
  int atual = destino;

  while (atual != -1) {
    menor_caminho = TLSE_insere_ini(menor_caminho, atual);
    atual = pai[atual];
  }

  return menor_caminho;
}

TLSE* aux_conectado(TG *g, int origem) {
  TLSE *fila = TLSE_inicializa();
  TLSE *visitados = TLSE_inicializa();

  visitados = TLSE_insere_ini(visitados, origem);
  fila = TLSE_insere_ini(visitados, origem);

  while(fila) {
    int atual = fila->info;
    fila = TLSE_retira(fila, atual);
    TG *no_atual = TG_busca_no(g, atual);

    if(!(no_atual->prim_viz)) return NULL;
    else {
      TVIZ *vizinhos = no_atual->prim_viz;
      while(vizinhos) {
        if(!(TLSE_busca(visitados, vizinhos->id_viz))) {
          visitados = TLSE_insere_ini(visitados, vizinhos->id_viz);
          fila = TLSE_insere_fim(fila, vizinhos->id_viz);
        }
        vizinhos = vizinhos->prox_viz;
      }
    }
  }

  return visitados;
}

int conectado(TG *g) {
  if (!g) return 0;
  TG *p = g;

  TLSE *lista_de_visitados = aux_conectado(g, g->id_no);
  if(!lista_de_visitados) return 0;

  while(p) {
    if(!TLSE_busca(lista_de_visitados, p->id_no)) return 0;
    p = p->prox_no;
  }

  return 1;
}


int conta_caminhos(TG *g, int origem, int destino, TLSE *visitados) {
  if(origem == destino) return 1;

  visitados = TLSE_insere_ini(visitados, g->id_no);
  TG *no_atual = TG_busca_no(g, g->id_no);

  int total = 0;

  if(no_atual->prim_viz) {
    TVIZ *vizinhos = no_atual->prim_viz;
    while(vizinhos) {
      if(!(TLSE_busca(visitados, vizinhos->id_viz))) 
            total += conta_caminhos(g, vizinhos->id_viz, destino, visitados);
      vizinhos = vizinhos->prox_viz;
    }
  }
  visitados = TLSE_retira(visitados, no_atual->id_no);

  return total;
}

int aux_ciclo(TG *g, int atual, int pai, TLSE *visitados) {
  visitados = TLSE_insere_ini(visitados, atual);
  TG *no_atual = TG_busca_no(g, atual);

  if(no_atual->prim_viz) {
    TVIZ *vizinhos = no_atual->prim_viz;
    while(vizinhos) {
      if(!(TLSE_busca(visitados, vizinhos->id_viz))) 
        return aux_ciclo(g, vizinhos->id_viz, atual, visitados);
      else if(vizinhos->id_viz != pai) return 1;
      vizinhos = vizinhos->prox_viz;
    }
  }
  visitados = TLSE_retira(visitados, no_atual->id_no);
  return 0;
}

int eh_ciclico(TG *g) {
  TG *p = g;
  TLSE *visitados = TLSE_inicializa();

  while(p) {
    if(!(TLSE_busca(visitados, p->id_no))) {
      if (aux_ciclo(g, p->id_no, -1, visitados)) return 1;
    }
    p = p->prox_no;
  }

  return 0;
}