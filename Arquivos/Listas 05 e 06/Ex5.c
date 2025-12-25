#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{
    char nome[50], cpf[12];
    int conta_corrente, agencia;
    float saldo;
}Cliente;

Cliente* busca_por_cpf(char *Arq, char *cpf);
void gerar_arquivo_clientes(char *arquivo);

int main() {
    char arquivo[] = "clientes.bin";
    char cpf[11];
    Cliente *c;

    gerar_arquivo_clientes(arquivo);
    printf("Deseja consultar dados de qual cliente? \n");
    printf("Entrar com valor do cpf: \n");
    scanf("%11s", cpf);

    c = busca_por_cpf(arquivo, cpf);
    if(!c) printf("Cliente nao encontrado");
    else {
        printf("Nome: %s\n", c->nome);
        printf("CPF: %s\n", c->cpf);
        printf("Conta: %d\n", c->conta_corrente);
        printf("Agencia: %d\n", c->agencia);
        printf("Saldo: %2.f\n", c->saldo);
    }

    return 0;
}

void gerar_arquivo_clientes(char *arquivo) {
    FILE *arq = fopen(arquivo, "wb");
    if (!arq) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    Cliente clientes[] = {
        {"Ana Souza", "1111111111", 101, 500, 560.80},
        {"Bruno Lima", "2222222222", 102, 1200, 1200.50},
        {"Carla Dias", "3333333333", 103, 300, 3500.90},
        {"Daniel Araujo", "4444444444", 104, 900, 400.00}
    };

    int count = sizeof(clientes) / sizeof(Cliente);
    fwrite(clientes, sizeof(Cliente), count, arq);
    fclose(arq);
}

Cliente* busca_por_cpf(char *Arq, char *cpf) {
    FILE *arq = fopen(Arq, "rb");
    if(!arq) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    Cliente *c1 = (Cliente*) malloc(sizeof(Cliente));
    while(fread(c1, sizeof(Cliente), 1, arq) == 1) {
        if (strcmp(c1->cpf, cpf) == 0) {
            fclose(arq);
            return c1;
        }
    }
    fclose(arq);
    free(c1);
    return NULL;
}