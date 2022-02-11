/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:02:16 by dso               #+#    #+#             */
/*   Updated: 2022/02/08 12:20:34 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**d_replace_env(int found, t_minishell *mshell)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char *) * (d_count_tab(mshell->g_mini_env) + 1));
	if (!new)
		return (NULL);
	while (mshell->g_mini_env[i])
	{
		if (i != found)
		{
			new[j] = d_strdup(mshell->g_mini_env[i]);
			j++;
		}
		i++;
	}
	new[j] = 0;
	d_free_tab(mshell->g_mini_env);
	return (new);
}

static int	d_find_line(char *tmp, t_minishell *mshell)
{
	int		i;
	int		j;
	char	*line;

	i = -1;
	j = 0;
	(void)tmp;
	while (mshell->g_mini_env[++i])
	{
		while (mshell->g_mini_env[i][j] && mshell->g_mini_env[i][j] != '=')
			j++;
		line = d_substr(mshell->g_mini_env[i], 0, j);
		if (d_strncmp(line, tmp, d_strlen(tmp)) == 0)
		{
			j = i;
			mshell->g_mini_env = d_replace_env(i, mshell);
			if (!mshell->g_mini_env)
				return (1);
			free(line);
			return (0);
		}
		j = 0;
		free(line);
	}
	return (0);
}

static int	d_put_unset(int count, char *cmd, t_minishell *mshell)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = d_calloc((count + 1), sizeof(char));
	if (!tmp)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] != '\'' && cmd[i] != '\"')
		{
			tmp[j] = cmd[i];
			j++;
		}
		i++;
	}
	i = 0;
	if (d_find_line(tmp, mshell) == 1)
		return (1);
	free(tmp);
	return (0);
}

void	ft_unset(char **cmds, t_minishell *mshell)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	j = 0;
	count = 0;
	while (cmds[i])
	{
		while (cmds[i][j])
		{
			if (cmds[i][j] != '\'' && cmds[i][j] != '\"')
				count++;
			j++;
		}
		if (count != 0)
			if (d_put_unset(count, cmds[i], mshell) == 1)
				return ;
		i++;
		j = 0;
		count = 0;
	}
	return ;
}
