/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_calc_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/10 00:20:25 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/20 00:35:40 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	heredoc_env(char *str, t_env *env, int *length, int *i)
{
	char *env_str;

	env_str = search_env(env, str + (*i), 0);
	(*length) += ft_strlen(env_str);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	(*i)--;
}

int	heredoc_get_str_len(t_list *list, char *str, t_heredoc *heredoc)
{
	int	i;
	int	newlength;

	i = 0;
	newlength = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '('))
			{
				if (str[i] == '(')
					newlength += heredoc_exec_len(list, heredoc, str, &i);
				else
					heredoc_env(str, list->env, &newlength, &i);
				if (heredoc->syntax_error)
					return (-1);
			}
			else
				i--;
		}
		else
		{
			newlength++;
			i++;
		}
	}
	return (newlength);
}
//[i am ] = 5
// [$(whoami)] = [rkieboom] = 8
//total = 13