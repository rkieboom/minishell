/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:59:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/16 20:24:02 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../header.h"
# include "../commands/commands.h"

void	checkcommand(t_list	*list, int k);

void	set_redirection(t_list *list, int k);

#endif