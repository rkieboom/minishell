/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/12 19:10:43 by rkieboom      #+#    #+#                 */
/*   Updated: 2020/11/15 20:26:38 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>

void	ft_error(char *msg, int ret)
{
	write(2, msg, ft_strlen(msg));
	//call free func?
	if (ret == -1)
		ret = 1;
	exit(ret);
}
