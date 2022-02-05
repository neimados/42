/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:01:34 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 17:46:23 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	k_error(char *str1, char *str2, char **env)
{
	char	*str0;
	int		i;

	i = 0;
	while (env[i] && (env[i][0] != 'S' || env[i][1] != 'H' || env[i][2] != 'E'
	|| env[i][3] != 'L' || env[i][4] != 'L'))
		i++;
	if (env[i][0] != 'S' && env[i][1] != 'H' && env[i][2] != 'E'
	&& env[i][3] != 'L' && env[i][4] != 'L')
		str0 = NULL;
	else
		str0 = ft_strrchr(env[i], '/');
	write(2, str0 + 1, ft_strlen(str0 + 1));
	if (str1)
		write(2, ": ", 2);
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	return ;
}

void	ft_cd(char **cmds)
{
	char	*old;
	char	*oldjoin;
	int		i;
	int		j;
	char	*tmp;
	char	**tmp2;
	char	**oldsplit;

	tmp = NULL;
	tmp2 = g_mini_env;
	if (cmds[2])
	{
		k_error("cd: string not in pwd:", cmds[1], NULL);
		return ;
	}
	i = 0;
	j = 0;
	if (!d_strncmp(cmds[1], ".", d_strlen(cmds[1])) || !d_strncmp(cmds[1], "\"\"", d_strlen(cmds[1])) || !d_strncmp(cmds[1], "\'\'", d_strlen(cmds[1])))
		return ;
	while (g_mini_env[i])
	{
		if (g_mini_env[i][0] == 'P' && g_mini_env[i][1] == 'W'
		&& g_mini_env[i][2] == 'D' && g_mini_env[i][3] == '=')
		{
			old = ft_strjoin("OLD", g_mini_env[i]);
			//free(g_mini_env[i]);
		}
		i++;
	}
	if (!cmds[1] || !d_strncmp(cmds[1], "--", d_strlen(cmds[1])) || !d_strncmp(cmds[1], "~", d_strlen(cmds[1])))
	{
		while (g_mini_env[j])
		{
			if (!d_strncmp(g_mini_env[j], "HOME=", d_strlen(g_mini_env[j])))
			{
				tmp = d_substr(g_mini_env[j], 5, d_strlen(g_mini_env[j] + 5));
				g_mini_env[i] = d_strjoin("PWD=", tmp);
				//free(tmp);
			}
			j++;
		}
	}
	else if (!d_strncmp(cmds[1], "..", d_strlen(cmds[1])))
	{
		g_mini_env[i] = d_substr(old, 3, d_strlen(old + 3) - d_strlen(ft_strrchr(old, '/')));
		if (!g_mini_env[i])
			k_error("cd : malloc error", cmds[1], NULL);
		dprintf(2, "test1 == %s\n", g_mini_env[i]);
	}
	else if (!d_strncmp(cmds[1], "-", d_strlen(cmds[1])))
	{
		while (g_mini_env[j])
		{
			if (!d_strncmp(g_mini_env[j], "OLDPWD=", d_strlen(g_mini_env[j])))
			{
				tmp = d_substr(g_mini_env[j], 7, d_strlen(g_mini_env[j] + 7));
				g_mini_env[i] = d_strjoin("PWD=", tmp);
				//free (tmp);
			}
			j++;
		}
	}
	else if (cmds[1][0] == '/')
	{
		g_mini_env[i] = cmds[1];
	}
	else
	{
		g_mini_env[i] = ft_strjoin(old + 3, cmds[1]);
	}
	i = 0;
	j = 0;
	while (g_mini_env[i])
	{
		dprintf(2, "env == %s\n", g_mini_env[i]);
		if (!d_strncmp(g_mini_env[i], "OLDPWD=", d_strlen(g_mini_env[i])))
		{
			//free(g_mini_env[i]);
			g_mini_env[i] = old;
			j = 1;
		}
		i++;
	}
	if (j == 0)
	{
		oldjoin = ft_strjoin("export ", old);
		oldsplit = ft_split(oldjoin, ' ');
		ft_export(oldsplit);
		//free(oldsplit[0]);
		//free(oldsplit[1]);
		//free(oldsplit);
	}
	//free(old);
	if (chdir(cmds[1]) == -1)
	{
		g_mini_env = tmp2;
		dprintf(2, "test %s\n", g_mini_env[0]);
		k_error(strerror(errno), cmds[1], g_mini_env);
		return ;
	}
	dprintf(2, "test2 %s\n", g_mini_env[0]);
}
