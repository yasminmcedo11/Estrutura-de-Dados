#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE 10
#define RECORD_SIZE (WORD_SIZE * sizeof(char))
#define PAIR_RECORD_SIZE (2 * WORD_SIZE * sizeof(char))

typedef struct word{
    char word[WORD_SIZE];
}Word;

typedef struct word_pair{
    Word word1;
    Word word2;
}WordPair;

void gerar_arquivos_binarios(char *arq1, char *arq2);
int get_file_size(char* arq);
void produto_cartesiano(char *arq1, char *arq2, char *arq3);


int main() {
    char arquivo_1[] = "a.bin";
    char arquivo_2[] = "b.bin";
    char arquivo_3[] = "c.bin";

    gerar_arquivos_binarios(arquivo_1, arquivo_2);
    produto_cartesiano(arquivo_1, arquivo_2, arquivo_3);
    
    // TESTAGEM DO ARQUIVO FINAL
    FILE *arq_C = fopen(arquivo_3, "rb");
    if(!arq_C) {
        printf("Erro ao abrir o arquivo de saida.\n");
        exit(1);
    }
    WordPair pair_check;
    int qtd = 0;

    while(fread(&pair_check, PAIR_RECORD_SIZE, 1, arq_C) == 1) {
        char temp_a[WORD_SIZE + 1];
        char temp_b[WORD_SIZE + 1];
        memcpy(temp_a, pair_check.word1.word, WORD_SIZE);
        temp_a[WORD_SIZE] = '\0';
        memcpy(temp_b, pair_check.word2.word, WORD_SIZE);
        temp_b[WORD_SIZE] = '\0';
                
        printf("(%s, %s)\n", temp_a, temp_b);
        qtd++;
    }
    printf("%d pares ordenados gerados!\n", qtd);

    return 0;
}

void gerar_arquivos_binarios(char *arq1, char *arq2) {
    FILE *arq_A = fopen(arq1, "wb"), *arq_B = fopen(arq2, "wb");
    if (!arq_A || !arq_B) {
        printf("Erro ao abrir os arquivos. \n");
        exit(1);
    }

    Word words_A[] = {
        {"palavra_A1"},
        {"palavra_A2"},
        {"palavra_A3"},
        {"palavra_A4"}
    };
    int count_a = sizeof(words_A)/sizeof(Word);

    Word words_B[] = {
        {"palavra_B1"},
        {"palavra_B2"},
        {"palavra_B3"},
    };
    int count_b = sizeof(words_B)/sizeof(Word);

    fwrite(words_A, RECORD_SIZE, count_a, arq_A);
    fwrite(words_B, RECORD_SIZE, count_b, arq_B);
    fclose(arq_A);
    fclose(arq_B);
}

int get_file_size(char* arq) {
    FILE* fp = fopen(arq, "rb");
    if (fp == NULL) {
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fclose(fp);
    return size;
}

void produto_cartesiano(char *arq1, char *arq2, char *arq3) {
    FILE *arq_A, *arq_B, *arq_C;
    arq_A = fopen(arq1, "rb");
    arq_B = fopen(arq2, "rb");
    arq_C = fopen(arq3, "wb");
    if(!arq_A || !arq_B || !arq_C) {
        printf("Erro ao abrir os arquivos. \n");
        exit(1);
    }

    Word word_a, word_b;
    WordPair pair;
    int tamanho_a, qtd_palavras_a;
    tamanho_a = get_file_size(arq1);
    qtd_palavras_a = tamanho_a/RECORD_SIZE;

    for (int i = 0; i < qtd_palavras_a; i++) {
        fread(&word_a, RECORD_SIZE, 1, arq_A);
        fseek(arq_B, 0, SEEK_SET); // Volta ao início de b.bin

        while (fread(&word_b, RECORD_SIZE, 1, arq_B) == 1) {
            memcpy(pair.word1.word, word_a.word, WORD_SIZE);
            memcpy(pair.word2.word, word_b.word, WORD_SIZE);
            
            fwrite(&pair, PAIR_RECORD_SIZE, 1, arq_C);
        }
    }
    fclose(arq_A);
    fclose(arq_B);
    fclose(arq_C);
}