/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 12:29:32 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **cmds)
{
	int	i;

	i = 0;
	if (cmds[1])
	{
		printf("pwd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	while (g_mini_env[i])
	{
		if (g_mini_env[i][0] == 'P' && g_mini_env[i][1] == 'W'
		&& g_mini_env[i][2] == 'D' && g_mini_env[i][3] == '=')
		{
			printf("%s\n", g_mini_env[i] + 5);
		}
		i++;
	}
	exit(EXIT_SUCCESS);
}