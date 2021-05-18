/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   functions.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/17 16:40:03 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/18 22:55:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// char *single_quote(t_list *list, char *str)
// {
// 	return (ft_substr(str, 1, ft_strlen(str) - 2));
// }


// static int ft_strchr_l(const char *s, int c)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = (char *)s;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == c)
// 			return (i);
// 		i++;
// 	}
// 	if (str[i] == c)
// 		return (i);
// 	return (0);
// }

// static char *recreate_string(t_list *list, char *str, char *env, int length)
// {
// 	int i;

// 	i = 0;
// 	while (str[i] && str[i] != '\"')
// 		i++;
// 	i += ft_strlen(env);
// 	while (str[i])
// 		i++;
// }

// static int	env_str_length(char *str)
// {
// 	int i;

// 	i = 0;
// 	if (str[i] == '$')
// 		i++;
// 	while (str[i] && (ft_isdigit(str[i]) || ft_isalpha(str[i])))
// 		i++;
// 	return (i);
// }

// static char *create_string(t_list *list, char *str, int length)
// {
// 	int i;
// 	int newstr_counter = 0;
// 	char *newstr;
// 	char *env;

// 	i = 0;
// 	newstr = malloc(length + 1);
// 	if (!newstr)
// 		return (NULL);
// 	while (length > 0)
// 	{
// 		if (str[i] == '$')
// 		{
// 			newstr_counter = ft_strlcpy(newstr + i, search_env(list->env, str + i, 0), ft_strlen(search_env(list->env, str + i, 0)) + 1); //lenghte van env
// 			newstr_counter -= env_str_length(str + i); //voor normale text na $PWD zodat de counter goed staat
// 			length -= ft_strlen(search_env(list->env, str + i, 0)) - 1;
// 			i += env_str_length(str + i) - 1;//i moet lengte van $PWD
// 		}
// 		else
// 			newstr[i + newstr_counter] = str[i];
// 		i++;
// 		length--;
// 	}
// 	newstr[i + newstr_counter] = 0;
// 	return (newstr);
// }

// char *double_quote(t_list *list, char *str)
// {
// 	char *str_dup;
// 	int i;
// 	int length;

// 	i = 0;
// 	str_dup = ft_strchr(str, '\"') + 1;
// 	length = ft_strchr_l(str_dup, '\"');
// 	while (str_dup[i] && str_dup[i] != '\"')
// 	{
// 		if (str_dup[i] == '$')
// 		{
// 			length += ft_strlen(search_env(list->env, str_dup + i, 0));
// 			length -= env_str_length(str_dup + i);
// 			i += env_str_length(str_dup + i) - 1;
// 		}
// 		i++;
// 	}
// 	str_dup = create_string(list, str_dup, length);
// 	// recreate_string(list, str, str_dup, length);

// 	ft_putstr_fd("\n", 1);
// 	ft_putendl_fd(str_dup, 1);
// 	// ft_putendl_fd(search_env(list->env, "PWD", 3), 1);
// 	// write(1, str_dup, ft_strlen(str_dup));

// 	return (str);
// }

// char *dollar(t_list *list, char *str)
// {
// 	return (NULL);
// }
