/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parsing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/09 12:18:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/09 15:53:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static void	heredoc_changelen(char *str, t_env *env, int *length, int *i)
{
	char *env_str;

	env_str = search_env(env, str + (*i), 0);
	(*length) += ft_strlen(env_str);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	(*i)--;
	(*length)--;
}

static char	*heredoc_retenv_updatei(t_env *env, char *str, *i) //kijken als er 2 naast elkaa staan = $$
{
	char	*env_str;

	env_str = search_env(env, str + (*i), 0);
	
}

static void	heredoc_exec()
{
	
}

static int	get_newstr_len(t_env *env, char *str)
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
					heredoc_exec();
				else
					heredoc_changelen(str, env, &newlength, &i);
			}
			else
				i--;
		}
		newlength++;
		i++;
	}
	return (newlength);
}

static char	*get_newstr(t_list *list, t_heredoc_data *data, char *str, int length)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = ft_calloc(length, sizeof(char));
	if (!newstr)
		ft_ret_exit(1, 1);
	while (str[i])
	{
		if ()
		newstr[i] = str[i];
		

		
		i++;
	}
}

static void	heredoc_parse_str(t_list *list, t_heredoc_data *data)
{
	int	i;
	int	newlength;

	i = 0;
	while (data != NULL)
	{
		while (data != NULL && !ft_strchr(data->str, '$'))
			data = data->next;
		if (!data)
			return ;
		newlength = get_newstr_len(list->env, data->str);
		data->str = get_newstr(list, data, newlength);


		printf("%i. length=[%i]\n", i, newlength);
		i++;
		data = data->next;
	}
}

void	heredoc_parse(t_list *list, int k)
{
	int	i;

	i = 0;
	while (i < list->tokens[k].double_redirection_left)
	{
		if (list->tokens[k].heredoc[i].heredoc_q == 0)
			heredoc_parse_str(list, list->tokens[k].heredoc[i].data);
		i++;
	}
}

//Dit is mijn pwd=/Users/rkieboom/Documents/minishell