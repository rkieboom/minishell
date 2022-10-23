/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_tokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 14:08:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 00:51:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

typedef struct s_vars
{
	t_newcommand	*temp;	
	int				tokens;
	int				i;
	int				token_c;
	int				token_local_c;
}				t_vars;

//Return the token we are at
static char	*ret_token(t_list *v, int k, int token_count)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (count != token_count)
	{
		if (v->tokens[k].token[i] && \
		!ft_strncmp(v->tokens[k].token[i], "|", 2))
			i++;
		else
		{
			count++;
			if (count != token_count)
				i++;
		}
		if (!v->tokens[k].token[i])
			ft_error("Something went wrong in func: ret_token\n");
	}
	return (v->tokens[k].token[i]);
}

static int	get_resetter(t_list *v, int k, int i)
{
	while (i > 0)
	{
		i--;
		if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
			return (v->tokens[k].token_pos[i] + 1);
	}
	return (0);
}

/**
 * @param token_pos = Is the x token we want
 * 
 * *		 [-1] [-1] [0] [-1][1] [-1] [2][-1]
 * *Example: cat main.c >  out  <  out2 > Makefile
 * *token_pos = 0 will return >
 * *token_pos = 1 will return <
**/
static int	get_token_pos(t_list *v, int k, int token_count)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (count != token_count)
	{
		if (v->tokens[k].token[i] && \
		!ft_strncmp(v->tokens[k].token[i], "|", 2))
			i++;
		else
		{
			count++;
			if (count != token_count)
				i++;
		}
		if (!v->tokens[k].token[i])
			ft_error("Something went wrong in func: get_token_pos\n");
	}
	return (v->tokens[k].token_pos[i] - get_resetter(v, k, i));
}

//Set the token values
void	set_tokens(t_list *v, t_newcommand *pipes, int k)
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	vars.temp = pipes;
	while (vars.temp)
	{
		vars.i = 0;
		vars.tokens = vars.temp->tokens->total;
		while (vars.tokens)
		{
			vars.temp->tokens->token[vars.token_local_c] = \
			ft_strdup(ret_token(v, k, vars.token_c + 1));
			if (!vars.temp->tokens->token[vars.token_local_c])
				ft_ret_exit(1, 1);
			vars.temp->tokens->token_pos[vars.token_local_c] = \
			get_token_pos(v, k, vars.token_c + 1);
			vars.token_c++;
			vars.token_local_c++;
			vars.tokens--;
			vars.i++;
		}
		vars.temp = vars.temp->next;
		vars.token_local_c = 0;
	}
	set_heredoc_tokens(v, pipes, k);
}
