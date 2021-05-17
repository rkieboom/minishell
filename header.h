/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:04:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 16:46:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include "env_list/env_list.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_parse
{
	char		**commands;
	int			comma1;
	int			comma2;
}				t_parse;

typedef struct	s_gnl
{
	int			fd;
	char		*buf;
}				t_gnl;


typedef struct	s_list
{
	t_parse parse;
	t_gnl	gnl;
	t_env	*env;
}				t_list;

int				get_next_line(int fd, char **line);

int				parse(t_list *list);

void			free_parse_commands(t_list *list);

void			ft_error(char *msg);

void			execute(t_list *list);
int				skipspaces(const char *str);

void	check_quote(t_list *list, char *c);
char	*add_new_line(char *str);

#endif