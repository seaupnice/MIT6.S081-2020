#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    char *args[MAXARG];
    int argsIndex = 0;
    char pipeLine[1024];
    int n;

    if(argc < 2){
        fprintf(2, "Usage:xargs command (args...)\n");
        exit(1);
    }

    for (int i = 1; i < argc && argsIndex < MAXARG-1; i++) {
        args[argsIndex++] = argv[i];
    }
    while ((n = read(0, pipeLine, 1024)) > 0) {
        if (fork() == 0) {
            char *arg = (char *)malloc(sizeof(pipeLine));
            int index = 0;
            for (int i = 0; i < n; i++) {
                if (pipeLine[i] == ' ' || pipeLine[i] == '\n') {
                    arg[index] = '\0';
                    index = 0;
                    args[argsIndex++] = arg;
                    arg = (char *)malloc(sizeof(pipeLine));
                } else {
                    arg[index++] = pipeLine[i];
                }
            }
            arg[index] = 0;
            args[argsIndex] = 0;
            exec(args[0], args);
        } else {
            wait(0);
        }
    }
    exit(0);
}