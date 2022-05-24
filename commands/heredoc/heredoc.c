/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/18 15:03:34 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/24 13:12:42 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static char *add_newline(char *str)
{
	char *newstr;
	int length;

	if (!str)
		return (ft_strdup("\n"));
	length = ft_strlen(str);
	newstr = ft_calloc(sizeof(char), ft_strlen(length + 2));
	if (!newstr)
		ft_ret_exit(1, 1);
	ft_strlcpy(newstr, str, ft_strlen(str));
	newstr[length] = "\n";
	free(str);
	return (newstr);
}

static char *cunt_function(char *buf)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (buf[i])
	{
		if (buf[i] == '$')   			//$LOGNAME = env variable || $(whoami) = functie
			
		i++;
		size++;
	}
}

static char	*read_data(char *delimiter)
{
	char *buf;
	char *total;
	char *tmp;

	total = ft_strdup("");
	buf = readline("> ");
	if (!buf)
		ft_ret_exit(1, 1);
	while (ft_strncmp(delimiter, buf, ft_strlen(delimiter) + 1))
	{
		if (ft_strchr(buf, '$'))
			cunt_function(buf);
		buf = add_new_line(buf);
		tmp = total;
		total = ft_strjoin(total, buf);
		if (!total)
			ft_ret_exit(1, 1);
		free(tmp);
		free(buf);
		buf = readline("> ");
		if (!buf)
			ft_ret_exit(1, 1);
	}
	free(buf);
	return (total);
}


char *heredoc(char *cmd, char *delimiter)
{
	char *str;

	str = read_data(delimiter);
	
	return (0);
}

//Dit is een test $(whoami)