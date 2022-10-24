/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   commands.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/11 16:35:27 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 23:01:52 by rkieboom      ########   odam.nl         */
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
int		pwd(void);
int		echo(char **str);
int		export(t_env **v, char **str);
int		unset(t_env **v, char **str);
void	ft_execve(t_list *list, char **str);
void	ft_ret_exit(int ret, int print);
void	ft_exit(char **str);

/*
###
###		Functions
###
*/

int		cd_check_permissions(char *path);
int		cd_exec_cmd(t_env *env, char *path);
int		cd_tilde_expansion(t_list *list, char *str);

char	*relative_path(char *PATH, t_env *env);
char	*absolute_path(char *PATH);
int		is_absolute_path(char *str);
int		check_exist(char *PATH);
int		check_permission(char *PATH);
void	export_declare_list(t_env *v);
void	ft_swap(char **s1, char **s2);//Not ness
void	signals(void);
void	signals_dfl(void);

#endif