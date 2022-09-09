/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/08 17:23:55 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/09 00:04:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>


char *add_newline(char *str)
{
	char	*newstr;
	int		length;

	length = strlen(str);
	newstr = calloc(length + 2, sizeof(char));
	if (!newstr)
		return (0);
	strcpy(newstr, str);
	newstr[length] = '\n';
	newstr[length + 1] = 0;
	free(str);
	return (newstr);
}

int	main(int argc, char **argv, char **envp)
{
	char buf[255];
	char *input;
	char *input2;
	char *input3;
	
	int FD_STDIN_CPY = dup(0);

	char **command;

	command = calloc(2, sizeof(char *));
	command[0] = strdup("/bin/cat");
	command[1] = 0;

	int pipes[2];

	if (pipe(pipes) < 0)
		exit(1);

	//reading input and putting it in pipe
	// input[read(0, input, 255)] = 0;
	// input2[read(0, input2, 255)] = 0;
	// input3[read(0, input3, 255)] = 0;
	input = readline("> ");
	input2 = readline("> ");
	input3 = readline("> ");
	input = add_newline(input);
	input2 = add_newline(input2);
	input3 = add_newline(input3);
	write(pipes[1], input, strlen(input));
	write(pipes[1], input2, strlen(input2));
	write(pipes[1], input3, strlen(input3));
	
	close(pipes[1]);
	free(input);
	free(input2);
	free(input3);
	input = 0;

	//getting info out the pipe and printing it
	// buf[read(pipes[0], buf, 255)] = 0;
	// close(pipes[0]);

	//set FD's
	close(0);
	dup2(pipes[0], 0);
	printf("Now we run the command\n");

	pid_t f = fork();
	printf("f = [%i]\n",f);
	if (f == 0)
	{
		printf("in the command now\n");
		execve(command[0], command, envp);
		exit(1);
	}
	else
		waitpid(f, 0, 0);

	//reset FD's
	// printf("\n");
	// fflush(0);
	close(0);
	dup2(FD_STDIN_CPY, 0);


	printf("command done!\n");
	// printf("Written string = %s\n", buf);
}
