/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:59:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/19 16:53:14 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../header.h"
# include "../commands/commands.h"

void	ft_pipes(t_list *list, t_newcommand *v);

int		redirections(t_list *list, t_newcommand *v);
void	reset_redirections(t_list *list, t_newcommand *v);

void	single_redirection_right(t_newcommand *v, int i);
int		single_redirection_left(t_newcommand *v, int i);
void	double_redirection_right(t_newcommand *v, int i);

void	run_commands(t_list *list, t_newcommand *v);
void	run_cmd_redir(t_list *list, t_newcommand *cmd);

#endif