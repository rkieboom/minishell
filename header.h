/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   header.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:04:45 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 01:45:20 by rkieboom      ########   odam.nl         */
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
# include <termios.h>

# include <readline/readline.h>
# include <readline/history.h>

# define __DUP__ "MINISHELL_DUP_537425"

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

typedef struct s_heredoc_data
{
	char					*str;
	struct s_heredoc_data	*next;
}				t_heredoc_data;

typedef struct s_heredoc
{
	int				pipe[2];
	int				heredoc_q;
	char			*eof;
	t_heredoc_data	*data;

}				t_heredoc;

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
	int			error;
	t_heredoc	*heredoc;
}				t_tokens;

typedef struct s_newcommand
{
	int						id;
	int						fd[2];
	int						read_pipe;
	char					**command;
	struct s_tokens			*tokens;
	struct s_newcommand		*next;
	struct s_newcommand		*prev;
}				t_newcommand;

typedef struct s_list
{
	int				stdout_cpy;
	int				stdin_cpy;
	t_parse			parse;
	t_gnl			gnl;
	t_env			*env;
	t_tokens		*tokens;
	t_newcommand	*cmd;
}				t_list;

typedef struct s_global
{
	int				status;
	pid_t			pid;
	struct termios	termios_save;
	struct termios	termios_new;
	int				heredoc_break;
	int				__dup__;
}				t_global;

extern t_global	g_global;

int		new_parse(t_list *list);

void	free_all(t_list *list);
void	free_commands(t_list *list, t_newcommand *temp, \
						t_newcommand *temp2, int totalcommands);
void	free_heredoc(t_list *list, int totalcommands);

void	ft_error(char *msg);
int		syntax_error_parse(t_list *list);
int		syntax_error(t_newcommand *cmd, int i);

void	execution(t_list *list, t_newcommand *cmd, int k);
int		skipspaces(const char *str);

void	check_quote(t_list *list, char *c);
char	*add_new_line(char *str);
int		cmd_len(char **str);

int		check_input(t_list *v);
void	read_input(t_list *list, int option);
void	check_input_quotes(t_list *list);

int		create_cmd(t_list *v, int k);

void	sig_handler(int sign_num);

#endif