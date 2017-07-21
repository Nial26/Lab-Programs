#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv){
    if (argc != 2){
        printf("Usage <cmd>\n");
        exit(1);
    }
    else{
        pid_t pid;
        if ((pid = fork()) < 0){
            perror("Fork Error");
        }
        else if (pid == 0){
            execl("/bin/sh", "sh",  "-c", argv[1], (char *)NULL);
            exit(0);
        }
        else{
            wait(NULL);
        }
    }
    return 0;
}
