/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 12:47:40 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/20 13:37:40 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

int		create_cmd(t_list *v, int k)
{
	int	i;
	int	pipes;

	i = 0;
	while (v->parse.commands[k])
		k++;
	v->pipecommand = ft_calloc(k, sizeof(t_pipecommand)); //plus 1???
	if (!v->pipecommand)
		ft_error("Malloc failed!\n");
	while (i < k)
	{
		pipes = v->tokens[i].pipe;
		declaring_values(v, &v->pipecommand[i], pipes, i);//positie nodig k
		tokens_cmd(v, v->pipecommand, k);//totale nodig k
		i++;
	}


	return (0);
}
