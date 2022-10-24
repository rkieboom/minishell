/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/30 00:29:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 09:24:00 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	allocate_tokens_vars(t_list *list)
{
	int	j;
	int	k;
	int	total;

	k = 0;
	total = 0;
	while (list->parse.commands[k])
	{
		j = 0;
		while (list->parse.commands[k][j])
		{
			if (check_char(list->parse.commands[k][j]))
				total++;
			j++;
		}
		list->tokens[k].token = ft_calloc(total + 1, sizeof(char *));
		if (!list->tokens[k].token)
			ft_ret_exit(1, 1);
		list->tokens[k].token_pos = ft_calloc(total + 1, sizeof(int));
		if (!list->tokens[k].token_pos)
			ft_ret_exit(1, 1);
		list->tokens[k].total = total;
		total = 0;
		k++;
	}
}

static void	set_tokens(t_list *list)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	while (list->parse.commands[k])
	{
		i = 0;
		j = 0;
		while (list->parse.commands[k][j])
		{
			if (check_char(list->parse.commands[k][j]))
			{
				list->tokens[k].token[i] = \
				ft_strdup(list->parse.commands[k][j]);
				list->tokens[k].token_pos[i] = j;
				i++;
			}
			j++;
		}
		k++;
	}
}

// Counts occurence of every token
static void	identify_tokens(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	while (list->parse.commands[i])
	{
		j = 0;
		while (j < list->tokens[i].total)
		{
			if (!ft_strncmp(list->tokens[i].token[j], "<<", 3))
				list->tokens[i].double_redirection_left++;
			else if (!ft_strncmp(list->tokens[i].token[j], ">>", 3))
				list->tokens[i].double_redirection_right++;
			else if (!ft_strncmp(list->tokens[i].token[j], "<", 2))
				list->tokens[i].single_redirection_left++;
			else if (!ft_strncmp(list->tokens[i].token[j], ">", 2))
				list->tokens[i].single_redirection_right++;
			else if (!ft_strncmp(list->tokens[i].token[j], "|", 2))
				list->tokens[i].pipe++;
			j++;
		}
		i++;
	}
}

//It saves wich word is a token
//And it saves the location of the token
void	tokens(t_list *list)
{
	allocate_tokens_vars(list);
	set_tokens(list);
	identify_tokens(list);
}
