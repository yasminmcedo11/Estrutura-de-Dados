#include "TH_MS.h"

int TH_hash(int mat, int tam){
  return mat % tam;
}

void TH_inicializa(char *tabHash, char *dados, int n){
  FILE *fp = fopen(dados, "wb");
  if(!fp) exit(1);
  fclose(fp);
  fp = fopen(tabHash, "wb");
  if(!fp) exit(1);
  int i, elem = -1;
  for(i = 0; i < n; i++)fwrite(&elem, sizeof(int), 1, fp);
  fclose(fp);
}

TA* TH_aloca(int mat, float cr){
  TA *novo = (TA*)malloc(sizeof(TA));
  novo->mat = mat;
  novo->cr = cr;
  novo->prox = -1;
  novo->status = 1;
  return novo;
}

TA* TH_busca(char *tabHash, char *dados, int n, int mat){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp)exit(1);
  int pos, h = TH_hash(mat,n); // Calcula o indice do arquivo tabHash
  fseek(fp, h*sizeof(int), SEEK_SET); //fseek para posição correta do vetor de indices
  fread(&pos, sizeof(int), 1, fp); // guardando o valor lido
  fclose(fp);
  if(pos == -1)return NULL; // Se pos == 1 => não existe valor associado a essa posição ainda
  fp = fopen(dados,"rb"); // abre o arquivo de dados
  if(!fp) exit(1);
  fseek(fp, pos, SEEK_SET); // vai pra posição onde o dado tá guardado no arquivo de dados
  TA aux;
  fread(&aux, sizeof(TA), 1, fp); // lê o primeiro nó da lista 
  while(1){
    if((aux.mat == mat) && (aux.status)){ // verifica se encontrou o nó buscado
      TA *resp = TH_aloca(aux.mat, aux.cr); // se encontrou => aloca ele na memória principal
      resp->prox = aux.prox;
      fclose(fp);
      return resp;
    }
    if(aux.prox == -1){ // não encontrou => retorna NULL
      fclose(fp);
      return NULL;
    }
    fseek(fp, aux.prox, SEEK_SET); // p = p->prox
    fread(&aux, sizeof(TA), 1, fp); // lê novo valor de p
  }
}

float TH_retira(char *tabHash, char *arq, int n, int mat){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp) exit(1);
  int pos, h = TH_hash(mat,n);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1)return -1;
  float cr = -1;
  fp = fopen(arq,"rb+");
  if(!fp)exit(1);
  TA aux;
  while(1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TA), 1, fp);
    if((aux.mat == mat) && (aux.status)){
      cr = aux.cr;
      aux.status = 0; // atualiza o status para 0 => removido
      fseek(fp, pos, SEEK_SET); // volta o cursor pra posição pos
      fwrite(&aux, sizeof(TA), 1, fp); // sobrescreve valor novo
      fclose(fp);
      return cr;
    }
    if(aux.prox == -1){
      fclose(fp);
      return cr;
    }
    pos = aux.prox;
  }
}

