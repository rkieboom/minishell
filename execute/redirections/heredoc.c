/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 12:48:35 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/17 12:50:51 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	heredoc_set_pipe(t_heredoc *heredoc, t_heredoc_data *data)
{
	if (pipe(heredoc->pipe) < 0)
		ft_ret_exit(1, 1);
	while (data)
	{
		ft_putendl_fd(data->str, heredoc->pipe[1]);
		data = data->next;
	}
	close(heredoc->pipe[1]);
}
