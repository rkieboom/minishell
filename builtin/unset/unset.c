/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spelle <spelle@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/05/19 20:01:05 by spelle        #+#    #+#                 */
/*   Updated: 2022/10/23 02:35:57 by rkieboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[0]) || str[0] == '_')
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		if (!str[i])
			return (1);
	}
	ft_putstr_fd("minishell-4.2$: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (0);
}

int	unset(t_env **v, char **str)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (str[i])
	{
		if (valid_identifier(str[i]))
			env_lst_remove(v, str[i]);
		else
			error = 1;
		i++;
	}
	return (error);
}


// TERM_SESSION_ID SSH_AUTH_SOCK LC_TERMINAL_VERSION COLORFGBG ITERM_PROFILE XPC_FLAGS PWD SHELL __CFBundleIdentifier LC_CTYPE TERM_PROGRAM_VERSION TERM_PROGRAM PATH LC_TERMINAL COLORTERM COMMAND_MODE TERM HOME TMPDIR USER XPC_SERVICE_NAME LOGNAME ITERM_SESSION_ID __CF_USER_TEXT_ENCODING SHLVL OLDPWD HOMEBREW_PREFIX HOMEBREW_CELLAR HOMEBREW_REPOSITORY MANPATH INFOPATH P9K_TTY _P9K_TTY ZSH PAGER LESS LSCOLORS P9K_SSH 