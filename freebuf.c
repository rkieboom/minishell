/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   freebuf.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 20:08:57 by rkieboom      #+#    #+#                 */
/*   Updated: 2020/11/29 10:44:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		freebuf(t_list *list)
{
	free(list->gnl.buf);
	list->gnl.buf = NULL;
}
