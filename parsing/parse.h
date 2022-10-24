/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:01:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/24 10:59:07 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"

int		new_parse(t_list *list);
int		parse_arraysize(char **str, t_list *list);

char	**parse_split_commands(t_list *list, char c);
char	**parse_split_spaces(t_list *list, const char *str, char c);
void	parse_split_tokens(t_list *list, int size, int k);

void	tokens(t_list *list);
char	*checkword(t_list *list, char *str);
int		checkword_calclen(t_list *list, char *str, int i, int length);
char	*createstring(t_list *list, char *str, int length);

void	check_quote(t_list *list, char *c);
int		check_char_str(t_list *list, char *str);
int		check_char(char *c);
int		check_exist(char *PATH);

void	allocate_heredoc(t_list *list, int k);
void	set_heredoc(t_list *list, int k);
void	heredoc_parse(t_list *list, int k);
int		heredoc_get_str_len(t_list *list, char *str);
char	*heredoc_create_str(t_list *list, char *str, int length);

void	get_heredoc_eof(t_list *list, int k);
void	get_heredoc_input(t_list *list, int k);
void	get_heredoc_q(t_list *list, int k);

int		array_thingy(int *p);

int		ft_execve(t_list *list, char **str, int ret);
void	signal_handler_hdoc(int signum);

char	*search_env(t_env *v, char *name, int length, char *temp);
void	tilde_expansion(t_list *list, int length);

#endif