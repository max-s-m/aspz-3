#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void rec(int);

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Need one argument: amount of recursions\n");
        exit(1);
    }
    int recs = atoi(argv[1]);
    signal(SIGSEGV, limit_reached);
    printf("Recursing %d times...\n", recs);
    rec(recs);
}

//Рекурсивна функція, що нічого корисного не робить
void rec(int n){
    if(n <= 0){
        printf("Recursion finished\n");
        return;
    }
    rec(n - 1);
}
