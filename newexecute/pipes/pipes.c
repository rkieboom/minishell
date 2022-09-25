/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:17:04 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/23 17:06:25 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	init_vars(t_vars *var, t_newcommand *v)
{
	var->temp = v;
	var->i = 0;
	while (v)
	{
		v = v->next;
		var->i++;
	}
	var->size = var->i;
	var->i = 0;
	var->fd_stdin_cpy = dup(0);
	var->fd_stdout_cpy = dup(1);
}

static void	go(t_list *list, t_vars *vars)
{
	setup_pipes(vars);
	if (vars->temp->tokens && vars->temp->tokens->total > 0)
	{
		if (!redirections(list, vars->temp) && vars->temp->command)
			run_cmd_redir(list, vars->temp);
	}
	else
		run_cmd_redir(list, vars->temp);
	if (vars->temp->tokens && vars->temp->tokens->total > 0)
		reset_redirections(list, vars->temp);
	clear_pipes(vars);
}

void	ft_pipes(t_list *list, t_newcommand *v)
{
	t_vars	vars;

	init_vars(&vars, v);
	while (vars.temp)
	{
		if (get_last_redir(vars.temp, 0, vars.temp->tokens->total))
		{
			vars.temp = vars.temp->next;
			continue ;
		}
		if (vars.temp->tokens->heredoc)
		{
			setup_pipes(&vars);
			run_cmd_heredoc(list, vars.temp);
			clear_pipes(&vars);
		}
		else
			go(list, &vars);
		vars.i++;
		vars.size--;
		vars.temp = vars.temp->next;
	}
}
