/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 12:18:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/19 17:22:49 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	heredoc_parse_str(t_list *list, t_heredoc *heredoc) //double $$ or space ?+?
{
	int	i;
	int	newlength;

	i = 0;
	while (heredoc->data != NULL)
	{
		while (heredoc->data != NULL && !ft_strchr(heredoc->data->str, '$'))
			heredoc->data = heredoc->data->next;
		if (!heredoc->data)
			return ;
		newlength = heredoc_get_str_len(list, heredoc->data->str, heredoc);
		if (!heredoc->syntax_error)
			heredoc->data->str = heredoc_create_str(list, heredoc, heredoc->data->str, newlength);
		i++;
		heredoc->data = heredoc->data->next;
	}
}

void	heredoc_parse(t_list *list, int k)
{
	int	i;

	i = 0;
	while (i < list->tokens[k].double_redirection_left)
	{
		if (list->tokens[k].heredoc[i].heredoc_q == 0)
			heredoc_parse_str(list, &list->tokens[k].heredoc[i]);
		i++;
	}
}
