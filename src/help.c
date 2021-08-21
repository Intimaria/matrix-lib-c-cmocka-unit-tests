#include <stdio.h>

#include "../includes/help.h"

#define _HERE_ ""

FILE *f;
void print_help()
{
    char c;
    f = fopen(_HERE_"help.txt","r");
    if (f) {
        while((c=fgetc(f))!=EOF) {
            printf("%c",c);
        }
    } else {
        perror("Error");
    }
    fclose(f);
}


