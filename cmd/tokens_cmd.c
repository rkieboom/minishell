/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 16:25:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/04/10 15:03:39 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"
static int	get_last_id(t_newcommand *v)
{
	while (v->next)
		v = v->next;
	return (v->id);
	
}

static int	ret_token_pos(t_list *v, t_newcommand *pipes, int k, int *wc)
{
	while (1)
	{
		if (!v->tokens[k].token[*wc])
			return (-1);
		if (ft_strncmp(v->tokens[k].token[*wc], "|", 2))
			return (v->tokens[k].token_pos[*wc]);
		(*wc)++;
	}
	
}

static char	*ret_token(t_list *v, t_newcommand *pipes, int k, int token_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i - j != token_count)
	{
		if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
			j++;
		i++;
	}
	return (v->tokens[k].token[i]);
}

static void	set_tokens(t_list *v, t_newcommand *pipes, int k)
{
	t_newcommand	*temp;	
	int				tokens;
	int				i;
	int				token_c;
	int				token_local_c;

	token_c = 0;
	token_local_c = 0; //cat gfnoiesd ndi < fbnudsif > fdiubsfd | hallo hier daar < > ^ | hallooooooooooo poep | doei | doei | poep
	temp = pipes; //cat gfnoiesd ndi < fbnudsif > fdiubsfd | hallo hier daar < > ^ | hallooooooooooo "<" poep | doei < cat | doei | poep
	while (1)
	{
		i = 0;
		tokens = temp->tokens->total;
		while (tokens)
		{
			temp->tokens->token[token_local_c] = ft_strdup(ret_token(v, pipes, k, token_c));
			if (!temp->tokens->token[token_local_c])
				ft_exit(1, 1);
			temp->tokens->token_pos[token_local_c] = i;
			token_c++;
			token_local_c++;
			tokens--;
			i++;
		}
		temp = temp->next;
		if (!temp)
			break ;
		token_local_c = 0;
	}
}

//	cat main.c > test.output.txt | wc -l | sort < main.c
//	----------------------------------------------------
//	[0] cat main.c > test.output.txt		1x
//	[1]	wc -l								0x 
//	[2]	sort < main.c						1x


static void	count_tokens(t_list *v, t_newcommand *temp, int k)//cat gfnoiesd ndi < fbnudsif > fdiubsfd | hallo hier daar < > ^ | hallooooooooooo poep | doei | doei | poep
{
	int	i;
	int	t;
	int	wc;

	i = 0;
	wc = 0;
	t = 0;
	while (temp) //cat < main.c > text.txt | grep # > output.txt | grep @
	{
		if (v->tokens[k].token[t] && !ft_strncmp(v->tokens[k].token[t], "|", 2))
			t++;
		if (!ft_strncmp(temp->command[i], ">>", 3) && v->tokens[k].token_pos[t] == i + wc + temp->id)
		{
			temp->tokens->double_redirection_right++;
			t++;
		}
		else if (!ft_strncmp(temp->command[i], "<<", 3) && v->tokens[k].token_pos[t] == i + wc + temp->id)
		{
			temp->tokens->double_redirection_left++;
			t++;
		}
		else if (!ft_strncmp(temp->command[i], ">", 2) && v->tokens[k].token_pos[t] == i + wc + temp->id)
		{
			temp->tokens->single_redirection_right++;
			t++;
		}
		else if (!ft_strncmp(temp->command[i], "<", 2) && v->tokens[k].token_pos[t] == i + wc + temp->id)
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
			wc += i;
			i = 0;
			temp = temp->next;//cat main.c > output.txt | wc -l < output.txt
			if (t == v->tokens[k].total)
				break ;
		}
	}
}

static void	init_new_tokens(t_list *v, t_newcommand *cmd, int k)
{
	int	i;
	int	t;
	t_newcommand *temp; //1. cat main.c > output.txt | wc -l < main.c

	temp = cmd;
	while (temp)
	{
		temp->tokens->token = ft_calloc(temp->tokens->total + 1, sizeof(char *));
		if (!temp->tokens->token)
			ft_error("Malloc failed!\n");
		temp->tokens->token[temp->tokens->total] = 0;
		temp->tokens->token_pos = ft_calloc(temp->tokens->total + 1, sizeof(int));
		if (!temp->tokens->token_pos)
			ft_error("Malloc failed!\n");
		temp->tokens->token_pos[temp->tokens->total] = 0;
		temp = temp->next;
	}
	
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
	

void	tokens_cmd(t_list *v, t_newcommand *cmd, int k)
{
	int	i;

	i = 0;
	t_newcommand *temp;

	temp = cmd;
	if (v->tokens[k].total == 0)
		return ;
	while (temp)
	{
		temp->tokens = ft_calloc(1, sizeof(t_tokens));
		if (!temp->tokens)
			ft_exit(1, 1);
		temp = temp->next;
	}
	count_tokens(v, cmd, k); //cat gfnoiesd ndi < fbnudsif > fdiubsfd | hallo hier daar < > ^ | hallooooooooooo "<" poep | doei < cat | doei < dag | poep < poep | poep
	if (cmd->tokens->total == 0)
		return ;
	init_new_tokens(v, cmd, k);
	set_tokens(v, cmd, k);
}
