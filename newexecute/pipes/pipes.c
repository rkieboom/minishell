/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:17:04 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/05 13:27:26 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	init_vars(t_vars *var, t_newcommand *v)
{
	var->temp = v;
	var->i = 0;
	var->error = 0;
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

static void	close_fds(t_vars *var)
{
	if (var->fd_stdin_cpy >= 0)
		close(var->fd_stdin_cpy);
	if (var->fd_stdout_cpy >= 0)
		close(var->fd_stdout_cpy);
}

static void	go(t_list *list, t_vars *vars)
{
	setup_pipes(vars);
	if (vars->temp->tokens && vars->temp->tokens->total > 0)
	{
		if (vars->temp->tokens->heredoc)
			write_to_pipe(vars->temp->tokens->heredoc, \
			vars->temp->tokens->heredoc->data);
		if (!redirections(list, vars->temp) && \
		vars->temp->command && vars->error == 0)
			run_cmd_redir(list, vars->temp);
	}
	else if (vars->error == 0)
		run_cmd_redir(list, vars->temp);
	if (vars->temp->tokens && vars->temp->tokens->total > 0)
		reset_redirections(list, vars->temp);
	if (vars->temp->tokens->heredoc)
		clear_pipe_heredoc(vars->temp->tokens->heredoc);
	clear_pipes(vars);
	vars->error = 0;
}

void	ft_pipes(t_list *list, t_newcommand *v)
{
	t_vars	vars;

	init_vars(&vars, v);
	while (vars.temp)
	{
		if (get_last_redir(vars.temp, 0, vars.temp->tokens->total))
		{
			vars.error = 1;
			vars.temp->tokens->error = 1;
		}
		else
			go(list, &vars);
		vars.i++;
		vars.size--;
		vars.temp = vars.temp->next;
		vars.error = 0;
	}
	close_fds(&vars);
}
