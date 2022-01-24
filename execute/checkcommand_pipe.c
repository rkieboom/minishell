/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkcommand_pipe.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/13 00:50:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/01/14 00:22:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static	int	get_pipe_pos(t_list *v, int k, int len)
{
	int i;

	i = 0;
	while (v->tokens[k].token[i])
	{
		if (v->tokens[k].token[i][0] == '|')
		{
			if (len == i)
				return (v->tokens[k].token_pos[i]);
			len++;
		}
		i++;
	}
}

static void create_command(t_list *v, int k, t_pipecommand *temp, int c)
{
	int totalcommands;
	int i;

	i = 0;
	totalcommands = v->tokens[k].token_pos[c+1];
	if (totalcommands != 0)
	{
		totalcommands -= v->tokens[k].token_pos[c];
		c = v->tokens[k].token_pos[c] + 1;
		while (totalcommands)
		{
			temp->command[i] = ft_strdup(v->parse.commands[k][c]);
			totalcommands--;
			c++;
			i++;
		}
	}
	else
	{
		c = v->tokens[k].token_pos[c] + 1;
		while (v->parse.commands[k][c])
		{
			temp->command[i] = ft_strdup(v->parse.commands[k][c]);
			c++;
			i++;
		}
	}
}

static void create_pipe_command(t_list *v, int k)
{
	int i;
	int totalcommands;
	int totalpipes;
	int c;
	t_pipecommand *temp;

	i = 0;
	totalpipes = v->tokens[k].pipe;
	v->pipecommand = ft_calloc(1, sizeof(t_pipecommand));
	temp = v->pipecommand;
	c = 0;
	if (!temp)
		ft_exit(1, 1);
	while (totalpipes)
	{
		totalcommands = v->tokens[k].token_pos[c] - 1;//checken of de token == |
		temp->command = ft_calloc(totalcommands, sizeof(t_pipecommand));
		if (!temp->command)
			ft_exit(1, 1);
		create_command(v, k, temp, c);
		
		
		i++;
		c++;
		temp->next = ft_calloc(1, sizeof(t_pipecommand));
		temp = temp->next;
		totalpipes--;
	}
	// while (v->parse.commands[k][i])
	// {
	// 	temp
	// 	i++;
	// }
	
}

void	checkcommand_pipe(t_list *v, int k)
{
	int i = 0;
	create_pipe_command(v, k);
	t_pipecommand *temp;

	temp = v->pipecommand;
	while (temp)
	{
		while (temp->command[i])
		{
			if (!temp->command[i+1])
				printf("[%s]\n", temp->command[i]);
			else
				printf("[%s]-", temp->command[i]);
			i++;
		}
		i = 0;
		temp = temp->next;
	}
}