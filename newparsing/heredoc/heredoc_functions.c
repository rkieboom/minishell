/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 00:23:24 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/25 17:45:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	heredoc_allocation(t_list *list, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (list->tokens[i].double_redirection_left)
		{
			list->tokens[i].heredoc = \
			ft_calloc(sizeof(t_heredoc), \
			list->tokens[i].double_redirection_left); //leak
			if (!list->tokens[i].heredoc)
				ft_ret_exit(1, 1);
		}
		i++;
	}
}

void	set_heredoc(t_list *list, int k)
{
	int	i;

	i = 0;
	heredoc_allocation(list, k);
	while (i < k)
	{
		if (list->tokens[i].double_redirection_left)
		{
			get_heredoc_q(list, i);
			get_heredoc_eof(list, i);
			get_heredoc_input(list, i);
			heredoc_parse(list, i);
		}
		i++;
	}
}
