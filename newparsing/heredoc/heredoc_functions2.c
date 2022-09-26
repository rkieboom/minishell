/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_functions2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 03:13:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/26 15:20:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	free_and_get_data(t_list *list, int k)
{
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = 0;
	}
	list->gnl.buf = readline("> ");
	if (!list->gnl.buf)
		list->gnl.buf = ft_strdup(list->tokens[k].heredoc->eof);
}

static void	allocate(t_heredoc_data **temp, t_heredoc_data **head)
{
	if (!*temp)
	{
		*temp = ft_calloc(sizeof(t_heredoc_data), 1);
		if (!*temp)
			ft_ret_exit(1, 1);
		*head = *temp;
	}
	else
	{
		(*temp)->next = ft_calloc(sizeof(t_heredoc_data), 1);
		if (!(*temp)->next)
			ft_ret_exit(1, 1);
		*temp = (*temp)->next;
	}
}

static void	set_heredoc_data(t_list *list, int k, int i)
{
	t_heredoc_data	*temp;
	t_heredoc_data	*head;

	temp = 0;
	head = 0;
	if (!list->tokens[k].heredoc->eof)
		return ;
	free_and_get_data(list, k);
	while (ft_strncmp(list->gnl.buf, \
	list->tokens[k].heredoc[i].eof, ft_strlen(list->tokens[k].heredoc[i].eof)))
	{
		allocate(&temp, &head);
		if (!temp)
			ft_ret_exit(1, 1);
		temp->str = ft_strdup(list->gnl.buf);
		free_and_get_data(list, k);
	}
	list->tokens[k].heredoc[i].data = head;
}

void	get_heredoc_q(t_list *list, int k)
{
	int	i;
	int	current;
	int	pos;

	i = 0;
	current = 0;
	while (i < list->tokens[k].total)
	{
		if (!ft_strncmp(list->tokens[k].token[i], "<<", 3))
		{
			pos = list->tokens[k].token_pos[i] + 1;
			if (!list->parse.commands[k][pos])
				return ;
			if (list->parse.commands[k][pos][0] == '\"' \
			|| list->parse.commands[k][pos][0] == '\'')
				list->tokens[k].heredoc[current].heredoc_q = 1;
			current++;
		}
		i++;
	}
}

void	get_heredoc_input(t_list *list, int k)
{
	int	i;
	int	length;

	i = 0;
	length = list->tokens[k].double_redirection_left;
	while (i < length)
	{
		set_heredoc_data(list, k, i);
		i++;
	}
}
