#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char    *program_2[2] = {"/bin/ls", NULL};
char    *program_3[2] = {"/bin/cat", NULL};

int main(int argc, char **argv, char **envp)
{
    int fd[2];
    pid_t pid;
    pid_t pid2;

    pipe(fd);
    if ((pid = fork()) == 0) //Child process
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(program_3[0], program_3, NULL);
    }
    else if (pid > 0) //Parent process
    {
        if ( (pid2 = fork()) == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            execve(program_2[0], program_2, NULL);
        }
    }
    waitpid(pid, 0, 0);
    waitpid(pid2, 0, 0);
    return (EXIT_SUCCESS);
}

