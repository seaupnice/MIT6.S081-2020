#include "kernel/types.h"
#include "user/user.h"

void primes(int *prime, int length)
{
    printf("prime %d\n", prime[0]);
    if (length == 1) {
        exit(0);
    }
    int fd[2];
    pipe(fd);
    if (fork()== 0) {
        close(fd[1]);
        char buf[4];
        int index = 0;
        while (read(fd[0], buf, sizeof(int)) != 0) {
            prime[index++] = *((int *)buf);
        }
        close(fd[0]);
        primes(prime, index);
        exit(0);
    }

    close(fd[0]);
    for (int i = 1; i < length; i++) {
        if (prime[i] % prime[0] != 0) {
            write(fd[1], &prime[i], sizeof(int));
        }
    }
    close(fd[1]);
  
    wait(0);
    exit(0);
}

int main(int argc, char *argv[])
{
    int primesArr[36];
    int index = 0;
    for (int i = 2; i < 36; i++) {
        primesArr[index++] = i;
    }
    primes(primesArr, index);
    exit(0);
}