#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    int ping[2];
    int pong[2];

    pipe(ping);
    pipe(pong);
    if (fork() == 0) {
        close(ping[1]);
        close(pong[0]);
        int pn;
        char creadByte[2];
        pn = read(ping[0], creadByte, sizeof(creadByte));
        if (pn == 1) {
            printf("%d: received ping\n", getpid());
            //printf("%s\n", creadByte);
        }

        write(pong[1], "A", sizeof(char));
        close(ping[0]);
        close(pong[1]);
        exit(0);
    }
    close(ping[0]);
    close(pong[1]);
    write(ping[1], "A", sizeof(char));

    int fn;
    char preadByte[2];
    fn = read(pong[0], preadByte, sizeof(preadByte));
    if (fn == 1) {
        printf("%d: received pong\n", getpid());
        //printf("%s\n", preadByte);
    }
    close(ping[1]);
    close(pong[0]);
    wait(0);
    exit(0);
}