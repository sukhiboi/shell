#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void execute(char *command)
{
    int exitStatus = execlp(command, command, NULL);
    if (exitStatus == -1)
        printf("command not found\n");
}

void prompt()
{
    char cwd[255];
    printf("%s", getcwd(cwd, sizeof(cwd)));
    printf(" $ ");
}

int main()
{
    while (1)
    {
        signal(SIGINT, SIG_IGN);
        prompt();
        char command[255];
        gets(command);
        int pid = fork();
        if (pid == 0)
            execute(command);
        else
            wait(&pid);
    }
}