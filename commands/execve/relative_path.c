/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   relative_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:02:42 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/09/07 11:07:16 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

char *relative_path(char *PATH)
{
	if (check_exist(PATH))
		return (NULL);
	if (check_permission(PATH))
		return (NULL);


	return (ft_strdup(PATH));
}
