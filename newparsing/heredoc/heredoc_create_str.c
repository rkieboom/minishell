/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_create_str.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 21:21:20 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/16 16:25:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"


// static void	run_and_copy_exec(t_list *list, char *str, int *str_c)
// {
// 	int	bracket;

// 	bracket = 0;
// 	while (str[*str_c] && str[])
// }

char	*heredoc_create_str(t_list *list, t_heredoc *heredoc, char *str, int length)
{
	int		i;
	int		j;
	int		str_c;
	char	*newstr;
	char	*temp;

	int bracket = 0;

	i = 0;
	j = 0;
	str_c = 0;
	newstr = ft_calloc(length + 1, sizeof(char));
	if (!newstr)
		ft_ret_exit(1, 1);
	while (str[str_c])
	{
		if (str[str_c] == '$')
		{
			str_c++;
			if (str[str_c] && (ft_isalnum(str[str_c]) || str[str_c] == '_' || str[str_c] == '('))
			{
				if (str[str_c] == '(')
				{
					temp = heredoc_exec_str(list, heredoc, str, &str_c);
					if (temp)
						j += ft_strlcpy(newstr + i + j, temp, ft_strlen(temp) + 1);
					while (str[str_c] && str[str_c] == '(')
					{
						str_c++;
						bracket++;
					}
					while (str[str_c] && str[str_c] != ')' && bracket)
					{
						str_c++;
						bracket--;
					}
				}
				else
				{
					temp = search_env(list->env, str + i, 0);
					j += ft_strlcpy(newstr + i + j, temp, ft_strlen(temp) + 1) - 1;
					while (str[str_c] && (ft_isalnum(str[str_c]) || str[str_c] == '_'))
						str_c++;
				}
			}
			else
				str_c--;
		}
		else
		{
			newstr[i + j] = str[str_c];
			str_c++;
			i++;
		}
	}
	free(str);
	newstr[length] = 0;
	return (newstr);
}