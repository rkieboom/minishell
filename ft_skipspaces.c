/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_skipspaces.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 10:15:46 by rkieboom      #+#    #+#                 */
/*   Updated: 2020/11/29 10:39:11 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		skipspaces(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	return (i);
}
