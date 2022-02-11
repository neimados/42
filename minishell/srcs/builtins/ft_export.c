/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 14:29:51 by dso               #+#    #+#             */
/*   Updated: 2022/02/08 12:58:50 by dso              ###   ########.fr       */
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

static int	d_exist_var(char **env, char *cmd, int i)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = 0;
	while (cmd[i] != '=')
		i++;
	tmp = d_substr(cmd, 0, i);
	i = -1;
	while (env[++i])
	{
		while (env[i][j] != '=')
			j++;
		tmp2 = d_substr(env[i], 0, j);
		if (d_strncmp(tmp, tmp2, d_strlen(tmp)) == 0)
		{
			free(tmp2);
			free(tmp);
			return (i);
		}
		j = 0;
		free(tmp2);
	}
	free(tmp);
	return (0);
}

static char	**d_put_export(char *cmd, t_minishell *mshell)
{
	char	**new;
	int		size;
	int		i;
	int		exist;

	i = 0;
	size = d_count_tab(mshell->g_mini_env);
	exist = d_exist_var(mshell->g_mini_env, cmd, i);
	if (exist == 0)
		new = d_calloc((size + 2), sizeof(char *));
	else
		new = d_calloc((size + 1), sizeof(char *));
	if (!new)
		return (NULL);
	while (mshell->g_mini_env[i])
	{
		if (exist != 0 && exist == i)
			new[i] = d_strdup(cmd);
		else
			new[i] = d_strdup(mshell->g_mini_env[i]);
		i++;
	}
	if (exist == 0)
		new[i] = d_strdup(cmd);
	return (new);
}

void	d_print_declare_export(t_minishell *mshell)
{
	int	i;

	i = -1;
	while (mshell->g_mini_env[++i])
		printf("declare -x %s\n", mshell->g_mini_env[i]);
	return ;
}

void	ft_export(char **cmds, t_minishell *mshell)
{
	int		i;
	char	**new_env;

	i = 1;
	if (!cmds[1])
		return (d_print_declare_export(mshell));
	while (cmds[i])
	{
		if (cmds[i][0] == '=')
		{
			printf("export : \'%s\': not a valid identifier\n", cmds[i]);
			return ;
		}
		else if (d_check_export(cmds[i]) == 1)
		{
			new_env = d_put_export(cmds[i], mshell);
			if (!new_env)
				exit(EXIT_FAILURE);
			d_free_tab(mshell->g_mini_env);
			mshell->g_mini_env = new_env;
		}
		i++;
	}
	return ;
}
