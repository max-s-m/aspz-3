#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    //Відкривайться купа файлів
    int i=0;
    while(1){
        FILE *file = fopen("empty", "r");
        if(!file){
            printf("Limit reached. Opened %d files\n", i);
            exit(1);
        }
        i++;
    }
}
