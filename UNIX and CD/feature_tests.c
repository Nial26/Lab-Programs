#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <unistd.h>

int main(){

#ifdef _POSIX_JOB_CONTROL
    printf("System Supports BSD style Job Control\n");
#else
    printf("System doesn't support job control\n");
#endif

#ifdef _POSIX_SAVED_IDS
    printf("System allows processes to save UID's and GID's\n");
#else
    printf("System doesn't support saved ids\n");
#endif

#ifdef _POSIX_CHOWN_RESTRICTED
    printf("System supports chown restricted\n");
#else
    printf("System doesn't globally define CHOWN_RESTRICTED, it needs to checked per file basis\n");
#endif

#ifdef _POSIX_NO_TRUNC
    printf("System supports no trunc\n");
#else
    printf("System doesn't globally define NO_TRUNC, it needs to be checked per directory basis\n");
#endif

#ifdef _POSIX_VDISABLE
    printf("System supports vdisable\n");
#else
    printf("System doesn't globally define disabling character, it needs to be checked per terminal\n");
#endif

    return 0;
}
