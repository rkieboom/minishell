/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:35:27 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/20 09:41:23 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# include "../header.h"
# include "../libft/libft.h"
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <fcntl.h>

int		cd(t_list *v, char **str);
int		env(t_env *v);
int		pwd(t_env *v);
int		ft_echo(t_list *v, char **str);
int		ft_execve(t_list *list, char **str);
void	ft_exit(int ret);
int		export(t_env *v, char **str);
int		unset(t_env *v, char **str);

/*
###
###		Functions
###
*/

char	*add_new_line(char *str);
char	*relative_path(char *PATH);
char	*absolute_path(char *PATH, t_env *env);
int		check_exist(char *PATH);
int		check_permission(char *PATH);

#endif