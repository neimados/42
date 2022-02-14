/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:54:24 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 18:10:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_cp_env_err(void)
{
	write(2, "Malloc Error\n", 13);
	exit(EXIT_FAILURE);
}

static int	ft_search_oldpwd(char **envp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'O' && envp[i][1] == 'L' && envp[i][2] == 'D'
		&& envp[i][3] == 'P' && envp[i][4] == 'W' && envp[i][5] == 'D'
		&& envp[i][6] == '=')
			count--;
		count++;
		i++;
	}
	return (count);
}

static void	d_search_pwd(t_minishell *mshell)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = d_calloc(i, sizeof(char));
	if (!buffer)
		return ;
	while (buffer == NULL || buffer[0] == '\0')
	{
		free(buffer);
		buffer = d_calloc(i, sizeof(char));
		getcwd(buffer, i);
		i++;
	}
	mshell->pwd = buffer;
}

void	ft_cp_env(char **envp, t_minishell *mshell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	d_search_pwd(mshell);
	mshell->g_mini_env = malloc(sizeof(char *) * (ft_search_oldpwd(envp) + 1));
	if (!mshell->g_mini_env)
		d_cp_env_err();
	while (envp[i])
	{
		if (envp[i][0] == 'O' && envp[i][1] == 'L' && envp[i][2] == 'D'
		&& envp[i][3] == 'P' && envp[i][4] == 'W' && envp[i][5] == 'D'
		&& envp[i][6] == '=')
			i++;
		else
		{
			mshell->g_mini_env[j] = d_strdup(envp[i]);
			if (!mshell->g_mini_env[j])
				d_cp_env_err();
			i++;
			j++;
		}
	}
	mshell->g_mini_env[j] = 0;
}