void TH_insere(char *tabHash, char *arq, int n, int mat, float cr){
  FILE *fph = fopen(tabHash, "rb+");
  if(!fph) exit(1);
  int pos, h = TH_hash(mat, n);
  fseek(fph, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fph);
  int ant, prim_pos_livre;
  ant = prim_pos_livre = -1; // ant => guarda o endereço do nó anterior
  FILE *fp = fopen(arq,"rb+");
  if(!fp){
    fclose(fph);
    exit(1);
  }
  TA aux;
  while(pos != -1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TA), 1, fp);
    if(aux.mat == mat){ // elemento já existe => atualização
      aux.cr = cr;
      aux.status = 1;
      fseek(fp, pos, SEEK_SET); // sempre voltar o cursor!!
      fwrite(&aux, sizeof(TA), 1, fp);
      fclose(fp);
      fclose(fph);
      return;
    }
    if((!aux.status) && (prim_pos_livre == -1))prim_pos_livre=pos;
    // registro morto e não achamos nenhum buraco pra inserção => guarda o buraco
    ant = pos; // ant = p
    pos = aux.prox; // p = p->prox
  }
  if(prim_pos_livre == -1){ // Não achamos nenhum buraco pra inserção
    aux.mat = mat;
    aux.cr = cr;
    aux.prox = -1; // Como será o último da lista => p->prox aponta pra NULL
    aux.status = 1;
    fseek(fp, 0L, SEEK_END); // Vai pro final do arquivo
    pos = ftell(fp); // guarda o offset de onde será salvo
    fwrite(&aux, sizeof(TA), 1, fp); // grava o valor
    if(ant != -1){ // A lista já existia
      fseek(fp, ant, SEEK_SET); // Volta pra ant
      fread(&aux, sizeof(TA), 1, fp); // le o valor de ant
      aux.prox = pos; // ant->prox = pos (posicao do registro novo no arquivo de dados)
      fseek(fp, ant, SEEK_SET); // volta pra posição de ant
      fwrite(&aux, sizeof(TA), 1, fp); // grava o valor novo
    }
    else{ // Se a lista não existia (1° inserção daquele índice no hash)
      fseek(fph, h*sizeof(int), SEEK_SET); // vai no arquivo de indices (na posição onde h está)
      fwrite(&pos, sizeof(int), 1, fph); // grava o offset do registro no arquivo de dados
    }
    fclose(fp);
    fclose(fph);
    return;
  }
  // Achamos um buraco pra inserção
  fseek(fp, prim_pos_livre, SEEK_SET); // vai pra posição livre no arquivo de dados
  fread(&aux, sizeof(TA), 1, fp); // lê o registro que está ali
  // Atribui novos valores de cr, matricula e status
  aux.mat = mat;
  aux.cr = cr;
  aux.status = 1;
  fseek(fp, prim_pos_livre, SEEK_SET); // volta o cursor pra posição correta
  fwrite(&aux, sizeof(TA), 1, fp); // grava o valor lá
  fclose(fp);
  fclose(fph);
  return;
}

void TH_imprime (char *nome_hash, char *nome_dados, int m){
  FILE *fp = fopen(nome_hash, "rb");
  if(!fp) exit(1);
  int vet[m];
  fread(&vet, sizeof(int), m, fp);
  fclose(fp);

  fp = fopen(nome_dados, "rb");
  if(!fp) exit(1);
  int i, pos;
  for(i = 0; i < m; i++){
    int p = vet[i];
    if(p != -1) printf("%d:\n", i);
    TA x;
    while(p != -1){
      fseek(fp, p, SEEK_SET);
      pos = ftell (fp);
      fread(&x, sizeof(TA), 1, fp);
      printf("$%d: matricula: %d\tcr: %f\tstatus: %d\tprox_end: $%d\n", pos, x.mat, x.cr, x.status, x.prox);
      p = x.prox;
    }
  }
  fclose(fp);
}

