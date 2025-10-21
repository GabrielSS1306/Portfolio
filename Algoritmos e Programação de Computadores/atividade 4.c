#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    printf ("Informe um caracter: \n");
    scanf("%c", &c);

    system ("clear");

    printf("Caracter: %c \n", c);
    printf("Decimal: %d \n", c);
    printf("Octal: %o \n", c);
    printf("Hexadecimal: %x \n", c);

    return 0;
}
