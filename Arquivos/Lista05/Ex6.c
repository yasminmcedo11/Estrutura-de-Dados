#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    char nome[50], cpf[12];
    int conta_corrente, agencia;
    float saldo;
}Cliente;

typedef struct indice{
    char cpf[12];
    int offset;
    float saldo;
}Indice;

void gerar_arquivo_indices(char *arq, char *arq_indices);
void imprimir_indices(char *arquivo_indice);
int comparar_por_saldo(const void *a, const void *b);

int main() {
    char arquivo_dados[] = "clientes.bin";
    char arquivo_indice[] = "indices.bin";

    gerar_arquivo_indices(arquivo_dados, arquivo_indice);
    imprimir_indices(arquivo_indice);

    return 0;
}

int comparar_por_saldo(const void *a, const void *b) {
    Indice *x = (Indice*) a;
    Indice *y = (Indice*) b;

    if (x->saldo < y->saldo) return -1;
    if (x->saldo > y->saldo) return 1;
    return 0;
}

void gerar_arquivo_indices(char *arqDados, char *arqIndices) {
    FILE *arq_dados = fopen(arqDados, "rb");
    FILE *arq_indices = fopen(arqIndices, "wb");
    if(!arq_dados || !arq_indices) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1);
    }

    int tamanho, qtd_registros;
    fseek(arq_dados, 0, SEEK_END);
    tamanho = ftell(arq_dados);
    qtd_registros = tamanho/sizeof(Cliente);
    rewind(arq_dados); //voltando o cursor para o inicio do arquivo

    Indice *vet_clientes = (Indice*) malloc(qtd_registros*sizeof(Indice));
    Cliente *c1 = (Cliente*) malloc(sizeof(Cliente));
    int offset = ftell(arq_dados);
    int n = 0;

    while(fread(c1, sizeof(Cliente), 1, arq_dados) == 1) {
        strcpy(vet_clientes[n].cpf, c1->cpf);
        vet_clientes[n].offset = offset;
        vet_clientes[n].saldo = c1->saldo;
        //fwrite(registro, sizeof(Indice), 1, arq_indices);
        offset = ftell(arq_dados);
        n++;
    }

    qsort(vet_clientes, n, sizeof(Indice), comparar_por_saldo);
    fwrite(vet_clientes, sizeof(Indice), n, arq_indices);

    fclose(arq_dados);
    fclose(arq_indices);
}

void imprimir_indices(char *arquivo_indice) {
    FILE *arq = fopen(arquivo_indice, "rb");
    if (!arq) {
        printf("Erro ao abrir %s\n", arquivo_indice);
        exit(1);
    }
    Indice idx;
    printf("\n--- Conteúdo do arquivo de índices ---\n");
    while (fread(&idx, sizeof(Indice), 1, arq) == 1) {
        printf("CPF: %s  |  Offset: %ld\n", idx.cpf, idx.offset);
    }

    fclose(arq);
}
