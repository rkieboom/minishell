/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkcommand_pipe.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/13 00:50:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/01/27 21:19:17 by rkieboom      ########   odam.nl         */
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
	return (-1);
}

static void	create_command(t_list *v, int k, int i, int wordcount, t_pipecommand *temp)
{
	int j;

	j = 0;
	if (wordcount > 0)
	{
		temp->command = ft_calloc(wordcount + 1, sizeof(char*));
		if (!temp->command)
			ft_exit(1, 1);
	}
	if (i == 0)		//if i == 0 its the first command so it can begin from the start
		while (wordcount)
		{
			temp->command[i] = ft_strdup(v->parse.commands[k][i]);
			if (!temp->command[i])
				ft_exit(1, 1);
			i++;
			wordcount--;
		}
	else
	{
		i = get_pipe_pos(v, k, i - 1); //i == first word after pipe
		if (wordcount == -1)//voor als er geen pipes zijn kijken we gewoon hoeveel worden er na de laatste pipe waren
		{
			i++;
			wordcount = i;
			while(v->parse.commands[k][wordcount])
				wordcount++;
			wordcount -= i;
			temp->command = ft_calloc(wordcount + 1, sizeof(char*));
			if (!temp->command)
				ft_exit(1, 1);
		}
		while (wordcount) //wordcount is the amount of words
		{
			temp->command[j] = ft_strdup(v->parse.commands[k][i]);
			if (!temp->command[i])
				ft_exit(1, 1);
			i++;
			j++;
			wordcount--;
		}
	}
}

static void create_pipe_command(t_list *v, int k)
{
	int i;
	int j;
	int wordcount;
	int pipes = v->tokens[k].pipe;
	t_pipecommand *temp;

	v->pipecommand = ft_calloc(1, sizeof(t_pipecommand));
	temp = v->pipecommand;

	i = 0;
	j = 0;
	while (pipes + 1)
	{
		if (i == 0)
			wordcount = get_pipe_pos(v, k, i); //getting the amount of words before pipe
		else if (pipes == 0)
		{
			create_command(v, k, i, -1, temp); //nu zijn er geen pipes meer
			break ;
		}
		else
			wordcount = get_pipe_pos(v, k, i) - get_pipe_pos(v, k, i - 1); //getting the amount of words between pipes
		create_command(v, k, i, wordcount, temp);// creating the command
		pipes--;
		i++;
		if (pipes + 1 > 0) //allocating next one if needed
		{
			temp->next = ft_calloc(1, sizeof(t_pipecommand));
			temp = temp->next;
		}
	}

	while(1);
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