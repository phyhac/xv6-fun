#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    int p[2];
    char bytes[5];

    pipe(p);
    
    int pid = fork();
    int cpid = getpid();
    if (pid == 0) {
        char *DATA = "c";
        if (read(p[0], bytes, 1) == -1) {
            fprintf(2, "child recv error.\n");
            exit(1);
        }
        printf("%d: received ping: %s\n", cpid, bytes);
        write(p[1], DATA, 1);
    } else {
        char *DATA = "p";
        write(p[1], DATA, 1);
        if (read(p[0], bytes, 1) == -1) {
            fprintf(2, "parent recv error.\n");
            exit(1);
        }
        printf("%d: received pong: %s\n", cpid, bytes);
    }
    close(p[0]);
    close(p[1]);
    exit(0);
}