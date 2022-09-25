/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_last_redir.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/21 01:18:00 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/21 04:13:36 by rkieboom      ########   odam.nl         */
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
			if (single_redirection_left(v, i) < 0)
				return (1);
		}
		else if (!ft_strncmp(v->tokens->token[i], ">>", 3))
			double_redirection_right(v, i);
		else if (!ft_strncmp(v->tokens->token[i], ">", 2))
			single_redirection_right(v, i);
		i++;
	}
	return (0);
}
