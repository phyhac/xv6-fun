#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    int p[2];
    int pin, pout;
    pipe(p);

    int msg[1];
    int recv_num;
    int my_prime = 0;
    int has_son = 0;

    has_son = fork();
    if (!has_son) {4
        // using dup(), don't 'pin = p[0]' !
        pin = dup(p[0]);
        close(p[0]);
        close(p[1]);

        while (read(pin, (char *)msg, 4) > 0) {
            recv_num = *msg;

            // recv number the first time!
            if (!my_prime) {
                my_prime = recv_num;
                printf("prime %d\n", my_prime);
                continue;
            }
            
            if (recv_num % my_prime != 0) {
                if (has_son) {
                    write(pout, (char *)msg, 4);
                } else {
                    // create new pipe for the subprocess
                    pipe(p);
                    has_son = fork();
                    if (!has_son) {
                        pin = dup(p[0]);
                        my_prime = 0;
                    } else {
                        pout = dup(p[1]);
                        write(pout, (char *)msg, 4);
                    }
                    close(p[0]);
                    close(p[1]);
                }
            }
        }
        close(pin);
        if (has_son) 
            close(pout);
    } else {
        pout = dup(p[1]);
        close(p[0]);
        close(p[1]);
        for (int i = 2; i <= 35; i++) {
            *msg = i;
            write(pout, (char *)msg, 4);
        }
    }

    // except the last process
    if (has_son) {
        close(pout);
        wait(0);
    }
    exit(0);
}