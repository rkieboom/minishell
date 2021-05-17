/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:18:10 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/17 13:45:49 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../header.h"

void	read_input(t_list *list, int ret);

void		parse_check_quotes(t_list *list);
void		check_quote(t_list *list, char *c);
char		*add_new_line(char *str);

#endif	