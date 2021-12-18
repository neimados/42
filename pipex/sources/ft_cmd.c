/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:40:31 by dso               #+#    #+#             */
/*   Updated: 2021/12/17 16:33:15 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_search_path_line(char *envp)
{
	int	i;

	i = 0;
	if (envp[0] == 'P' && envp[1] == 'A' && envp[2] == 'T'
		&& envp[3] == 'H')
		return (1);
	return (0);
}

static int	ft_check_cmd(char *path_line, char **cmds, char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = ft_calloc((ft_strlen(path_line) + 2), sizeof(char));
	if (!path)
		return (1);
	while (path_line[i])
	{
		path[i] = path_line[i];
		i++;
	}
	path[i] = '/';
	path = ft_strjoin(path, cmds[0]);
	if (access(path, F_OK) == 0)
	{
		execve(path, cmds, envp);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	ft_cmd(char *argv, char **envp)
{
	char	**cmds;
	char	**paths;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmds = ft_split(argv, ' ');
	while (ft_search_path_line(envp[i]) == 0 && envp[i])
		i++;
	paths = ft_split(envp[i] + 5, ':');
	while (paths[j])
	{
		if (ft_check_cmd(paths[j], cmds, envp) == 1)
		{
			freemalloc(cmds);
			freemalloc(paths);
			ft_error();
		}
		j++;
	}
	return (1);
}
