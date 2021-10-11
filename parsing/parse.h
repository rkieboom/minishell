/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:18:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/10/11 16:24:23 by spelle        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"

void	read_input(t_list *list, int ret);
void	tokens(t_list *list, int k);

void	parse_check_quotes(t_list *list);
void	check_quote(t_list *list, char *c);
char	*add_new_line(char *str);
char	**split_spaces(t_list *list, const char *str, char c);

char	*single_quote(t_list *list, char *str);
char	*double_quote(t_list *list, char *str);
char	*dollar(t_list *list, char *str);

int		array_thingy(int *p);
int		check_char(char *c);
int		check_char_str(t_list *list, char *str);
void	free_old_and_set(t_list *list, int k, char **str, char **newstr);
int		split_str_size(char **str, int j);

#endif	