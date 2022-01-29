/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:54:24 by dso               #+#    #+#             */
/*   Updated: 2022/01/28 12:52:57 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_cp_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	g_mini_env = malloc(sizeof(char *) * (i + 1));
	if (!g_mini_env)
	{
		write(2, "Malloc Error\n", 13);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		g_mini_env[i] = d_strdup(envp[i]);
		i++;
	}
	g_mini_env[i] = 0;
}