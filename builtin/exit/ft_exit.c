/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 12:03:50 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/10/23 18:52:22 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	all_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
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
	tcsetattr(0, 0, &g_global.termios_save);
	ft_putendl_fd(str, 2);
	exit(ret);
}

int	check_errors(char **str, int i)
{
	if (all_num(str[1]) || !ft_strncmp(str[1], "-", 2))
	{
		ft_putstr_fd("minishell-4.2$: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		print_and_exit(": numeric argument required", 255);
	}
	if (i > 2)
	{
		ft_putendl_fd("minishell-4.2$: exit: too many arguments", 2);
		return (1);
	}
	if (ft_atoi(str[1]) != ft_atoi_l(str[1]))
	{
		ft_putstr_fd("minishell-4.2$: exit: ", 2);
		ft_putstr_fd(str[1], 2);
		print_and_exit(": numeric argument required", 255);
	}
	return (0);
}

void	ft_exit(char **str)
{
	int				i;
	unsigned char	ret;

	i = 0;
	while (str[i])
		i++;
	tcsetattr(0, 0, &g_global.termios_save);
	if (i == 1)
		exit(0);
	if (check_errors(str, i))
	{
		g_global.status = 1;
		return ;
	}
	ret = ft_atoi(str[1]);
	exit(ret);
}
