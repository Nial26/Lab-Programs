#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(){
    pid_t pid;

    if ((pid = fork()) < 0){
        perror("Fork Error");
    }
    else if (pid == 0){ //Child
        exit(0); //Exit Immediately
    }
    else{ //Parent
        sleep(3); //Parent doesn't Reap the exit status of the child
        system("ps -a -o pid,ppid,stat,cmd");
    }

    return 0;
}

