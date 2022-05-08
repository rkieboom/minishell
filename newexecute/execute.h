/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:59:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/07 15:59:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../header.h"
# include "../commands/commands.h"

// typedef struct s_pipe_command
// {
// 	t_newcommand *temp;
// 	int	pid;
// 	int	totalcommands;
// 	int	i;
// 	int	fd_stdin_cpy;
// 	int	fd_stdout_cpy;
// 	int	newpipes[2];
// 	int	oldpipe;
// }				t_pipe_command;

// void	checkcommand(t_list	*list, int k);
// void	createcommand_pipe(t_list *v, int k);
// void	here_document(char *cmd, char *end);

// int		command_is_builtin(char *str);
// int		set_redirection(t_list *list, int k);
// void	exec_command_pipes(t_list *v, int k);
// void	execute_builtin_pipe_cmd(t_list *v, t_pipe_command *cmd);

int		redirections(t_list *list, t_newcommand *v);
void	reset_redirections(t_list *list, t_newcommand *v);

void	single_redirection_right(t_newcommand *v, int i);
int		single_redirection_left(t_newcommand *v, int i);
void	double_redirection_right(t_newcommand *v, int i);

void	run_commands(t_list *list, t_newcommand *v);
void	run_cmd_redir(t_list *list, t_newcommand *cmd);

#endif