#include "TH_MS.h"

void cria_subconjuntos() {
    int s1[] = {2,4,6};
    int s2[] = {1,10};
    int s3[] = {3,4,5,9};

    FILE *f;

    f = fopen("sub1.bin", "wb");
    for(int i=0;i<3;i++) fwrite(&s1[i], sizeof(int), 1, f);
    fclose(f);

    f = fopen("sub2.bin", "wb");
    for(int i=0;i<2;i++) fwrite(&s2[i], sizeof(int), 1, f);
    fclose(f);

    f = fopen("sub3.bin", "wb");
    for(int i=0;i<4;i++) fwrite(&s3[i], sizeof(int), 1, f);
    fclose(f);
}

int main(void){
  //int n, m;
  //printf("Digite m... ");
  //scanf("%d", &m);
  //printf("Digite n... ");
  //scanf("%d", &n);

  //if((n <= 1) || (m <= 1)) return 0;

  //char nome_dados[31], nome_hash[31];
  //printf("Digite nome do arquivo de dados... ");
  //scanf("%s", nome_dados);
  //printf("Digite nome do arquivo de hash... ");
  //scanf("%s", nome_hash);

  //TH_inicializa(nome_hash, nome_dados, m);

  //int i, mat;
  //float cr;
  //for(i = 0; i < n; i++){
  //  printf("Digite a matricula e o cr...\n");
  //  scanf("%d", &mat);
  //  scanf("%f", &cr);
  //  TH_insere(nome_hash, nome_dados, m, mat, cr);
  //}
  //TH_imprime(nome_hash, nome_dados, m);

  //char resp;
  //do{
  //  printf("Digite a matricula a ser removida... ");
   // scanf("%d", &mat);
  //  cr = TH_retira(nome_hash, nome_dados, m, mat);
  //  if(cr != -1) printf("%d %f saiu\n", mat, cr);
  //  printf("Quer continuar? ");
   // scanf(" %c", &resp);
  //}while((resp != 'N') && (resp != 'n'));
 // TH_imprime(nome_hash, nome_dados, m);

  //printf("Digite a matricula a ser procurada... ");
  //scanf("%d", &mat);
  //TA *r = TH_busca(nome_hash, nome_dados, m, mat);
  //if(!r)
  //  printf("Elemento nao encontrado!\n");
  //else{
  //  printf("matricula: %d\tstatus: %d\tprox_end: %d\n", r->mat, r->status, r->prox);
  //  free(r);
 // }
  
 // do{
  //  printf("Digite a matricula e o cr... ");
  //  scanf("%d", &mat);
  //  scanf("%f", &cr);
  //  TH_insere(nome_hash, nome_dados, m, mat, cr);
  //  printf("Quer continuar? ");
   /// scanf(" %c", &resp);
  //}while((resp != 'N') && (resp != 'n'));
  //TH_imprime(nome_hash, nome_dados, m);

  int v[] = {1,2,3,4,5,6,7,8,9,10};
  FILE *f = fopen("universo.bin", "wb");
  for(int i = 0; i < 10; i++) fwrite(&v[i], sizeof(int), 1, f);
  fclose(f);
  cria_subconjuntos();

  char arquivo1[] = "arquivo_teste1.txt";
  char arquivo2[] = "arquivo_teste2.txt";
  char arquivo3[] = "arquivo_teste3Saida.txt";

  //inter(arquivo1, arquivo2, arquivo3);
  //dif_sim(arquivo1, arquivo2, arquivo3);
  uniao(arquivo1, arquivo2, arquivo3);

  return 0;
}
