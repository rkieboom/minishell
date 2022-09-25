/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_pipes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/20 02:13:57 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/20 02:17:25 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

void	set_pipe_heredoc(t_heredoc *heredoc, t_heredoc_data *data)
{
	if (pipe(heredoc->pipe) < 0)
		ft_ret_exit(1, 1);
	if (write(heredoc->pipe[1], data->str, ft_strlen(data->str)) < 0)
		ft_ret_exit(1, 1);
	close(heredoc->pipe[1]);
}

void	clear_pipe_heredoc(t_heredoc *heredoc)
{
	close(heredoc->pipe[0]);
}
