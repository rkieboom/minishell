/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 13:49:04 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/30 17:54:24 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define STDIN 0
#define STDOUT 1
#define STDERROR 2

// CPP program to illustrate dup() 
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//STDIN
//STDOUT
//STDERROR

int main(int argc, char **argv, char **envp)
{
	int fd = open("test.homo", O_WRONLY | O_APPEND |O_CREAT, 0644);
	int STDOUT_CPY;
	int FD_CPY;

	STDOUT_CPY = dup(1);
	FD_CPY = dup(fd);
	dup2(fd, 1);
	pid_t PID;
	char *newargv[] = {"/bin/echo", "hello", "world", ">", NULL }; "echo" "\"hallo ik ben sid\">test.homo"
	
	PID = fork();
		if (PID < 0)
			exit(1);
		if (PID == 0)
		{
			execve(newargv[0], newargv, envp);
			fflush(NULL);
		}	
		else
		{
			wait(NULL);
			while(1);
		}
}