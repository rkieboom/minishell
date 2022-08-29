/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/27 03:29:49 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/08/29 14:23:38 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include "../cmd.h"

void	count_tokens(t_list *v, t_newcommand *temp, int k);
void	init_new_tokens(t_newcommand *cmd);
void	set_tokens(t_list *v, t_newcommand *pipes, int k);

#endif