/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 16:07:54 by spelle        #+#    #+#                 */
/*   Updated: 2022/09/21 21:37:27 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"
#include <string.h>

static void	create_declare_list(t_env *v, char **array)
{
	int	i;

	i = 0;
	while (v)
	{
		array[i] = ft_strdup(v->name);
		i++;
		v = v->next;
	}
	array[i] = NULL;
}

static void	sort_list(char **array, size_t length)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < length)
	{
		j = 0;
		while (j < length - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], \
			ft_strlen(array[j]) + ft_strlen(array[j + 1])) > 0)
				ft_swap(&array[j], &array[j + 1]);
			j++;
		}
		i++;
	}
}

static void	print_declare_list(char **array, t_env *v)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(array[i], 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(search_env(v, array[i], ft_strlen(array[i])), 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	export_declare_list(t_env *v)
{
	int		length;
	char	**array;

	length = env_lstsize(v);
	array = ft_calloc(length + 1, sizeof(char *));
	if (!array)
		ft_ret_exit(1, 1);
	create_declare_list(v, array);
	sort_list(array, length);
	print_declare_list(array, v);
	free_arr(array);
}
