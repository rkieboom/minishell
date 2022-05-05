/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 12:47:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/04 12:03:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static void	create_command(t_list *v, t_newcommand *pipes_cmd, int k)
{
	int	i;

	i = 0;
	while (v->parse.commands[k][i])
		i++;
	pipes_cmd->command = ft_calloc(i+1, sizeof(char *));
	if (!pipes_cmd->command)
		ft_ret_exit(1, 1);
	i = 0;
	while (v->parse.commands[k][i])
	{
		pipes_cmd->command[i] = ft_strdup(v->parse.commands[k][i]);
		if (!pipes_cmd->command[i])
			ft_ret_exit(1, 1);
		i++;
	}
}

int		create_cmd(t_list *v, int k)
{
	int	i;
	int	pipes;

	i = 0;
	while (v->parse.commands[k])
		k++;
	v->pipecommand = ft_calloc(k, sizeof(t_newcommand)); //plus 1???
	if (!v->pipecommand)
		ft_error("Malloc failed!\n");
	while (i < k)
	{
		pipes = v->tokens[i].pipe;
		if (pipes == 0)
			create_command(v, &v->pipecommand[i], i);
		else
			declaring_values(v, &v->pipecommand[i], pipes, i);//positie nodig k
		if (v->tokens[i].total)
			tokens_cmd(v, &v->pipecommand[i], i);//positie k
		i++;
	}
	// i = 0;
	// while (i < k)
	// {
	// 	temp = &v->pipecommand[i];
	// 	while (temp)
	// 	{
	// 		int j = 0;
	// 		while (temp->command[j])
	// 		{
	// 			printf("%i-id=[%i] [%s]\n", i, temp->id ,temp->command[j]);
	// 			j++;
	// 		}
	// 		printf("tokenstotal=[%i]\n---\n", temp->tokens->total);
	// 		temp = temp->next;
	// 	}
	// 	i++;
	// }
	// exit(1);
	return (0);
}
