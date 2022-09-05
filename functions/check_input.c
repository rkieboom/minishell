/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:32:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/05 11:19:23 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	check_input_quotes(t_list *list)
{
	char	*newstr;
	int		i;

	i = 0;
	while (1)
	{
		list->parse.comma1 = 0;
		list->parse.comma2 = 0;
		while (list->gnl.buf[i])
		{
			check_quote(list, &list->gnl.buf[i]);
			i++;
		}
		if (list->parse.comma1 == 1 || list->parse.comma2 == 1)
		{
			newstr = ft_strdup(list->gnl.buf);
			read_input(list, 1);
			list->gnl.buf = ft_strjoin(add_new_line(newstr), list->gnl.buf);
		}
		else
			break ;
		i = 0;
	}
}

int	check_input(t_list *v)
{
	int		i;
	char	*str;

	i = 0;
	str = v->gnl.buf;
	while (str[i])
	{
		i += skipspaces(str + i);
		if (!str[i])
			return (1);
		if (str[i] == ';')
		{
			ft_putendl_fd("minishell-4.2$: \
syntax error near unexpected token ;", 2);
			free(v->gnl.buf);
			v->gnl.buf = 0;
			return (258);
		}
		else
			while (str[i] && str[i] != ';')
				i++;
		if (str[i])
			i++;
	}
	return (0);
}
