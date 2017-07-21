#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){

    if (argc != 3){
        printf("Usage <old file name> <new file name>\n");
        exit(1);
    }
    else{
        if (link(argv[1], argv[2]) == -1){
            perror("linking Error");
        }
        else{
            printf("Files linked Successfully\n");
        }
    }
    return 0;
}
