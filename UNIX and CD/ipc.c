#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main(int argc, char **argv){
    int fd, num1, num2;
    char buf[100];

    if (argc == 3){
        mkfifo(argv[1], 0666);
        fd = open(argv[1], O_WRONLY);
        num1 = write(fd, argv[2], strlen(argv[2]));
        printf("Written %d bytes to the fifo file\n", num1);
    }
    if (argc == 2){
        fd = open(argv[1], O_RDONLY);
        num2 = read(fd, buf, sizeof(buf));
        buf[num2] = '\0';
        printf("Read %d bytes from the fifo file\nFile contents :\n%s\n", num2, buf);
    }
    
    close(fd);
    unlink(argv[1]);

    return 0;
}

