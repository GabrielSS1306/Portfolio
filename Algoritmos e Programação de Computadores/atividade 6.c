#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    const char *s;

    printf("Informe a primeira letra da inicial do termo que identifica seu sexo\n");
    scanf("%c", &c);

    system("cls");

    s = (c == "f" || c == "F")?"Feminino":(c == "m"  || c == "M")?"Masculino": "Inválido";

    printf("Sexo %s", s);
    return 0;
}
