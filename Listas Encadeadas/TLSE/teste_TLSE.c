#include "TLSE.h"

int main(void){
    TLSE *l = TLSE_inicializa();
    TLSE *p = TLSE_inicializa();
    TLSE *novo;
    int x, i;
    printf("cheguei aqui\n");
    do{
        scanf("%d", &x);
        if(x == 0) break;
        l = TLSE_insere_ini(l, x);
    } while(1);
    printf("agora o vetor 2");
    do{
        scanf("%d", &x);
        if(x == 0) break;
        p = TLSE_insere_ini(p, x);
    } while(1);
    TLSE_imprime(l);
    printf("\n");
    //l = inverte(l);
    //p = inverte_nova_lista(l);
    //l = desloca(l, 1);
    //novo = copia(l);
    //l = rto (l, 2); 
    //novo = i_p(l);
    //i_p_void (l);
    //i = igual(l, p);
    //if (i == 0) {
     //   printf("Sao diferentes.\n");
    //} else if (i == 1) {
    //    printf("Sao iguais.\n");
    //}
    //l = junta_listas(l, p);
    //i = Contrario(l, p);
    //printf("%d\n", i);
    novo = ordena(l);
    TLSE_imprime(novo);

    return 0;
}