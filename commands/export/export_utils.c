/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/03 16:07:54 by spelle        #+#    #+#                 */
/*   Updated: 2021/11/04 18:13:37 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"
#include <string.h>

static void	swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

static void	create_declare_list(t_env *v, char **array)
{
	int	i;

	i =  0;
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
	int i;
	int j;
	size_t max;

	i = 0;
	while (i < length)
	{
		j = 0;
		while  (j < length - 1)
		{
			if (ft_strncmp(array[j], array[j + 1], ft_strlen(array[j]) + ft_strlen(array[j + 1])) > 0)
				swap(&array[j], &array[j + 1]);
			j++;
		}
		i++;
	}
}

static void	print_declare_list(char **array, t_env *v, size_t length)
{
	int i;
	
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
	int i;

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
	create_declare_list(v, array);
	sort_list(array, length);
	print_declare_list(array, v, length);
	free_arr(array);
}
