
#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <unistd.h>

int main(){
    int res;
    if ((res = sysconf(_SC_CLK_TCK)) == -1){
        perror("sysconf");
    }
    else{
        printf("No of clock ticks per second = %d\n", res);
    }

    if ((res = sysconf(_SC_CHILD_MAX)) == -1){
        perror("sysconf");
    }
    else{
        printf("Maximum number of childs = %d\n", res); //Should be equal to ulimit -u
    }

    if ((res = pathconf("/", _PC_PATH_MAX)) == -1){
        perror("pathconf");
    }
    else{
        printf("Maximum number of characters in the path = %d\n", res);
    }
 
    if ((res = pathconf("/", _PC_NAME_MAX)) == -1){
        perror("sysconf");
    }
    else{
        printf("Maximum number of characters in filename = %d\n", res);
    }
    
    if ((res = sysconf(_SC_OPEN_MAX)) == -1){
        perror("sysconf");
    }
    else{
        printf("Maximum number of open files = %d\n", res); //Should be equal to ulimit -n
    }

    return 0;
}
