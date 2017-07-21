#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

    pid_t pid;
    

    if ((pid = fork()) == -1)
        perror("Fork Error");
   
    else if (pid == 0){ //The child forks and exits immediately
        
        pid_t pid1;
        if ((pid1 = fork()) == -1)
            perror("Fork Error");
        
        else if (pid1 == 0){
            sleep(2); //Just in case the parent hasn't exited
            printf("Child process Inherited by Init\nPPID=%d\n", getppid()); //In Linux upstart Inherits the child, which is a replacement for init daemon
        }
        
        exit(0);
    }
   
    else{//Parent
        wait(NULL); //Parent reaps the exit status of the child almost immediately
        system("ps -ao pid,ppid,stat,cmd");
    }
    
    return 0;
}


