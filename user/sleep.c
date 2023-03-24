#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
    if (argc <= 1 || argc > 2) {
        fprintf(2, "sleep: missing operand\n");
        exit(1);
    }

    int second = atoi(argv[1]);
    sleep(second);
    exit(0);
}