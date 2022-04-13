/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   example_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 16:13:39 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/10 17:52:54 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

void	test(char **envp)
{
	int		pid;
	int		i = 0;

	int		size;
	int		FD_STDIN_CPY = dup(0);
	int		FD_STDOUT_CPY = dup(1);
	
	int		newpipes[2];
	int		oldpipes;
	char	***cmd;

	cmd = malloc(sizeof(char **) * 6);
	cmd[5] = 0;

	cmd[0] = malloc(sizeof(char *) * 3);
	cmd[1] = malloc(sizeof(char *) * 3);
	cmd[2] = malloc(sizeof(char *) * 3);
	cmd[3] = malloc(sizeof(char *) * 2);
	cmd[4] = malloc(sizeof(char *) * 3);

	cmd[0][0] = strdup("/bin/cat");
	cmd[0][1] = strdup("Makefile");
	cmd[0][2] = 0;

	cmd[1][0] = strdup("/usr/bin/grep");
	cmd[1][1] = strdup("@");
	cmd[1][2] = 0;

	cmd[2][0] = strdup("/usr/bin/grep");
	cmd[2][1] = strdup("$");
	cmd[2][2] = 0;

	cmd[3][0] = strdup("/usr/bin/sort");
	cmd[3][1] = 0;

	cmd[4][0] = strdup("/usr/bin/grep");
	cmd[4][1] = strdup("r");
	cmd[4][2] = 0;

	size = 5;

	while (size)
	{
		if (size > 1)
		{
			if (pipe(newpipes) < 0)
				exit(1);
		}
		if (i == 0) //de eerste keer, Alleen schrijven naar pipe
		{
			close(1);
			dup2(newpipes[1], 1);
		}
		else if (size == 1) //de laatste keer, alleen lezen uit pipes
		{
			close(0);
			dup2(oldpipes, 0);
		}
		else //tussenin allebei lezen en schrijven uit pipes
		{
			close(1);
			close(0);
			dup2(oldpipes, 0);
			dup2(newpipes[1], 1);
		}

		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			execve(cmd[i][0], cmd[i], envp);
			exit(1);
		}
		else
			wait(NULL);


		if (i == 0) //de eerste keer, Alleen schrijven naar pipe
		{
			close(newpipes[1]);
			oldpipes = dup(newpipes[0]);
			close(newpipes[0]);
			dup2(FD_STDOUT_CPY, 1);
			FD_STDOUT_CPY = dup(1);
		}
		else if (size == 1) //de laatste keer, alleen lezen uit pipes
		{
			close(oldpipes);
			dup2(FD_STDIN_CPY, 0);
			close(FD_STDOUT_CPY);
		}
		else //tussenin allebei lezen en schrijven uit pipes
		{
			close(oldpipes);
			close(newpipes[1]);
			oldpipes = dup(newpipes[0]);
			close(newpipes[0]);
			dup2(FD_STDIN_CPY, 0);
			dup2(FD_STDOUT_CPY, 1);
			FD_STDOUT_CPY = dup(1);
			FD_STDIN_CPY = dup(0);
		}
		i++;
		size--;
	}


}

int	main(int argc, char **argv, char **envp)
{
	test(envp);

	return (0);
}
