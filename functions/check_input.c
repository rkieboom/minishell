/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/02 17:32:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 14:20:30 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// Called when user input has unclosed quotes.
// Stores current gnl.buf and prompts user for input again using read_input()
static void	quote(t_list *list)
{
	char	*newstr;
	char	*temp;

	newstr = ft_strdup(list->gnl.buf);
	if (!newstr)
		ft_ret_exit(1, 1);
	read_input(list, 1);
	if (!list->gnl.buf)
	{
		free(newstr);
		return ;
	}
	temp = list->gnl.buf;
	newstr = add_new_line(newstr);
	list->gnl.buf = ft_strjoin(newstr, list->gnl.buf);
	if (!list->gnl.buf)
		ft_ret_exit(1, 1);
	free(temp);
	free(newstr);
}

// Checks if gnl.buf contains unclosed quotes.
// User remains in this function unrtil input has closed quotes.
void	check_input_quotes(t_list *list)
{
	int		i;

	i = 0;
	while (1)
	{
		if (!list->gnl.buf)
			return ;
		list->parse.comma1 = 0;
		list->parse.comma2 = 0;
		while (list->gnl.buf[i])
		{
			check_quote(list, &list->gnl.buf[i]);
			i++;
		}
		if (list->parse.comma1 == 1 || list->parse.comma2 == 1)
			quote(list);
		else
			break ;
		i = 0;
	}
}

static int	check_ret_error(t_list *v)
{
	ft_putendl_fd("minishell-4.2$: \
syntax error near unexpected token ;", 2);
	free(v->gnl.buf);
	v->gnl.buf = 0;
	g_global.status = 258;
	return (1);
}

// Checking semicolons syntax error
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
			return (check_ret_error(v));
		else
			while (str[i] && str[i] != ';')
				i++;
		if (str[i])
			i++;
	}
	return (0);
}
