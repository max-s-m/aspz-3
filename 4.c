#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void limit_reached(int);
void lottery(int *, int, int);
void print_nums(int *, int);

int main(){
    signal(SIGXCPU, limit_reached);
    srand(time(NULL));

    int res_49[7];
    int res_36[6];
    lottery(res_49, 7, 49);
    lottery(res_36, 6, 36);

    printf("7 із 49: ");
    print_nums(res_49, 7);
    printf("6 із 36: ");
    print_nums(res_36, 6);
}

//Цей код не може навантажити систему достатньо для досягнення навіть ulimit -t 1
void lottery(int *arr, int n, int max){
    int used[max + 1];
    for(int i=0; i <= max; i++){
        used[i] = 0;
    }
    for(int i=0; i < n;){
        int num = (rand() % max) + 1;
        if(!used[num]){
            arr[i++] = num;
            used[num] = 1;
        }
    }
}

void print_nums(int *arr, int n){
    for(int i=0; i < n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void limit_reached(int n){
    printf("Cpu is tired\n");
    exit(1);
}
