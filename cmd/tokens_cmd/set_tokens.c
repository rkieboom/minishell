/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_tokens.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/29 14:08:53 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/08/29 14:29:58 by rkieboom      ########   odam.nl         */
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

static char	*ret_token(t_list *v, int k, int token_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i - j != token_count)
	{
		if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
			j++;
		i++;
	}
	if (token_count == 0)
	{
		while (1)
		{
			if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
				j++;
			else
				return (v->tokens[k].token[i]);
			i++;
		}
	}
	return (v->tokens[k].token[i]);
}

static int	get_token_pos_null(t_list *v, int k)
{
	int	i;
	int	j;
	int	resetter;

	i = 0;
	j = 0;
	resetter = 0;
	while (1)
	{
		if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
		{
			resetter = v->tokens[k].token_pos[i] + 1;
			j++;
		}
		else
			return (v->tokens[k].token_pos[i] - resetter);
		i++;
	}
}

static int	get_token_pos(t_list *v, int k, int token_count)
{
	int	i;
	int	j;
	int	resetter;

	i = 0;
	j = 0;
	resetter = 0;
	while (i - j != token_count)
	{
		if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
		{
			resetter = v->tokens[k].token_pos[i] + 1;
			j++;
		}
		i++;
	}
	if (token_count == 0)
		return (get_token_pos_null(v, k));
	return (v->tokens[k].token_pos[i] - resetter);
}

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
			ft_strdup(ret_token(v, k, vars.token_c));
			if (!vars.temp->tokens->token[vars.token_local_c])
				ft_ret_exit(1, 1);
			vars.temp->tokens->token_pos[vars.token_local_c] = \
			get_token_pos(v, k, vars.token_c);
			vars.token_c++;
			vars.token_local_c++;
			vars.tokens--;
			vars.i++;
		}
		vars.temp = vars.temp->next;
		vars.token_local_c = 0;
	}
}
