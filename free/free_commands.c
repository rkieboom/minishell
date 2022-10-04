/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_commands.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/04 19:50:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 23:15:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_cmd(t_newcommand *temp, int j, int k)
{
	while (temp->command && temp->command[j])
	{
		free(temp->command[j]);
		j++;
	}
	if (temp->command)
		free(temp->command);
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
}

void	free_commands(t_list *list, t_newcommand *temp, \
						t_newcommand *temp2, int totalcommands)
{
	int	i;
	int	k;

	i = 0;
	while (totalcommands)
	{
		k = 0;
		temp = &list->cmd[i];
		while (temp)
		{
			temp2 = temp->next;
			free_cmd(temp, 0, k);
			temp = temp2;
			k++;
		}
		i++;
		totalcommands--;
	}
	free(list->cmd);
}
