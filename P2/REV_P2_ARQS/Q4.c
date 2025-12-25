#include "TH.c"
#include <string.h>

void complemento(char **arqs, int n, char* universo, char *saida){
  char hash_table[] = "hash.bin";
  char hash_dados[] = "dados.bin";
  int tam = 7; // definindo o tamanho do vetor da hash (tinha esquecido de definir na prova)
  TH_inicializa(hash_dados, hash_table, tam);

  FILE *f_universo = fopen(universo, "rb");
  int num;

  // leio o arquivo universo salvando os dados na hash
  while(fread(&num, sizeof(int), 1, f_universo) == 1) { // aqui só alterei o == para 1 (leitura bem sucedida)
    TH_insere(hash_table, hash_dados, tam, num);
  }
  fclose(f_universo);

  // leio os subconjuntos e vou retirando da hash todos os numeros presentes nos arquivos de subconjunto
  for(int i = 0; i < n; i++) {
    FILE *arq = fopen(arqs[i], "rb"); // alterei para ler os arqs[i] (antes tava só arqs)
    while(fread(&num, sizeof(int), 1, arq) == 1) { // aqui a mesma alteração do == para == 1
      if(TH_busca(hash_table, hash_dados, tam, num)) TH_retira(hash_table, hash_dados, tam, num);
    }
    fclose(arq);
  }

  // leitura do hash final.
  // aqui foi onde aconteceram as maiores mudanças pra eu conseguir salvar corretamente os valores 
  // nos arquivos de saida.
  // antes eu tentava acessar diretamente os valores do vetor de hash usando o TH_hash dentro de um for
  // porém vi que ficava mais fácil só salvar o vetor de hash num vetor real para depois acessar os valores
  FILE *f_hash = fopen(hash_table, "rb");
  int vet[tam];
  fread(vet, sizeof(int), tam, f_hash);
  fclose(f_hash);

  FILE *f_dados = fopen(hash_dados, "rb");
  FILE *arq_saida = fopen(saida, "wb");
  int i, pos;
  for(i = 0; i < tam; i++) {
    // ele percorre o vetor de hash e vai buscando item da lista encadeada associada
    int p = vet[i];
    if(p == -1) continue;
    TNUM x;
    while(p != -1) {
      fseek(f_dados, p, SEEK_SET);
      fread(&x, sizeof(TNUM), 1, f_dados);
      // quando eu retiro ele decrementa a quantidade, então é só pegar todos os elementos que tem 0 qtde
      if(x.qtde > 0) fwrite(&x.num, sizeof(int), 1, arq_saida);
      p = x.prox;
    }
  }
  fclose(f_dados);
  fclose(arq_saida);
}

int main(int argc, char **argv){
  if(argc == 1) printf("ERRO: <./nome_exec> <arq_universo> <arq_saida> <lista arquivos a serem pesquisados>\n");
  else{
    int n = argc - 3, i;
    char **arq = (char **)malloc(sizeof(char *) * n);
    for(i = 0; i < n; i++){
      arq[i] = (char *) malloc(sizeof(char) * 31);
      strcpy(arq[i], argv[i + 3]);
    }
    int ant, num;
    FILE *fp = fopen(argv[1], "wb");
    if(!fp) exit(1);
    while(1){
      printf("Digite um numero para o arquivo UNIVERSO... Pare quando o numero for menor ou igual ao anterior...\n");
      do{
        scanf("%d", &ant);
        if(ant >= 0){
          fwrite(&ant, sizeof(int), 1, fp);
          break;
        }
      }while(1);
      do{
        scanf("%d", &num);
        if(num <= ant) break;
        fwrite(&num, sizeof(int), 1, fp);
        ant = num;
      }while(1);
      break;
    }
    fclose(fp);
    
    for(i = 0; i < n; i++) printf("arq[%d] = %s\n", i, arq[i]);
    for(i = 0; i < n; i++){
      FILE *fp = fopen(arq[i], "wb");
      if(!fp) exit(1);
      while(1){
        printf("Digite um numero... Pare quando o numero for menor ou igual ao anterior...\n");
        do{
          scanf("%d", &ant);
          if(ant >= 0){
            fwrite(&ant, sizeof(int), 1, fp);
            break;
          }
        }while(1);
        do{
          scanf("%d", &num);
          if(num <= ant) break;
          fwrite(&num, sizeof(int), 1, fp);
          ant = num;
        }while(1);
        break;
      }
      fclose(fp);
    }

    complemento(arq, n, argv[1], argv[2]);
    
    
    FILE *fp_saida = fopen(argv[2], "rb");
    if(!fp_saida) exit(1);
    int r, num_2;
    while(1){
      r = fread(&num_2, sizeof(int), 1, fp_saida);
      if(r != 1){
        fclose(fp_saida);
        break;
      }
      printf("%d ", num_2);
    }
    printf("\n");
    
    
    for(i = 0; i < n; i++) free(arq[i]);
    free(arq);
  }  
  return 0;
}

