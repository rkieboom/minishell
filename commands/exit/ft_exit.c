/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 12:03:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/09/04 15:52:14 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	all_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	print_and_exit(char *str, int ret)
{
	ft_putendl_fd(str, 2);
	exit(ret);
}

void	check_errors(char **str, int i)
{
	if (all_num(str[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		print_and_exit(": numeric argument required", 255);
	}
	if (i > 2)
		print_and_exit("minishell: exit: too many arguments", 1);
	if (ft_atoi(str[1]) != ft_atoi_l(str[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		print_and_exit(": numeric argument required", 255);
	}
}

void	ft_exit(char **str)
{
	int				i;
	unsigned char	ret;

	i = 0;
	while (str[i])
		i++;
	if (i == 1)
		exit(0);
	check_errors(str, i);
	ret = ft_atoi(str[1]);
	exit(ret);
}
