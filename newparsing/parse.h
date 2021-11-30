/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:01:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/30 01:09:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"


void	new_parse(t_list *list);

char	**parse_split_commands(t_list *list, char c);
char	**parse_split_spaces(t_list *list, const char *str, char c);
char	**parse_split_tokens(t_list *list, int size, int k);

void	tokens(t_list *list);
char	*checkword(t_list *list, char *str);
char	*createstring(t_list *list, char *str, int length);

void	check_quote(t_list *list, char *c);
int		check_char_str(t_list *list, char *str);
int		check_char(char *c);

int		array_thingy(int *p);

#endif