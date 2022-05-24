/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:04:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/24 13:46:53 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include "env_list/env_list.h"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_parse
{
	char		***commands;
	int			comma1;
	int			comma2;
}				t_parse;

typedef struct s_gnl
{
	int			fd;
	char		*buf;
}				t_gnl;

typedef struct s_dir
{
	DIR				*dir;
	struct dirent	*dp;
}					t_dir;

typedef struct s_tokens
{
	int			total;
	int			stdin_fd;
	int			stdout_fd;
	char		**token;
	int			*token_pos;
	int			single_redirection_left;
	int			single_redirection_right;
	int			double_redirection_left;
	int			double_redirection_right;
	int			pipe;
	int			last_l;
	int			last_r;
	int			*heredoc_q;
}				t_tokens;

typedef struct s_newcommand
{
	int						id;
	char					**command;
	struct s_tokens			*tokens;
	struct s_newcommand		*next;
}				t_newcommand;

typedef struct s_list
{
	int				stdout_cpy;
	int				stdin_cpy;
	int				ret;
	t_parse			parse;
	t_gnl			gnl;
	t_dir			dir;
	t_env			*env;
	t_tokens		*tokens;
	t_newcommand	*cmd;
}				t_list;

void	new_parse(t_list *list);

void	free_parse_commands(t_list *list);

void	ft_error(char *msg);
int		syntax_error(t_newcommand *cmd);

void	execute(t_list *list, t_newcommand *v, int k);
int		skipspaces(const char *str);

void	check_quote(t_list *list, char *c);
char	*add_new_line(char *str);

int		check_input(t_list *v);
void	read_input(t_list *list, int option);
void	check_input_quotes(t_list *list);

int		create_cmd(t_list *v, int k);

#endif