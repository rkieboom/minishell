/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:35:27 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/06/29 14:31:44 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../header.h"
# include "../libft/libft.h"

int		cd(t_list *v, char **str);
int		env(t_env *v);
int		pwd(t_env *v);
int		ft_echo(t_list *v, char **str);

/*
###
###		Functions
###
*/

char	*add_new_line(char *str);

#endif