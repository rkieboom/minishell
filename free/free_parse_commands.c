/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_parse_commands.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:34:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/21 14:56:52 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	free_parse_commands(t_list *list)
{
	int	i;
	int	j;
	int totalcommands;

	i = 0;
	while (list->parse.commands[i])
		i++;
	totalcommands = i;
	i = 0;
	while (list->parse.commands[i])
	{
		while(list->tokens[i].total)
		{
			free(list->tokens[i].token[list->tokens[i].total - 1]);
			list->tokens[i].total--;
		}
		free(list->tokens[i].token);
		free(list->tokens[i].token_pos);
		i++;
	}
	i = 0;
	if (list->parse.commands)
	{
		while (list->parse.commands[i])
		{
			j = 0;
			while (list->parse.commands[i][j])
			{
				free(list->parse.commands[i][j]);
				j++;
			}
			free(list->parse.commands[i]);
			i++;
		}
		free(list->parse.commands);
	}
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = NULL;
	}
	free(list->tokens);
	//freeing new tokens
	i = 0;
	int k = 0;
	t_newcommand *temp;
	t_newcommand *temp2;
	while (totalcommands)
	{
		temp = &list->cmd[i];
		while (temp)
		{
			temp2 = temp->next;
			//freeing commands
			j = 0;
			while (temp->command[j])
			{
				free(temp->command[j]);
				j++;
			}
			free(temp->command);
			//freeing commands
			if (temp->tokens && temp->tokens->total == 0)
				free(temp->tokens);
			else if (temp->tokens)
			{	
				j = 0;
				while (temp->tokens->token[j])
				{
					free(temp->tokens->token[j]);
					j++;
				}
				free(temp->tokens->token);
				free(temp->tokens->token_pos);
				free(temp->tokens);
			}
			if (k != 0)
				free(temp);
			temp = temp2;
			k++;
		}
		i++;
		totalcommands--;
	}
	free(list->cmd);
}
