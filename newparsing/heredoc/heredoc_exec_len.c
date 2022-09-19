/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_exec_len.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/10 19:20:38 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/16 17:05:20 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../parse.h"

static char	*remove_newline_str(char *str)
{
	int	i;
	int	length;
	char *newstr;

	i = 0;
	length = 0;
	while (str[i])
		i++;
	i--;
	while (i > 0 && str[i] == '\n')
	{
		i--;
		length++;
	}
	newstr = ft_substr(str, 0, ft_strlen(str) - length);
	free(str);
	return (newstr);
}

static int	read_fd(int fd)
{
	char	*str_free;
	char	*str;
	char	*temp;
	int		c_read;

	c_read = 1;
	temp = ft_calloc(sizeof(char), 256);
	if (!temp)
		ft_ret_exit(1, 1);
	str = ft_strdup("");
	while (c_read > 0)
	{
		c_read = read(fd, temp, 255);
		if (c_read == -1)
			ft_ret_exit(1, 1);
		temp[c_read] = 0;
		str_free = str;
		str = ft_strjoin(str, temp);
		if (!str)
			ft_ret_exit(1, 1);
		free(str_free);
	}
	free(temp);
	str = remove_newline_str(str);
	c_read = ft_strlen(str);
	return (c_read);
}

static int	run_and_ret_cmdlen(t_list *list, t_heredoc *heredoc, char **cmd)
{
	int		length;
	int		fd_stdout_cpy;

	length = 0;
	fd_stdout_cpy = dup(1);
	close(1);
	dup2(heredoc->pipe[1], 1);
	ft_execve(list, cmd, 0);
	close(heredoc->pipe[1]);
	dup2(fd_stdout_cpy, 1);
	length = read_fd(heredoc->pipe[0]);
	close(heredoc->pipe[0]);
	return (length);
}

static int	check_syntax_error_and_len(t_heredoc *heredoc, int i)
{
	char	*str;
	int		length;
	int		bracket;

	length = 0;
	str = heredoc->data->str;
	bracket = 0;
	while (str[i] && str[i] == '(')
	{
		i++;
		bracket++;
	}
	while (str[i + length] && str[i + length] != ')')
		length++;
	while (str[i + length] && str[i + length ] == ')')
	{
		i++;
		bracket--;
	}
	if (bracket > 0)
	{
		heredoc->syntax_error = ft_strdup("minishell: bad substitution: no closing `)' in");
		return (-1);
	}
	return (length);
}

static char	**get_heredoc_exec_cmd(char *str, int *i, int length)
{
	char	*cmd;
	char	**arr_cmd;
	int		bracket;

	bracket = 0;
	while (str[*i] && str[*i] == '(')
	{
		(*i)++;
		bracket++;
	}
	cmd = ft_substr(str, *i, length);
	if (!cmd)
		ft_ret_exit(1, 1);
	arr_cmd = ft_split(cmd, ' ');
	if (!arr_cmd)
		ft_ret_exit(1, 1);
	free(cmd);
	*i += length + bracket;
	return (arr_cmd);
}

int	heredoc_exec_len(t_list *list, t_heredoc *heredoc, char *str, int *i)
{
	int	length;
	int	cmd_c = 0;
	char 	**cmd;
	
	length = check_syntax_error_and_len(heredoc, *i);
	if (length == -1)
		return (-1);//nog opvangen
	cmd = get_heredoc_exec_cmd(str, i, length);
	if (pipe(heredoc->pipe) < 0)
		ft_ret_exit(1, 1);
	if (heredoc_cmd_exist(*cmd, list->env, 0))
		length = run_and_ret_cmdlen(list, heredoc, cmd);
	else
		length = 0;
	cmd_c = 0;
	while (cmd[cmd_c])
	{
		free(cmd[cmd_c]);
		cmd_c++;
	}
	free(cmd);
	return (length);
}
