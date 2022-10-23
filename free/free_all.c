/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_all.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:34:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 01:36:19 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_tokens(t_list *list)
{
	int	i;

	i = 0;
	while (list->parse.commands[i])
	{
		while (list->tokens[i].total)
		{
			free(list->tokens[i].token[list->tokens[i].total - 1]);
			list->tokens[i].total--;
		}
		free(list->tokens[i].token);
		free(list->tokens[i].token_pos);
		i++;
	}
	free(list->tokens);
}

static void	free_parse_commands(t_list *list)
{
	int	i;
	int	j;

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
}

static void	free_gnl_buf(t_list *list)
{
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = NULL;
	}
}

//Frees all stuff
void	free_all(t_list *list)
{
	int	totalcommands;

	totalcommands = 0;
	while (list->parse.commands[totalcommands])
		totalcommands++;
	free_gnl_buf(list);
	free_heredoc(list, totalcommands);
	free_tokens(list);
	free_parse_commands(list);
	free_commands(list, 0, 0, totalcommands);
	list->cmd = 0;
	list->tokens = 0;
}
