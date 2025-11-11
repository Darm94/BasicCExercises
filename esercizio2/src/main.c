#define _CRT_SECURE_NO_WARNINGS
#include "s_functions.h"
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv)
{
    const char* string_1 = "Hello";
    const char* string_2 = ": Part 2";
    const char* string_3 = "Hello";
    const char* string_4 = "Helko";
    char string_5[8] = {'H','e','l','l','o','o','o','\0'};


    printf("--CONCAT\n");
    char tmp_buffer[1024];
    strcpy(tmp_buffer,string_1);
    strcat(tmp_buffer,string_2);
    printf("%s\n", tmp_buffer); 

    printf("--COMPARE\n");
    if (strcmp(string_1, string_3) == 0)
        printf("String 1 equals String 3\n");
    else
        printf("String 1 not equal to String 3\n");

    if (strcmp(string_1, string_4) == 0)
        printf("String 1 equals String 4\n");
    else
        printf("String 1 not equal to String 4\n");

    printf("--STRING LENGHT\n");
    printf("Length of string_1: %llu\n", strlen(string_1));
    printf("Length of string_5: %llu\n", strlen(string_5));



    //now with my functions:
    printf("=================================\nNow My Functions: \n\n");
    printf("--CONCAT\n");
    char tmp_buffer2[1024];
    mystrcpy(tmp_buffer2,string_1);
    mystrcat(tmp_buffer2,string_2);
    printf("%s\n", tmp_buffer2);
    printf("--CONCAT SHORTER FUN\n");
    char tmp_buffer3[1024];
    mystrcpy2(tmp_buffer3,string_1);
    mystrcat2(tmp_buffer3,string_2);
    printf("%s\n", tmp_buffer3); 

    printf("--COMPARE\n");
    if (mystrcmp(string_1, string_3) == 0)
        printf("String 1 equals String 3\n");
    else
        printf("String 1 not equal to String 3\n");

    if (mystrcmp(string_1, string_4) == 0)
        printf("String 1 equals String 4\n");
    else
        printf("String 1 not equal to String 4\n");

    printf("--STRING LENGHT\n");
    printf("Length of string_1: %llu\n", mystrlen(string_1));
    printf("Length of string_5: %llu\n", mystrlen(string_5));


    printf("   --BYE TO THE NEXT EXERCISE!---   \n");
}
