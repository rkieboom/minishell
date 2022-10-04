/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_pipes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 02:13:57 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/04 22:41:34 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	write_to_pipe(t_heredoc *heredoc, t_heredoc_data *data)
{
	if (pipe(heredoc->pipe) < 0)
		ft_ret_exit(1, 1);
	while (data)
	{
		if (write(heredoc->pipe[1], data->str, ft_strlen(data->str)) < 0)
			ft_ret_exit(1, 1);
		if (write(heredoc->pipe[1], "\n", 1) < 0)
			ft_ret_exit(1, 1);
		data = data->next;
	}
	close(heredoc->pipe[1]);
}

void	clear_pipe_heredoc(t_heredoc *heredoc)
{
	close(heredoc->pipe[0]);
}
