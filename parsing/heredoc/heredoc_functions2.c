/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_functions2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 03:13:14 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 00:23:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	free_and_get_data(t_list *list, int k, int i)
{
	if (list->gnl.buf)
	{
		free(list->gnl.buf);
		list->gnl.buf = 0;
	}
	list->gnl.buf = readline("> ");
	if (!list->gnl.buf)
		list->gnl.buf = ft_strdup(list->tokens[k].heredoc[i].eof);
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

//Saving the actual data
static void	set_heredoc_data(t_list *list, int k, int i)
{
	t_heredoc_data	*temp;
	t_heredoc_data	*head;

	temp = 0;
	head = 0;
	if (!list->tokens[k].heredoc->eof)
		return ;
	signal(SIGINT, signal_handler_hdoc);
	signal(SIGQUIT, SIG_IGN);
	if (g_global.heredoc_break == 1)
		return ;
	free_and_get_data(list, k, i);
	while (ft_strncmp(list->gnl.buf, \
	list->tokens[k].heredoc[i].eof, ft_strlen(list->tokens[k].heredoc[i].eof)))
	{
		if (g_global.heredoc_break == 1)
			return ;
		allocate(&temp, &head);
		if (!temp)
			ft_ret_exit(1, 1);
		temp->str = ft_strdup(list->gnl.buf);
		free_and_get_data(list, k, i);
	}
	list->tokens[k].heredoc[i].data = head;
}

/*We see if the EOF is in between quotes
If it is we should not expand anything
We do this here because after the parsing 
it removes the quotes*/
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

//We read the input for heredoc
//and save it in heredoc data structure
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
