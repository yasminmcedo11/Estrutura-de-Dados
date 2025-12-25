#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    char nome[100];
    float media;
}Aluno;

void media(char *ArqEnt, char *ArqSaida);
int compara(const void *a, const void *b);

int main() {
    char entrada[] = "notas_entrada.txt";
    char saida[] = "notas_saida.txt";

    media(entrada, saida);
    printf("Procedimento realizado com sucesso!");

    return 0;
}

int compara(const void *a, const void *b) {
    Aluno *x = (Aluno*) a;
    Aluno *y = (Aluno*) b;

    if (x->media < y->media) return -1;
    if (x->media > y->media) return 1;
    return 0;
}

void media(char *ArqEnt, char *ArqSaida) {
    FILE *arq_entrada, *arq_saida;
    arq_entrada = fopen(ArqEnt, "r");
    arq_saida = fopen(ArqSaida, "w");
    if(!arq_entrada || !arq_saida) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1);
    }

    Aluno vet[50];
    char nome[100];
    float n1, n2, media;
    int qtd = 0;
    while(fscanf(arq_entrada, "%s %f %f", nome, &n1, &n2) == 3) {
        media = (n1 + n2)/2;
        strcpy(vet[qtd].nome, nome);
        vet[qtd].media = (n1+n2)/2;
        qtd++;
    }

    qsort(vet, qtd, sizeof(Aluno), compara);

    for(int i = 0; i < qtd; i++) {
        fprintf(arq_saida, "%s %.2f\n", vet[i].nome, vet[i].media);
    }

    fclose(arq_entrada);
    fclose(arq_saida);
}