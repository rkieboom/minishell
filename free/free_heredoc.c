/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_heredoc.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 04:04:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/25 23:01:09 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

static void	free_heredoc_data(t_heredoc_data *data)
{
	t_heredoc_data	*tmp;

	while (data)
	{
		if (data->str)
			free(data->str);
		tmp = data->next;
		free(data);
		data = tmp;
	}
}

void	free_heredoc(t_list *list, int totalcommands)
{
	int				i;
	int				j;

	i = 0;
	while (totalcommands)
	{
		j = 0;
		while (list->tokens != NULL && &list->tokens[i] != NULL && \
		list->tokens[i].double_redirection_left)
		{
			if (list->tokens != NULL && &list->tokens[i] != NULL && \
			list->tokens[i].heredoc && list->tokens[i].heredoc[j].data)
				free_heredoc_data(list->tokens[i].heredoc[j].data);
			list->tokens[i].double_redirection_left--;
			j++;
		}
		if (list->tokens != NULL && \
		&list->tokens[i] != NULL && list->tokens[i].heredoc)
			free(list->tokens[i].heredoc);
		i++;
		totalcommands--;
	}
}
