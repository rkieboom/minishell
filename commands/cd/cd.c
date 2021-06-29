/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 14:29:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/06/29 16:25:21 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

int	cd(t_list *v, char **str) //voor nu simpel moet nog permissies en dingen checken
{
	char *buf;
	
	buf = malloc(sizeof(char) * ft_strlen(str[1]));
	if (buf && chdir(str[1]) < 0)
	{	
		ft_putstr_fd("sh: cd: ", 2);
		ft_putstr_fd(str[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else
		return (-1);
	return (1);
}
