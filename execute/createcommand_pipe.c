/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   createcommand_pipe.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/13 00:50:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/02/06 14:24:27 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static	int	get_pipe_pos(t_list *v, int k, int len)
{
	int	i;

	i = 0;
	while (v->tokens[k].token[i])
	{
		if (v->tokens[k].token[i][0] == '|')
		{
			if (len == i)
				return (v->tokens[k].token_pos[i]);
		}
		i++;
	}
	return (-1);
}

static void	create_command(t_list *v, int k,
int i, int wordcount, t_pipecommand *temp)
{
	int	j;

	j = 0;
	if (wordcount > 0)
	{
		temp->command = ft_calloc(wordcount + 1, sizeof(char*));
		if (!temp->command)
			ft_exit(1, 1);
	}
	if (i == 0)
	{
		while (wordcount)
		{
			temp->command[i] = ft_strdup(v->parse.commands[k][i]);
			if (!temp->command[i])
				ft_exit(1, 1);
			i++;
			wordcount--;
		}
	}
	else
	{
		i = get_pipe_pos(v, k, i - 1);
		i++;
		if (wordcount == -1)
		{
			wordcount = i;
			while (v->parse.commands[k][wordcount])
				wordcount++;
			wordcount -= i;
			temp->command = ft_calloc(wordcount + 1, sizeof(char*));
			if (!temp->command)
				ft_exit(1, 1);
		}
		while (wordcount) //echo "Hallo" | pwd | echo "Bye"
		{
			temp->command[j] = ft_strdup(v->parse.commands[k][i]);
			if (!temp->command[j])
				ft_exit(1, 1);
			i++;
			j++;
			wordcount--;
		}
	}
}

static void create_pipe_command(t_list *v, int k)
{
	int				i;
	int				j;
	int				wordcount;
	int				pipes;
	t_pipecommand	*temp;

	pipes = v->tokens[k].pipe;
	v->pipecommand = ft_calloc(1, sizeof(t_pipecommand));
	temp = v->pipecommand;
	i = 0;
	j = 0;
	while (pipes + 1)
	{
		if (i == 0)
			wordcount = get_pipe_pos(v, k, i);
		else if (pipes == 0)
		{
			create_command(v, k, i, -1, temp);
			break ;
		}
		else
			wordcount = get_pipe_pos(v, k, i) - get_pipe_pos(v, k, i - 1) - 1;
		create_command(v, k, i, wordcount, temp);
		pipes--;
		i++;
		if (pipes + 1 > 0)
		{
			temp->next = ft_calloc(1, sizeof(t_pipecommand));
			temp = temp->next;
		}
	}
}

void	createcommand_pipe(t_list *v, int k)
{
	create_pipe_command(v, k);
	exec_command_pipes(v, k);
}
