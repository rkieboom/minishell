/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:33:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/20 01:44:13 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "../builtin/commands.h"
# include "../header.h"

void	run_cmd(t_list *list, char **cmd);
void	run_cmd_tokens(t_list *list, t_newcommand *cmd);

int		setup_tokens_child(t_list *list, t_newcommand *cmd);
void	clean_tokens_child(t_list *list, t_newcommand *command);

void	setup_pipes(t_newcommand *cmd);

void	heredoc_set_pipe(t_heredoc *heredoc, t_heredoc_data *data);
int		loop_over_redirs(t_newcommand *v, int i, int total);

int		redir_left(t_newcommand *v);
int		redir_right(t_newcommand *v);

char	**set_cmd(t_newcommand *cmd);

void	setup_builtin(t_list *list, \
t_newcommand *cmd, char **command, int token_exist);
void	setup_single_cmd(t_list *list, t_newcommand *cmd);
void	setup_pipe_cmd(t_list *list, t_newcommand *cmd);

void	setup_pipe_stuff(t_newcommand *cmd);
int		exit_status(int status);

#endif