// -------------------------------------------------------------------------------------- //
void TH_insere_inteiros(char *tabHash, char *arq, int n, int mat){
  FILE *fph = fopen(tabHash, "rb+");
  if(!fph) exit(1);
  int pos, h = TH_hash(mat, n);
  fseek(fph, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fph);
  int ant, prim_pos_livre;
  ant = prim_pos_livre = -1; // ant => guarda o endereço do nó anterior
  FILE *fp = fopen(arq,"rb+");
  if(!fp){
    fclose(fph);
    exit(1);
  }
  N_INT aux;
  while(pos != -1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(N_INT), 1, fp);
    if(aux.numero == mat){ // elemento já existe => atualização
      aux.status = 1;
      fseek(fp, pos, SEEK_SET); // sempre voltar o cursor!!
      fwrite(&aux, sizeof(N_INT), 1, fp);
      fclose(fp);
      fclose(fph);
      return;
    }
    if((!aux.status) && (prim_pos_livre == -1))prim_pos_livre=pos;
    // registro morto e não achamos nenhum buraco pra inserção => guarda o buraco
    ant = pos; // ant = p
    pos = aux.prox; // p = p->prox
  }
  if(prim_pos_livre == -1){ // Não achamos nenhum buraco pra inserção
    aux.numero = mat;
    aux.prox = -1; // Como será o último da lista => p->prox aponta pra NULL
    aux.status = 1;
    fseek(fp, 0L, SEEK_END); // Vai pro final do arquivo
    pos = ftell(fp); // guarda o offset de onde será salvo
    fwrite(&aux, sizeof(N_INT), 1, fp); // grava o valor
    if(ant != -1){ // A lista já existia
      fseek(fp, ant, SEEK_SET); // Volta pra ant
      fread(&aux, sizeof(N_INT), 1, fp); // le o valor de ant
      aux.prox = pos; // ant->prox = pos (posicao do registro novo no arquivo de dados)
      fseek(fp, ant, SEEK_SET); // volta pra posição de ant
      fwrite(&aux, sizeof(N_INT), 1, fp); // grava o valor novo
    }
    else{ // Se a lista não existia (1° inserção daquele índice no hash)
      fseek(fph, h*sizeof(int), SEEK_SET); // vai no arquivo de indices (na posição onde h está)
      fwrite(&pos, sizeof(int), 1, fph); // grava o offset do registro no arquivo de dados
    }
    fclose(fp);
    fclose(fph);
    return;
  }
  // Achamos um buraco pra inserção
  fseek(fp, prim_pos_livre, SEEK_SET); // vai pra posição livre no arquivo de dados
  fread(&aux, sizeof(N_INT), 1, fp); // lê o registro que está ali
  // Atribui novos valores de cr, matricula e status
  aux.numero = mat;
  aux.status = 1;
  fseek(fp, prim_pos_livre, SEEK_SET); // volta o cursor pra posição correta
  fwrite(&aux, sizeof(N_INT), 1, fp); // grava o valor lá
  fclose(fp);
  fclose(fph);
  return;
}

N_INT* TH_aloca_inteiros(int mat){
  N_INT *novo = (N_INT*)malloc(sizeof(N_INT));
  novo->numero = mat;
  novo->prox = -1;
  novo->status = 1;
  return novo;
}

N_INT* TH_busca_inteiros(char *tabHash, char *dados, int n, int mat){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp)exit(1);
  int pos, h = TH_hash(mat,n); // Calcula o indice do arquivo tabHash
  fseek(fp, h*sizeof(int), SEEK_SET); //fseek para posição correta do vetor de indices
  fread(&pos, sizeof(int), 1, fp); // guardando o valor lido
  fclose(fp);
  if(pos == -1)return NULL; // Se pos == 1 => não existe valor associado a essa posição ainda
  fp = fopen(dados,"rb"); // abre o arquivo de dados
  if(!fp) exit(1);
  fseek(fp, pos, SEEK_SET); // vai pra posição onde o dado tá guardado no arquivo de dados
  N_INT aux;
  fread(&aux, sizeof(N_INT), 1, fp); // lê o primeiro nó da lista 
  while(1){
    if((aux.numero == mat) && (aux.status)){ // verifica se encontrou o nó buscado
      N_INT *resp = TH_aloca_inteiros(aux.numero); // se encontrou => aloca ele na memória principal
      resp->prox = aux.prox;
      fclose(fp);
      return resp;
    }
    if(aux.prox == -1){ // não encontrou => retorna NULL
      fclose(fp);
      return NULL;
    }
    fseek(fp, aux.prox, SEEK_SET); // p = p->prox
    fread(&aux, sizeof(N_INT), 1, fp); // lê novo valor de p
  }
}

void TH_retira_inteiros(char *tabHash, char *arq, int n, int mat){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp) exit(1);
  int pos, h = TH_hash(mat,n);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1)return;
  float cr = -1;
  fp = fopen(arq,"rb+");
  if(!fp)exit(1);
  N_INT aux;
  while(1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(N_INT), 1, fp);
    if((aux.numero == mat) && (aux.status)){
      aux.status = 0; // atualiza o status para 0 => removido
      fseek(fp, pos, SEEK_SET); // volta o cursor pra posição pos
      fwrite(&aux, sizeof(N_INT), 1, fp); // sobrescreve valor novo
      fclose(fp);
      return;
    }
    if(aux.prox == -1){
      fclose(fp);
      return;
    }
    pos = aux.prox;
  }
}

