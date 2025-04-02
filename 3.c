#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void limit_reached(int);

int main(){
    FILE *file;
    int roll;
    //Тут обробка сигналу SIGXFS (SIGnal "eXceeded File SiZe")
    signal(SIGXFSZ, limit_reached);
    srand(time(NULL));
    file = fopen("rolls.txt", "w");
    if(file == NULL){
        printf("File wasn't opened\n");
        exit(1);
    }

    while(1){
        roll = (rand() % 6) + 1;

        if(fprintf(file, "rolled %d\n", roll) < 0){
            printf("Couldn't write'\n");
            break;
        }
        fflush(file);
    }
    fclose(file);
}

void limit_reached(int n){
    printf("I'm gonna stop you right there\n");
    exit(1);
}
