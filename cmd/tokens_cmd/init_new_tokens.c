/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_new_tokens.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 14:08:13 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 00:46:13 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

//Allocate the token variables
void	init_new_tokens(t_newcommand *cmd)
{
	t_newcommand	*temp;

	temp = cmd;
	while (temp)
	{
		if (temp->tokens && temp->tokens->total > 0)
		{
			temp->tokens->token = \
			ft_calloc(temp->tokens->total + 1, sizeof(char *));
			if (!temp->tokens->token)
				ft_ret_exit(1, 1);
			temp->tokens->token[temp->tokens->total] = 0;
			temp->tokens->token_pos = \
			ft_calloc(temp->tokens->total + 1, sizeof(int));
			if (!temp->tokens->token_pos)
				ft_ret_exit(1, 1);
			temp->tokens->token_pos[temp->tokens->total] = 0;
		}
		temp = temp->next;
	}
}
