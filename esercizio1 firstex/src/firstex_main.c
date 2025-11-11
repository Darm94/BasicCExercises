#include <stdio.h>

int main (int argc, char** argv)
{

    puts("Hi, this simple code print all the parameters passed to this executable file throught the terminal: ");
    
    for (int i=1; i<argc; i++){
        printf("Arg number %d: \"%s\"\n",i, argv[i]);
    }

    return 0;
}