#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void limit_reached(int n);

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Program need two arguments\n");
        exit(1);
    }

    FILE *from = fopen(argv[1], "r");
    if(!from){
        printf("Cannot open file %s for reading\n", argv[1]);
        exit(1);
    }
    FILE *to = fopen(argv[2], "w");
    if(!to){
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(from);
        exit(1);
    }
    signal(SIGXFSZ, limit_reached);

    //Копіювання побуквенне, щоб можна було побачити на якому моменті досягнуто ліміт
    char ch;
    while((ch = fgetc(from)) != EOF){
        if(fprintf(to, "%c", ch) < 0){
            printf("Couldn't write\n");
            fclose(from);
            fclose(to);
            exit(1);
        }
    }

    fclose(from);
    fclose(to);
}

void limit_reached(int sig){
    printf("\nI'm gonna stop you right there\n");
    exit(1);
}
