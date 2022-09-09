/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 00:23:24 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/08 01:12:30 by rkieboom      ########   odam.nl         */
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
			list->tokens[i].double_redirection_left);
			if (!list->tokens[i].heredoc)
				ft_ret_exit(1, 1);
		}
		i++;
	}
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
			if (list->parse.commands[k][pos][0] == '\"' \
			|| list->parse.commands[k][pos][0] == '\'')
				list->tokens[k].heredoc[current].heredoc_q = 1;
			current++;
		}
		i++;
	}
}


static void	free_and_get_data(t_list *list)
{
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = 0;
	}
	list->gnl.buf = readline("> ");
}

static void	set_heredoc_data(t_list *list, int k, int i)
{
	t_heredoc_data	*temp;
	t_heredoc_data	*head;

	temp = 0;
	free_and_get_data(list);
	while (ft_strncmp(list->gnl.buf, \
	list->tokens[k].heredoc[i].eof, ft_strlen(list->tokens[k].heredoc[i].eof)))
	{
		if (!temp)
		{
			temp = ft_calloc(sizeof(t_heredoc_data), 1);
			head = temp;
		}
		else
		{
			temp->next = ft_calloc(sizeof(t_heredoc_data), 1);
			temp = temp->next;
		}
		if (!temp)
			ft_ret_exit(1, 1);
		temp->str = ft_strdup(list->gnl.buf);
		free_and_get_data(list);
	}
	list->tokens[k].heredoc[i].data = head;
}

static void	get_heredoc_input(t_list *list, int k)
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

static void	get_heredoc_eof(t_list *list, int k)
{
	int	total;
	int	c;
	int	token_c;

	c = 0;
	token_c = 0;
	total = list->tokens[k].double_redirection_left;
	while (total)
	{
		if (!ft_strncmp(list->tokens[k].token[token_c], "<<", 3))
		{
			list->tokens[k].heredoc[c].eof = \
			list->parse.commands[k][list->tokens[k].token_pos[token_c] + 1];
			total--;
			c++;
		}
		token_c++;
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
		}
		i++;
	}
}
