#include "calc.h"
#include <stdio.h>

int main (int argc, char** argv)
{
    puts("Hello");
    printf("Num arg: %d\n", argc);

    char* first = argv[0];
    printf("First arg: %s\n", first);

    return add(argc, 100);
}

//clang -E main.c -I ./      
//per scoprire come ragiona il pre processore
//se si usa i tydef occhio perchè allora anche nel sorgente di definizione va messso include e occhio ai tipi che si usano in fase di compilazione
