/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 12:18:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/21 17:50:28 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	heredoc_parse_str(t_list *list, t_heredoc *heredoc)
{
	int				i;
	int				newlength;
	t_heredoc_data	*temp;

	i = 0;
	temp = heredoc->data;
	while (temp != NULL)
	{
		while (temp != NULL && !ft_strchr(temp->str, '$'))
			temp = temp->next;
		if (!temp)
			return ;
		newlength = heredoc_get_str_len(list, temp->str);
		temp->str = heredoc_create_str(list, temp->str, newlength);
		i++;
		temp = temp->next;
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
