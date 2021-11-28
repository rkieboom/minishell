/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/27 15:01:52 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/11/28 15:31:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"


void	new_parse(t_list *list);

char	**parse_split_commands(t_list *list, char c);
char	**parse_split_spaces(t_list *list, const char *str, char c);


char	*checkword(t_list *list, char *str);
char *createstring(t_list *list, char *str, int length);

void	check_quote(t_list *list, char *c);

#endif