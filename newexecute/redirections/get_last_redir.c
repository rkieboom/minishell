/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_last_redir.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 01:18:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 23:50:20 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	init_vars(t_tokens *tokens)
{
	tokens->last_l = -1;
	tokens->last_r = -1;
}

int	get_last_redir(t_newcommand *v, int i, int total)
{
	init_vars(v->tokens);
	while (i < total)
	{
		if (!ft_strncmp(v->tokens->token[i], "<<", 3))
			double_redirection_left(v, i);
		else if (!ft_strncmp(v->tokens->token[i], "<", 2))
		{
			if (single_redirection_left(v, i))
				return (1);
		}
		else if (!ft_strncmp(v->tokens->token[i], ">>", 3))
		{
			if (double_redirection_right(v, i))
				return (1);
		}
		else if (!ft_strncmp(v->tokens->token[i], ">", 2))
		{
			if (single_redirection_right(v, i))
				return (1);
		}
		i++;
	}
	return (0);
}
