/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:51:12 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/19 19:31:43 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	create_line(t_list *list, int k)
{
	int i;

	i = 0;
	list->cmd[k].cmd = ft_calloc(list->tokens[k].token_pos[0] + 1, sizeof(char*));
	while (i < list->tokens[k].token_pos[0])
	{
		list->cmd[k].cmd[i] = list->parse.commands[k][i];
		i++;
	}
}

static int	create_cmd(t_list *list)
{
	int k;

	k = 0;
	while (list->parse.commands[k])
		k++;
	list->cmd = ft_calloc(k + 1, sizeof(t_cmd));
	k = 0;
	while (list->parse.commands[k])
	{
		if (list->tokens[k].total > 0)
			create_line(list, k);
		else
			list->cmd[k].cmd = list->parse.commands[k];
		k++;
	}
	return (k);
}

static void	redirection_single_left(t_list *list, int k)
{
	
}
static void redirection_double_left(t_list *list, int k)
{
	
}

static void redirection_single_right(t_list *list, int k)
{
	int i;

	i = 0;
	while (ft_strncmp(list->tokens[k].token[i], ">", 2) == 0)
		i++;
	i = list->tokens[k].token_pos[i - 1];
	list->tokens[k].fd = open(list->parse.commands[k][i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	dup2(list->tokens[k].fd, 1);
}

static void redirection_double_right(t_list *list, int k)
{
	
}



static void	set_redirection(t_list *list, int k)
{
	int total;

	total = list->tokens[k].total;
	if (total <= 0)
		return ;
	

}

void		execute(t_list *list)
{
	int i;
	int k;
	
	i = 0;
	k = create_cmd(list);
	while (list->parse.commands[i])
	{
		list->stdout_cpy = dup(1);
		set_redirection(list, i);
		checkcommand(list, i);
		if (list->tokens[i].total > 0)
			dup2(list->stdout_cpy, 1);
		close(list->stdout_cpy);
		i++;
	}
}
