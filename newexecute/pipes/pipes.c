/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:17:04 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/19 19:08:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void init_vars(t_vars *var, t_newcommand *v)
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
	var->FD_STDIN_CPY = dup(0);
	var->FD_STDOUT_CPY = dup(1);
}

void	ft_pipes(t_list *list, t_newcommand *v)
{
	t_vars var;

	init_vars(&var, v);
	while (var.temp)
	{
		setup_pipes(&var);
		if (var.temp->tokens && var.temp->tokens->total > 0)
			redirections(list, var.temp);
		if (var.temp->command)
			run_cmd_redir(list, var.temp);
		if (var.temp->tokens && var.temp->tokens->total > 0)
			reset_redirections(list, var.temp);
		clear_pipes(&var);
		var.i++;
		var.size--;
		var.temp = var.temp->next;
	}
}
