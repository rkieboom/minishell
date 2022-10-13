#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

char    *program_1[2] = {"/bin/cat", NULL};
char    *program_2[2] = {"/bin/cat", NULL};
char    *program_3[2] = {"/bin/ls", NULL};

typedef struct s_cmd
{
	char	**cmd;
	int		fd[2];
	struct s_cmd *next;
}				t_cmd;

t_cmd *init(void)
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->cmd = program_1;
	cmd->fd[0] = 0;
	cmd->fd[1] = 1;
	cmd->next = malloc(sizeof(t_cmd));
	cmd->next->cmd = program_2;
	cmd->next->fd[0] = 0;
	cmd->next->fd[1] = 1;
	cmd->next->next = malloc(sizeof(t_cmd));
	cmd->next->next->cmd = program_3;
	cmd->next->next->fd[0] = 0;
	cmd->next->next->fd[1] = 1;
	cmd->next->next->next = 0;
	return cmd;
}

static int exec_cmd(t_cmd *cmd)
{
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		if (cmd->fd[0] != 0)
		{
			dup2(cmd->fd[0], 0);
			close(cmd->fd[0]);
		}
		if (cmd->fd[1] != 1)
		{
			dup2(cmd->fd[1], 1);
			close(cmd->fd[1]);
		}
		return execvp(cmd->cmd[0], cmd->cmd);
	}
	close(cmd->fd[1]);
	return pid;
}

static int test()
{
	int pip[2];
	int save = 0;
	t_cmd *cmd = init();

	t_cmd *temp = cmd;

	while (temp)
	{
		pipe(pip);
		temp->fd[0] = save;
		save = pip[0];
		if (temp->next)
			temp->fd[1] = pip[1];
		else
			close(pip[1]);
		temp = temp->next;
	}
	temp = cmd;
	while (temp->next)
	{
		exec_cmd(temp);
		temp = temp->next;
	}
	if (temp->fd[0] != 0)
		dup2(temp->fd[0], 0);
	execvp(temp->cmd[0], temp->cmd);
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	pid_t pid;
	int status;
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
		test();
	else
		waitpid(-1, &status, 0);
	dprintf(2, "done with everything\n");

	return (0);













    // int fd[2];
    // pid_t pid;
    // pid_t pid2;

    // pipe(fd);
    // if ((pid = fork()) == 0) //Child process
    // {
    //     dup2(fd[1], STDOUT_FILENO);
    //     close(fd[1]);
    //     execve(program_3[0], program_3, NULL);
    // }
    // else if (pid > 0) //Parent process
    // {
    //     if ( (pid2 = fork()) == 0) {
    //         dup2(fd[0], STDIN_FILENO);
    //         close(fd[0]);
    //         execve(program_2[0], program_2, NULL);
    //     }
    // }
    // waitpid(pid, 0, 0);
    // waitpid(pid2, 0, 0);
    // return (EXIT_SUCCESS);
}

