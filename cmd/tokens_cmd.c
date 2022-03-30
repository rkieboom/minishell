/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 16:25:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/03/20 13:38:01 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
static int	get_last_id(t_pipecommand *v)
{
	while (v->next)
		v = v->next;
	return (v->id);
	
}

static int	ret_token_pos(t_list *v, t_pipecommand *pipes, int k, int *wc)
{
	while (1)
	{
		if (ft_strncmp(v->tokens[k].token[*wc], "|", 2))
			return (v->tokens[k].token_pos[*wc]);
		(*wc)++;
	}
	
}

static void	set_tokens(t_list *v, t_pipecommand *pipes, int k)
{
	int	i;
	int	wc;
	int	t;
	int temp;

	i = 0; //iterator
	wc = 0; //wordcount for token pos in vlist
	t = pipes->tokens->total; //total pipes in list
	while (1)
	{
		temp = ret_token_pos(v, pipes, k, &wc);
		while (i < temp - pipes->id)
		{
			if (!pipes->command[i])
			{
				pipes = pipes->next;
			}
			temp -= i;
			i = 0;
		}
		pipes->tokens->token[wc] = ft_strdup(pipes->command[i]);
		if (!pipes->tokens->token[wc])
			ft_error("Malloc failed!\n");
		wc++;

		
		// pipes->tokens->token[wc] = ft_strdup(pipes->command[ret_token_pos(v, pipes, k, wc) + pipes->id]);//??
		// if (!pipes->tokens->token[wc])
		// 	ft_error("Malloc failed!\n");
		// t--;
		// wc++;
	}
}

//	cat main.c > test.output.txt | wc -l | sort < main.c
//	----------------------------------------------------
//	[0] cat main.c > test.output.txt		1x
//	[1]	wc -l								0x 
//	[2]	sort < main.c						1x


static void	count_tokens(t_list *v, t_pipecommand *temp, int k)
{
	int	i;
	int	t;
	int	wc;

	i = 0;
	wc = 0;
	t = 0;
	while (temp)
	{
		if (!ft_strncmp(temp->command[i], ">>", 3) && v->tokens[k].token_pos[t] == i + wc)
		{
			temp->tokens->double_redirection_right++;
			t++;
		}
		else if (!ft_strncmp(temp->command[i], "<<", 3) && v->tokens[k].token_pos[t] == i + wc)
		{
			temp->tokens->double_redirection_left++;
			t++;
		}
		else if (!ft_strncmp(temp->command[i], ">", 2) && v->tokens[k].token_pos[t] == i + wc)
		{
			temp->tokens->single_redirection_right++;
			t++;
		}
		else if (!ft_strncmp(temp->command[i], "<", 2) && v->tokens[k].token_pos[t] == i + wc)
		{
			temp->tokens->single_redirection_left++;
			t++;
		}
		i++;
		if (!temp->command[i])
		{
			temp->tokens->total = temp->tokens->single_redirection_left + \
			temp->tokens->single_redirection_right + \
			temp->tokens->double_redirection_left + \
			temp->tokens->double_redirection_right;
			wc = i;
			i = 0;
			temp = temp->next;
		}
	}
}

static void	init_new_tokens(t_list *v, t_pipecommand *pipes, int k)
{
	int	i;
	int	t;
	t_pipecommand *temp;

	// while (i < k)//kan niet je krijgt 1 mee
	// {
	// 	temp = pipes[i];
	// 	count_tokens(v, temp, k);
		temp->tokens->token = ft_calloc(temp->tokens->total + 1, sizeof(char *));
		if (!temp->tokens->token)
			ft_error("Malloc failed!\n");
		temp->tokens->token_pos = ft_calloc(temp->tokens->total + 1, sizeof(int));
		if (!temp->tokens->token_pos)
			ft_error("Malloc failed!\n");
		// set_tokens(v, temp, k);
	// }
	
}

	
	// pipes->tokens[k].total = v->tokens[k].total - get_last_id(&pipes[k]);
	// temp = pipes->tokens[k].total;
	// pipes[k].tokens->token = ft_calloc(pipes->tokens[k].total + 1, sizeof(char *));
	// if (!pipes[k].tokens->token)
	// 	ft_error("Malloc failed!\n");
	// pipes[k].tokens->token_pos = ft_calloc(pipes->tokens[k].total + 1, sizeof(int));
	// if (!pipes[k].tokens->token_pos)
	// 	ft_error("Malloc failed!\n");
	// pipes->tokens[k].double_redirection_left = v->tokens[k].double_redirection_left;
	// pipes->tokens[k].double_redirection_right = v->tokens[k].double_redirection_right;
	// pipes->tokens[k].single_redirection_left = v->tokens[k].single_redirection_left;
	// pipes->tokens[k].single_redirection_right =  v->tokens[k].single_redirection_right;
	

void	tokens_cmd(t_list *v, t_pipecommand *pipes, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		pipes[k].tokens = ft_calloc(1, sizeof(t_tokens));
		if (!pipes[k].tokens)
			ft_error("Malloc failed!\n");
		i++;
	}
	count_tokens(v, pipes, k);
	init_new_tokens(v, pipes, k);
	set_tokens(v, pipes, k);
	
}
