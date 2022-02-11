/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:01:34 by dso               #+#    #+#             */
/*   Updated: 2022/02/09 20:00:36 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	k_error(char *str1, char *str2)
{
	if (str1[0])
		write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	return ;
}

int	ft_strncmp(const char *first, const char *second, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len - 1 && first[i] == second[i] && first[i])
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}

void	ft_cd(char **cmds, t_minishell *minishell)
{
	char	*old;
	char	*oldjoin;
	int		i;
	int		j;
	char	*tmp;
	char	**tmp2;
	char	**oldsplit;

	tmp = NULL;
	old = NULL;
	i = 0;
	while (minishell->g_mini_env[i])
		i++;
	tmp2 = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (minishell->g_mini_env[i])
	{
		tmp2[i] = ft_strdup(minishell->g_mini_env[i]);
		i++;
	}
	tmp2[i] = NULL;
	i = 0;
	j = 0;
	while (minishell->g_mini_env[i])
	{
		if (minishell->g_mini_env[i][0] == 'P' && minishell->g_mini_env[i][1] == 'W'
		&& minishell->g_mini_env[i][2] == 'D' && minishell->g_mini_env[i][3] == '=')
		{
			old = ft_strjoin("OLDPWD=", minishell->pwd);
			j = i;
		}
		i++;
	}
	if (cmds[1])
	{
		if (cmds[2])
		{
			d_free_tab(tmp2);
			if (old)
				free(old);
			k_error("cd: string not in pwd:", cmds[1]);
			return ;
		}
		else if (!d_strncmp(cmds[1], ".", d_strlen(cmds[1])) || !d_strncmp(cmds[1], "\"\"", d_strlen(cmds[1])) || !d_strncmp(cmds[1], "\'\'", d_strlen(cmds[1])))
		{
			d_free_tab(tmp2);
			if (old)
				free(old);
			return ;
		}
	}
	if (!cmds[1] || !d_strncmp(cmds[1], "--", d_strlen(cmds[1])) || !d_strncmp(cmds[1], "~", d_strlen(cmds[1])))
	{
		i = 0;
		while (minishell->g_mini_env[i])
		{
			if (!ft_strncmp(minishell->g_mini_env[i], "HOME=", 5))
			{
				free(minishell->g_mini_env[j]);
				tmp = d_substr(old, 5, d_strlen(old + 5));
				minishell->g_mini_env[j] = ft_strjoin("PWD=", tmp);
				minishell->pwd = ft_strjoin("PWD=", tmp);
				free(tmp);
			}
			i++;
		}
	}
	else if (!d_strncmp(cmds[1], "..", d_strlen(cmds[1])))
	{
		if (j != 0)
			free(minishell->g_mini_env[j]);
		if (old)
		{
			tmp = d_substr(old, 3, d_strlen(old + 3) - d_strlen(ft_strrchr(old, '/')));
			minishell->g_mini_env[j] = ft_strjoin(tmp, "\0");
			free(tmp);
		}
		tmp = d_substr(minishell->pwd, 0, d_strlen(minishell->pwd) - d_strlen(ft_strrchr(minishell->pwd, '/')));
		if (tmp[0] == '\0')
			minishell->pwd = d_strjoin(tmp, "/\0");
		else
			minishell->pwd = d_strjoin(tmp, "\0");
		if (!d_strncmp("/", minishell->pwd, d_strlen(minishell->pwd)))
		{
			free(minishell->pwd);
			free(minishell->g_mini_env[j]);
			minishell->pwd = ft_strdup("/");
			minishell->g_mini_env[j] = ft_strdup("PWD=/");
		}
		tmp = NULL;
	}
	else if (!d_strncmp(cmds[1], "-", d_strlen(cmds[1])))
	{
		i = 0;
		while (minishell->g_mini_env[i])
		{
			if (!ft_strncmp(minishell->g_mini_env[i], "OLDPWD=", 7))
			{
				free(minishell->g_mini_env[j]);
				tmp = d_substr(minishell->g_mini_env[i], 7, d_strlen(minishell->g_mini_env[i] + 7));
				minishell->g_mini_env[j] = ft_strjoin("PWD=", tmp);
				free(minishell->pwd);
				minishell->pwd = ft_strjoin(tmp, "\0");
				free (tmp);
			}
			i++;
		}
	}
	else if (cmds[1][0] == '/')
	{
		free(minishell->g_mini_env[j]);
		minishell->g_mini_env[j] = cmds[1];
		minishell->pwd = cmds[1];
	}
	else
	{
		free(minishell->g_mini_env[j]);
		if (!d_strncmp("/", minishell->pwd, d_strlen(minishell->pwd)))
			tmp = ft_strdup(minishell->pwd);
		else
			tmp = ft_strjoin(minishell->pwd, "/");
		minishell->pwd = ft_strjoin(tmp, cmds[1]);
		if (old)
		{
			minishell->g_mini_env[j] = ft_strjoin("PWD=", tmp);
			free (tmp);
			tmp = ft_strjoin(minishell->g_mini_env[j], cmds[1]);
			free(minishell->g_mini_env[j]);
			minishell->g_mini_env[j] = tmp;
		}
		free(tmp);
	}
	i = 0;
	j = 0;
	dprintf(2, "old == %s\n", old);
	while (minishell->g_mini_env[i] && old)
	{
		if (!d_strncmp(minishell->g_mini_env[i], "OLDPWD=", 7))
		{
			free(minishell->g_mini_env[i]);
			minishell->g_mini_env[i] = ft_strjoin("OLDPWD=", minishell->pwd);
			j = 1;
		}
		i++;
	}
	if (j == 0)
	{
		if (old)
			oldjoin = ft_strjoin("export ", old);
		else
			oldjoin = ft_strjoin("export ", "OLDPWD=");
		oldsplit = ft_split(oldjoin, ' ');
		ft_export(oldsplit, minishell);
		d_free_tab(oldsplit);
		free(oldjoin);
	}
	if (cmds[1] && chdir(cmds[1]) == -1 && !d_strncmp(cmds[1], "-", d_strlen(cmds[1])) & !d_strncmp(cmds[1], "--", d_strlen(cmds[1])))
	{
		i = 0;
		minishell->pwd = old;
		d_free_tab(minishell->g_mini_env);
		free(old);
		minishell->g_mini_env = tmp2;
		k_error(strerror(errno), cmds[1]);
		return ;
	}
	i = 0;
	d_free_tab(tmp2);
}
