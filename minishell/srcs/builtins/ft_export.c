/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:29:51 by dso               #+#    #+#             */
/*   Updated: 2022/02/04 17:58:39 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_check_export(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static char	**d_put_export(char *cmd)
{
	char	**new;
	int		size;
	int		i;

	size = d_count_tab(g_mini_env);
	new = malloc(sizeof(char *) * (size + 2));
	i = 0;
	while (g_mini_env[i])
	{
		new[i] = d_strdup(g_mini_env[i]);
		i++;
	}
	new[i] = d_strdup(cmd);
	i++;
	new[i] = 0;
	i = 0;
	return (new);
}

void	ft_export(char **cmds)
{
	int		i;
	char	**new_env;

	i = 1;
	if (!cmds[1])
	{
		i = -1;
		while (g_mini_env[++i])
			printf("declare -x %s\n", g_mini_env[i]);
		return ;
	}
	while (cmds[i])
	{
		if (cmds[i][0] == '=')
		{
			printf("export : \'%s\': not a valid identifier\n", cmds[i]);
			return ;
		}
		else if (d_check_export(cmds[i]) == 1)
		{
			new_env = d_put_export(cmds[i]);
			if (!new_env)
				exit(EXIT_FAILURE);
			d_free_tab(g_mini_env);
			g_mini_env = new_env;
		}
		i++;
	}
	return ;
}
