/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_functions.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/06 00:23:24 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 00:22:11 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

//Allocates heredoc struct * the double redir left
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

//sets the EOF in the heredoc struct
void	get_heredoc_eof(t_list *list, int k)
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

//Allocates the heredoc struct
//And sets if the EOF has quotes
void	allocate_heredoc(t_list *list, int k)
{
	int	i;

	i = 0;
	heredoc_allocation(list, k);
	while (i < k)
	{
		if (list->tokens[i].double_redirection_left)
			get_heredoc_q(list, i);
		i++;
	}
}

//Here we set all heredoc information
void	set_heredoc(t_list *list, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		if (list->tokens[i].double_redirection_left)
		{
			get_heredoc_eof(list, i);
			get_heredoc_input(list, i);
			heredoc_parse(list, i);
		}
		i++;
	}
}
