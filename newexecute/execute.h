/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:59:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/23 17:36:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../header.h"
# include "../commands/commands.h"

void	ft_pipes(t_list *list, t_newcommand *v);

int		redirections(t_list *list, t_newcommand *v);
int		set_redir(t_list *list, t_newcommand *v);
void	reset_redirections(t_list *list, t_newcommand *v);
char	**set_cmd(t_newcommand *cmd);

void	single_redirection_right(t_newcommand *v, int i);
int		single_redirection_left(t_newcommand *v, int i);
void	double_redirection_right(t_newcommand *v, int i);
void	double_redirection_left(t_newcommand *v, int i);
int		get_last_redir(t_newcommand *v, int i, int total);

void	run_cmd(t_list *list, char **cmd);
void	run_cmd_redir(t_list *list, t_newcommand *cmd);
void	run_cmd_heredoc(t_list *list, t_newcommand *cmd);

#endif
