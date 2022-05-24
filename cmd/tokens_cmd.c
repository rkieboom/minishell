/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokens_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkieboom <rkieboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 16:25:48 by rkieboom      #+#    #+#                 */
/*   Updated: 2022/05/21 19:48:04 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

static char	*ret_token(t_list *v, int k, int token_count)
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
	if (token_count == 0)
		while (1)
		{
			if (!ft_strncmp(v->tokens[k].token[i], "|", 2))
				j++;
			else
				return (v->tokens[k].token[i]);
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
	token_local_c = 0;													// cat main.c | > output.txt
	temp = pipes;
	while (1)
	{
		i = 0;
		tokens = temp->tokens->total;
		while (tokens)
		{
			temp->tokens->token[token_local_c] = ft_strdup(ret_token(v, k, token_c));//hier gaat iets fout
			if (!temp->tokens->token[token_local_c])
				ft_ret_exit(1, 1);
			temp->tokens->token_pos[token_local_c] = v->tokens[k].token_pos[token_c];//klopt niks van
			// printf("cmd = %s\n", temp->command[0]);
			// printf("token = [%s]\n", temp->tokens->token[0]);
			// printf("token_pos = [%i]\n\n\n", temp->tokens->token_pos[0]);
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
	while (temp)
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
			temp = temp->next;
			if (t == v->tokens[k].total)
				break ;
		}
	}
}

static void	init_new_tokens(t_newcommand *cmd)
{
	t_newcommand *temp;

	temp = cmd;
	while (temp)
	{
		if (temp->tokens && temp->tokens->total > 0)
		{
			temp->tokens->token = ft_calloc(temp->tokens->total + 1, sizeof(char *));
			if (!temp->tokens->token)
				ft_ret_exit(1, 1);
			temp->tokens->token[temp->tokens->total] = 0;
			temp->tokens->token_pos = ft_calloc(temp->tokens->total + 1, sizeof(int));
			if (!temp->tokens->token_pos)
				ft_ret_exit(1, 1);
			temp->tokens->token_pos[temp->tokens->total] = 0;
		}
		temp = temp->next;
	}
}

void	tokens_cmd(t_list *v, t_newcommand *cmd, int k)
{
	t_newcommand *temp;

	temp = cmd;
	if (v->tokens[k].total == 0)
		return ;
	while (temp)
	{
		temp->tokens = ft_calloc(1, sizeof(t_tokens));
		if (!temp->tokens)
			ft_ret_exit(1, 1);
		temp = temp->next;
	}
	count_tokens(v, cmd, k);
	
	init_new_tokens(cmd);
	set_tokens(v, cmd, k);
}
