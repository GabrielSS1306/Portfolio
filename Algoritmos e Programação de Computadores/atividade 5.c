#include <stdio.h>
#include <stdlib.h>

int main()
{
    int escolha; 

    printf ("LOJA DE VENDAS");
    printf("Escolha o móvel que você deseja solicitar:\n");
    printf("1. Cadeira\n");
    printf("2. Mesa de Computador\n");
    printf("3. Estante de Livros\n");
    printf("4. Mesa de Impressora\n");
    printf("5. Estante de CDs\n");

    printf("--> \n");
    scanf("%d", &escolha);

    if (escolha == 1){
        printf("Você selecionou a Cadeira!\n");
    }
    if (escolha == 2){
        printf("Você selecionou a Mesa de Computador!\n");
    }
    if (escolha == 1){
        printf("Você selecionou a Estante de Livros!\n");
    }
    if (escolha == 1){
        printf("Você selecionou a Mesa de Impressora!\n");
    }
    if (escolha == 1){
        printf("Você selecionou a Estante de CDs!\n");
    }
    else{
        printf("Item indisponível!\n");
    }
    return 0;
}
