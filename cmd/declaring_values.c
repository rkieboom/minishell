/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   declaring_values.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 13:14:16 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/10 11:56:17 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		pipe_location(t_list *v, int k, int token_pos)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (i < v->tokens[k].total)
	{
		if (v->tokens[k].token[i][0] == '|')
		{
			if (len == token_pos)
				return (v->tokens[k].token_pos[i]);
			len++;
		}
		i++;
	}
	return (-1);
}

static void	first_cmd(t_list *v, t_newcommand *temp, int pipes, int k)
{
	int	i;
	int	j;

	i = 0;
	j = pipe_location(v, k, 0);
	if (j == -1)
		ft_error("Something went wrong in creating cmd!\n");
	temp->command = ft_calloc(j + 1, sizeof(char *));
	if (!temp->command)
		ft_error("Malloc failed!\n");
	while (j)
	{
		temp->command[i] = ft_strdup(v->parse.commands[k][i]);
		if (!temp->command[i])
			ft_error("Malloc failed!\n");
		j--;
		i++;
	}
}

static void	middle_cmd(t_list *v, t_newcommand *temp, int pipes, int k)
{
	int	i;
	int	j;
	int	l;

	i = pipe_location(v, k, pipes - 1);
	if (i == -1)
		ft_error("Something went wrong in creating cmd!\n");
	j = pipe_location(v, k, pipes);
	if (j == -1)
		ft_error("Something went wrong in creating cmd!\n");
	temp->command = ft_calloc(j - i, sizeof(char *));
	if (!temp->command)
		ft_error("Malloc failed!\n");
	j = j - i - 1;
	i++;
	l = 0;
	while (j)
	{
		temp->command[l] = ft_strdup(v->parse.commands[k][i]);
		if (!temp->command[l])
			ft_error("Malloc failed!\n");
		l++;
		i++;
		j--;
	}
	
}

static void	last_cmd(t_list *v, t_newcommand *temp, int pipes, int k)
{
	int i;
	int	j;
	int l;
	
	i = 0;
	j = pipe_location(v, k, pipes);
	if (!j)
		ft_error("Something went wrong in creating cmd!\n");
	while (v->parse.commands[k][i + j])
		i++;
	i += j;
	temp->command = ft_calloc(i - j, sizeof(char *));
	if (!temp->command)
		ft_error("Malloc failed!\n");
	j = i - j - 1;
	i = 0;
	l = pipe_location(v, k, pipes) + 1;
	while (j)
	{
		temp->command[i] = ft_strdup(v->parse.commands[k][l + i]);
		if (!temp->command[i])
			ft_error("Malloc failed!\n");
		i++;
		j--;
	}
}

void	declaring_values(t_list *v, t_newcommand *pipes_cmd, int pipes, int k)
{
	int	i;
	int j;
	t_newcommand *temp;

	temp = pipes_cmd;
	i = 0;
	while (pipes + 1)
	{
		temp->id = i;
		if (i == 0)
			first_cmd(v, temp, pipes, k);
		else if (pipes == 0)
			last_cmd(v, temp, v->tokens[k].pipe - 1, k);
		else
			middle_cmd(v, temp, i, k);
		i++;
		pipes--;
		if (pipes >= 0)
		{
			temp->next = ft_calloc(1, sizeof(t_newcommand));
			if (!temp->next)
				ft_error("Malloc failed!\n");
			temp = temp->next;
		}
	}
}