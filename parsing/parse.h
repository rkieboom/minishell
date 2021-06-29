/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:18:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/06/29 14:36:32 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"

void	read_input(t_list *list, int ret);

void	parse_check_quotes(t_list *list);
void	check_quote(t_list *list, char *c);
char	*add_new_line(char *str);
char	**split_spaces(t_list *list, const char *str, char c);


char *single_quote(t_list *list, char *str);
char *double_quote(t_list *list, char *str);
char *dollar(t_list *list, char *str);

#endif	