void inter(char* arq1, char* arq2, char* saida) {
  char tabHash[] = "tabIndices.bin";
  char tabDados[] = "tabDados.bin";
  char linha[100];
  int n = 7, numero;
  TH_inicializa(tabHash, tabDados, n);

  FILE *arq_1 = fopen(arq1, "r");
  while(fgets(linha, sizeof(linha), arq_1)) {
    numero = atoi(linha);
    TH_insere_inteiros(tabHash, tabDados, n, numero);
  }
  fclose(arq_1);
  FILE *arq_2 = fopen(arq2, "r");
  FILE *arq_saida = fopen(saida, "w");
  while(fgets(linha, sizeof(linha), arq_2)) {
    numero = atoi(linha);
    if(TH_busca_inteiros(tabHash, tabDados, n, numero)) {
      fprintf(arq_saida, "%d\n", numero);
    }
  }
  fclose(arq_2);
  fclose(arq_2);
  fclose(arq_saida);
}

void dif_sim(char* arq1, char* arq2, char* saida) {
  char tabHash[] = "tabIndices.bin";
  char tabDados[] = "tabDados.bin";
  char linha[100];
  int n = 7, numero;
  TH_inicializa(tabHash, tabDados, n);

  FILE *arq_1 = fopen(arq1, "r");
  while(fgets(linha, sizeof(linha), arq_1)) {
    numero = atoi(linha);
    TH_insere_inteiros(tabHash, tabDados, n, numero);
  }
  fclose(arq_1);

  FILE *arq_2 = fopen(arq2, "r");
  FILE *arq_saida = fopen(saida, "w");
  while(fgets(linha, sizeof(linha), arq_2)) {
    numero = atoi(linha);
    if(TH_busca_inteiros(tabHash, tabDados, n, numero)) {
      TH_retira_inteiros(tabHash, tabDados, n, numero);
    } else fprintf(arq_saida, "%d\n", numero);
  }
  fclose(arq_2);

  FILE *f_hash = fopen(tabHash, "rb");
  int vet[n];
  fread(&vet, sizeof(int), n, f_hash);
  fclose(f_hash);

  FILE *f_dados = fopen(tabDados, "rb");
  int i, pos;
  for(i = 0; i < n; i++) {
    int p = vet[i];
    if(p == -1) continue;
    N_INT x;
    while(p != -1) {
      fseek(f_dados, p, SEEK_SET);
      fread(&x, sizeof(N_INT), 1, f_dados);
      if(x.status == 1) fprintf(arq_saida, "%d\n", x.numero);
      //fprintf(arq_saida, "%d\n", x.numero);
      p = x.prox;
    }
  }
  fclose(f_dados);
  fclose(arq_saida);
}

void uniao(char* arq1, char* arq2, char* saida) {
  char tabHash[] = "tabIndices.bin";
  char tabDados[] = "tabDados.bin";
  char linha[100];
  int n = 7, numero;
  TH_inicializa(tabHash, tabDados, n);

  FILE *arq_1 = fopen(arq1, "r");
  FILE *arq_saida = fopen(saida, "w");
  while(fgets(linha, sizeof(linha), arq_1)) {
    numero = atoi(linha);
    TH_insere_inteiros(tabHash, tabDados, n, numero);
    fprintf(arq_saida, "%d\n", numero);
  }
  fclose(arq_1);

  FILE *arq_2 = fopen(arq2, "r");
  while(fgets(linha, sizeof(linha), arq_2)) {
    numero = atoi(linha);
    if(!TH_busca_inteiros(tabHash, tabDados, n, numero)){
      fprintf(arq_saida, "%d\n", numero);
    }
  }
  
  fclose(arq_2);
  fclose(arq_saida);
}

