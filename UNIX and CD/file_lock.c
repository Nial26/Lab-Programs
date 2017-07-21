#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv){
    if (argc == 2){

        int fd, num;
        char buf[100];

        fd = open(argv[1], O_RDWR);

        struct flock lock;

        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_END;
        lock.l_start = -1;
        lock.l_len = 50;
        lock.l_pid = getpid();

        printf("Checking Current lock\n");
        fcntl(fd, F_GETLK, &lock);
        
        if (lock.l_type != F_UNLCK){
            printf("File locked by process = %d\n", lock.l_pid);
            return 0;
        }
        
        else{
            printf("File is not locked\n");
            printf("Setting exclusive lock on the last 50 bytes of the file\n");
            fcntl(fd, F_SETLKW, &lock);
            printf("File Locked\n");
            printf("Reading last 50 bytes from the file ....\n");

            lseek(fd, -50, SEEK_END);
            num = read(fd, buf, 50);
            buf[num] = '\0';

            printf("Read Contents = %s\n", buf);

            printf("Enter to unlock the file\n");
            getchar();

            lock.l_type = F_UNLCK;
            num = fcntl(fd, F_SETLKW, &lock);

            printf("File Unlocked\n");
        }
    }
    else{
        printf("Usage <filename>\n");
        exit(1);
    }
    return 0;
}
