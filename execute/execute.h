/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 15:33:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/12 15:51:36 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include "../commands/commands.h"
# include "../header.h"

void	run_cmd(t_list *list, char **cmd);
void	run_cmd_tokens(t_list *list, t_newcommand *cmd);

int		setup_tokens_child(t_list *list, t_newcommand *cmd);
void	clean_tokens_child(t_list *list, t_newcommand *command);

void	setup_pipes(t_newcommand *cmd);
void	clean_pipes(t_newcommand *cmd);

int		loop_over_redirs(t_newcommand *v, int i, int total);

int		redir_left(t_newcommand *v);
void	redir_right(t_newcommand *v);

char	**set_cmd(t_newcommand *cmd);

void	setup_single_cmd(t_list *list, t_newcommand *cmd);
void	setup_pipe_cmd(t_list *list, t_newcommand *cmd);

#endif