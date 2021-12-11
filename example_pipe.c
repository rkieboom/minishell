/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   example_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 16:13:39 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/12/11 17:53:34 by rkieboom      ########   odam.nl         */
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
	int FD_STDIN_CPY = -1;
	int	FD_STDOUT_CPY = -1;
	int	FD_STDIN_FILE;
	int	FD_STDOUT_FILE;
	int	FD_STDIN_PIPE;
	int	FD_STDOUT_PIPE;

	char ***cmd;
	char **cmd2;

	int status;
	int options;

	// if (pipe(pipes) < 0)
	// 	exit(-1);

	//CMD1 | CMD2
	//Set pipe CMD2
	// close(1); //close STDIN
	
	//pipes[0] = read
	//pipes[1] = write

	// dup2(pipes[1], 1); //set Pipes[1] to stdin
	// pid = fork();//fork
	// //CMD1
	// if (pid == 0)
	// {
	// 	execve(cmd[0], cmd, envp);
	// 	exit(0);
	// }
	// else
	// 	waitpid(pid, &status, 0);

	// //CMD2
	// close(pipes[1]);
	// dup2(FD_STDOUT_CPY, 1);
	// close(0);
	// dup2(pipes[0], 0);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	execve(cmd2[0], cmd2, envp);
	// 	exit(0);
	// }
	// else
	// {

	// 	dprintf(1, "test");
	// 	waitpid(pid, &status, 0);
	// }
	// close(pipes[0]);
	// dup2(FD_STDIN_CPY, 0);
		
	cmd = malloc(sizeof(char **) * 4);
	cmd[3] = 0;

	cmd[0] = malloc(sizeof(char *) * 3);
	cmd[1] = malloc(sizeof(char *) * 3);
	cmd[2] = malloc(sizeof(char *) * 3);

	cmd[0][0] = strdup("/bin/cat");
	cmd[0][1] = strdup("Makefile");
	cmd[0][2] = 0;

	cmd[1][0] = strdup("/usr/bin/grep");
	cmd[1][1] = strdup("@");
	cmd[1][2] = 0;

	cmd[2][0] = strdup("/usr/bin/grep");
	cmd[2][1] = strdup("$");
	cmd[2][2] = 0;


	int i = 0;
	int size = 3;
	int newpipes[2];
	int oldpipes[2];
	while (size)
	{
		if (size > 1)
		{
			if (pipe(newpipes) < 0)
				exit(-1);
		}
		if (FD_STDIN_CPY == -1)
			FD_STDIN_CPY = dup(0);
		if (FD_STDOUT_CPY == -1)
			FD_STDOUT_CPY = dup(1);
		if (i == 0)//de eerste, alleen schrijven
		{
			close(1);
			dup2(newpipes[1], 1);
		}
		else if (size == 1)//de laatste, alleen lezen
		{
			close(0);
			dup2(oldpipes[0], 0);
		}
		else //Tussen in lezen en schrijven
		{
			close(0);
			close(1);
			dup2(oldpipes[0], 0);
			dup2(newpipes[1], 1);
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)																//NEW PROC
		{
			execve(cmd[i][0], cmd[i], envp);											//EXECVE
			exit(0);
		}
		else
			wait(NULL);
		if (i == 0) 
		{
			close(newpipes[1]);//close newpipe[write]
			oldpipes[0] = dup(newpipes[0]);
			close(newpipes[0]);
			// dup2(newpipes[0], oldpipes[0]);//zet newpipe[read] naar oldpipe[read]
			dup2(FD_STDOUT_CPY, 1);//zet STDOUT_CP naar STDOUT
			FD_STDOUT_CPY = dup(1);//nieuwe kopie van STDOUT
		}
			// dup2(FD_STDIN_CPY, 0);
			// FD_STDIN_CPY = -1; //op het hele einde
		if (size == 1)
		{
			close(oldpipes[0]); //close oldpipe[read]
			dup2(FD_STDIN_CPY, 0);//zet STDIN terug
			close(FD_STDOUT_CPY); //close STDOUT_CPY omdat het de laatste is
		}
		else
		{
			close(oldpipes[0]);
			oldpipes[0] = dup(newpipes[0]);
			close(newpipes[0]);
			close(newpipes[1]);
			dup2(FD_STDIN_CPY, 0);
			dup2(FD_STDIN_CPY, 1);
			FD_STDIN_CPY = dup(0);
			FD_STDOUT_CPY = dup(1);
		}
		size--;
		i++;
	}
	return (0);
}