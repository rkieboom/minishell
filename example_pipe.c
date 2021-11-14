/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   example_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 16:13:39 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/14 19:05:01 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	struct rusage rusage;

	pid_t pid;
	int pipes[2];
	int FD_STDIN_CPY = dup(0);
	int	FD_STDOUT_CPY = dup(1);
	int	FD_STDIN_FILE;
	int	FD_STDOUT_FILE;
	int	FD_STDIN_PIPE;
	int	FD_STDOUT_PIPE;

	char **cmd;
	char **cmd2;

	int status;
	int options;

	if (pipe(pipes) < 0)
		exit(-1);

	cmd = malloc(sizeof(char *) * 3);
	cmd2 = malloc(sizeof(char *) * 3);

	cmd[0] = strdup("/bin/cat");
	cmd[1] = strdup("Makefile");
	cmd[2] = 0;

	cmd2[0] = strdup("/usr/bin/grep");
	cmd2[1] = strdup("@");
	cmd2[2] = 0;


	//CMD1 | CMD2
	//Set pipe CMD2
	close(1);
	dup2(pipes[1], 1);
	pid = fork();
	//CMD1
	if (pid == 0)
	{
		execve(cmd[0], cmd, envp);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);

	//CMD2
	close(pipes[1]);
	dup2(FD_STDOUT_CPY, 1);
	close(0);
	dup2(pipes[0], 0);
	pid = fork();
	if (pid == 0)
	{
		execve(cmd2[0], cmd2, envp);
		exit(0);
	}
	else
	{

		dprintf(1, "test");
		waitpid(pid, &status, 0);
	}
	close(pipes[0]);
	dup2(FD_STDIN_CPY, 0);
	return (0);
}