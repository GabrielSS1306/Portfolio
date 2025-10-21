#include <stdio.h>
#include <locale.h>

int main()
{
    int a, b, c;
    setlocale(LC_ALL, "portuguese");

    printf("Digite o primeiro número: ");
    scanf("%d", &a);
    printf("Digite o segundo número: ");
    scanf("%d", &b);
    printf("Digite o terceiro número: ");
    scanf("%d", &c);

    if(a>b && a>c){
    printf("O valor de %d e maior que os valores %d e %d.", a, b, c);
    }
    else if (b>a && b>c){
        printf("O valor de %d e maior que os valores %d e %d.", b, a, c);    
    }
    else {
        printf("O valor de %d e maior que os valores %d e %d.", c, a, b);
    }

    return 0;
}
