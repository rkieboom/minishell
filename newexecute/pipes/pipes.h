/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/19 16:31:29 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/05 01:01:02 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "../execute.h"

typedef struct s_vars
{
	int				i;
	int				size;
	int				oldpipes;
	int				newpipes[2];
	int				fd_stdin_cpy;
	int				fd_stdout_cpy;
	int				error;

	t_newcommand	*temp;
}				t_vars;

void	setup_pipes(t_vars *vars);
void	clear_pipes(t_vars *vars);

#endif