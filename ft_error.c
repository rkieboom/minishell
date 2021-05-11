/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:10:43 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/05/11 15:58:05 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>

void	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	//call free func?
	exit(1);
}
