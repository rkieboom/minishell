/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   absolute_path.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 10:02:42 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/22 14:24:29 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

char	*absolute_path(char *PATH)
{
	if (check_exist(PATH))
	{
		ft_putstr_fd("minishell-4.2$: ", 2);
		ft_putstr_fd(PATH, 2);
		ft_putendl_fd(": command not found", 2);
		return (NULL);
	}
	if (check_permission(PATH))
		return (NULL);
	return (ft_strdup(PATH));
}
