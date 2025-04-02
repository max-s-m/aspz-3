#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Need one argument - amount of forks\n");
        exit(1);
    }
    int dups = atoi(argv[1]);

    for(int i=0; i<dups; i++){
        //fork створює дуплікат поточного процесу
        pid_t pid = fork();

        //pid < 0, якщо процес не створився
        if(pid < 0){
            printf("forkn't\n");
            exit(1);
        }

        //pid = 0, якщо даний процес - дочірній (новостворений, кладемо його спати)
        //кожний з процесів "спить" секунду поки нові створюються, що засоряє рахунок одночасних процесів
        if(pid == 0){
            sleep(1);
            exit(0);
        }
    }
    //pid > 0 - батьківський процес
    printf("fork'd well\n");
}
