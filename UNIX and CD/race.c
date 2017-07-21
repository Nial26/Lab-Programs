#include <stdio.h>
#include <unistd.h>

void charatatime(char *str){
    char *ptr;
    int c;
    setbuf(stdout, NULL);
    for (ptr = str; (c = *ptr++) != 0; ){
        putc(c, stdout);
    }
}

int main(){
    pid_t pid;

    if ((pid = fork()) < 0){
        perror("fork Error");
    }
    else if (pid == 0){ //Child
        charatatime("OUTPUT FROM CHILD\n");
    }
    else{ //Parent
        charatatime("output from parent\n");
    }

    return 0;
}
