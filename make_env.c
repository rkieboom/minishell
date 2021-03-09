/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   make_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/09 16:50:13 by rkieboom      #+#    #+#                 */
/*   Updated: 2021/03/09 16:51:58 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void	make_env(char **envp, t_list *list)
{
	int i;
	char	**temp;
	(void)list;

	i = 0;
	t_env	*head = NULL;
	while (envp[i])
	{
		temp = ft_split(envp[i], '=');
		if (head == NULL)
			head = env_lst_new(temp[0], temp[1]);
		else
			env_lstadd_back(&head, env_lst_new(temp[0], temp[1]));
		i++;
	}
	// PRINT LIST
	// for(t_env *test = head; test; test = test->next)
	// {
	// 	printf("name = [%s], content = [%s]\n", test->name, test->content);
	// }
}