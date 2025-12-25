#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void RetRepet(char *ArqEnt, char *ArqSaida);

int main() {
    char entrada[] = "texto_teste.txt";
    char saida[] = "texto_saida.txt";

    RetRepet(entrada, saida);
    printf("Processo concluído com sucesso!");

    return 0;
}

void RetRepet(char *ArqEnt, char *ArqSaida) {
    FILE *arq_entrada, *arq_saida;

    arq_entrada = fopen(ArqEnt, "r");
    arq_saida = fopen(ArqSaida, "w");
    if (!arq_entrada || !arq_saida) {
        printf("Erro ao abrir o arquivo. \n");
        exit(1);
    }
    char atual[100], anterior[100];
    fscanf(arq_entrada, "%s", atual);
    fprintf(arq_saida, "%s", atual);
    strcpy(anterior, atual);

    while(fscanf(arq_entrada, "%s", atual) == 1) {
        if(strcmp(atual, anterior) != 0) fprintf(arq_saida, " %s", atual);
        strcpy(anterior, atual);
    }

    fclose(arq_entrada);
    fclose(arq_saida);
}