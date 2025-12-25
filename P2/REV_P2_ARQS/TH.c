#include "TH.h"

int TH_hash(int num, int tam){
  return num % tam;
}

void TH_inicializa(char *tabDados, char *tabHash, int tam){
  FILE *fp = fopen(tabDados, "wb");
  if(!fp) exit(1);
  fclose(fp);
  fp = fopen(tabHash, "wb");
  if(!fp) exit(1);
  int i, elem = -1;
  for(i = 0; i < tam; i++)fwrite(&elem, sizeof(int), 1, fp);
  fclose(fp);
}

TNUM* TH_aloca(int num, int qtde){
  TNUM *novo = (TNUM*)malloc(sizeof(TNUM));
  novo->num = num;
  novo->prox = -1;
  novo->qtde = qtde;
  return novo;
}

TNUM* TH_busca(char *tabHash, char *dados, int tam, int num){
  FILE *fp = fopen(tabHash, "rb");
  if(!fp)exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1)return NULL;
  fp = fopen(dados,"rb");
  if(!fp) exit(1);
  fseek(fp, pos, SEEK_SET);
  TNUM aux;
  fread(&aux, sizeof(TNUM), 1, fp);
  while(1){
    if((aux.num == num) && (aux.qtde)){
      TNUM *resp = TH_aloca(aux.num, aux.qtde);
      resp->prox = aux.prox;
      fclose(fp);
      return resp;
    }
    if(aux.prox == -1){
      fclose(fp);
      return NULL;
    }
    fseek(fp, aux.prox, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
  }
}

void TH_retira(char *tabHash, char *dados, int tam, int num){
  FILE *fp = fopen(tabHash,"rb");
  if(!fp) exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fp, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fp);
  fclose(fp);
  if(pos == -1) return;
  fp = fopen(dados,"rb+");
  if(!fp)exit(1);
  TNUM aux;
  while(1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
    if((aux.num == num) && (aux.qtde)){
      aux.qtde--;
      fseek(fp, pos, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
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

void TH_insere(char *tabHash, char *dados, int tam, int num){
  FILE *fph = fopen(tabHash, "rb+");
  if(!fph) exit(1);
  int pos, h = TH_hash(num, tam);
  fseek(fph, h*sizeof(int), SEEK_SET);
  fread(&pos, sizeof(int), 1, fph);
  int ant, prim_pos_livre;
  ant = prim_pos_livre = -1;
  FILE *fp = fopen(dados,"rb+");
  if(!fp){
    fclose(fph);
    exit(1);
  }
  TNUM aux;
  while(pos != -1){
    fseek(fp, pos, SEEK_SET);
    fread(&aux, sizeof(TNUM), 1, fp);
    if(aux.num == num){
      aux.qtde++;
      fseek(fp, pos, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
      fclose(fp);
      fclose(fph);
      return;
    }
    if((!aux.qtde) && (prim_pos_livre == -1))prim_pos_livre=pos;
    ant = pos;
    pos = aux.prox;
  }
  if(prim_pos_livre == -1){
    aux.num = num;
    aux.prox = -1;
    aux.qtde = 1;
    fseek(fp, 0L, SEEK_END);
    pos = ftell(fp);
    fwrite(&aux, sizeof(TNUM), 1, fp);
    if(ant != -1){
      fseek(fp, ant, SEEK_SET);
      fread(&aux, sizeof(TNUM), 1, fp);
      aux.prox = pos;
      fseek(fp, ant, SEEK_SET);
      fwrite(&aux, sizeof(TNUM), 1, fp);
    }
    else{
      fseek(fph, h*sizeof(int), SEEK_SET);
      fwrite(&pos, sizeof(int), 1, fph);
    }
    fclose(fp);
    fclose(fph);
    return;
  }
  fseek(fp, prim_pos_livre, SEEK_SET);
  fread(&aux, sizeof(TNUM), 1, fp);
  aux.num = num;
  aux.qtde = 1;
  fseek(fp, prim_pos_livre, SEEK_SET);
  fwrite(&aux, sizeof(TNUM), 1, fp);
  fclose(fp);
  fclose(fph);
  return;
}

void TH_imprime (char *tabHash, char *dados, int tam){
  FILE *fp = fopen(tabHash, "rb");
  if(!fp) exit(1);
  int vet[tam];
  fread(&vet, sizeof(int), tam, fp);
  fclose(fp);

  fp = fopen(dados, "rb");
  if(!fp) exit(1);
  int i, pos;
  for(i = 0; i < tam; i++){
    int p = vet[i];
    if(p != -1) printf("%d:\n", i);
    TNUM x;
    while(p != -1){
      fseek(fp, p, SEEK_SET);
      pos = ftell (fp);
      fread(&x, sizeof(TNUM), 1, fp);
      printf("$%d: num: %d\tqtde: %d\tprox_end: $%d\n", pos, x.num, x.qtde, x.prox);
      p = x.prox;
    }
  }
  fclose(fp);
}
