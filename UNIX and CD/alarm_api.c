#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define INTERVAL 2

void callme(int signo){
    printf("Signal Handler Called\n");
}

int main(){
    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_handler = callme;

    if (sigaction(SIGALRM, &action, 0) == -1){
        perror("Sigaction");
        exit(1);
    }

    alarm(INTERVAL);

    pause();

    return 0;
}




