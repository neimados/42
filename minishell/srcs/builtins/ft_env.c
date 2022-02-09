/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/07 12:55:30 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(char **cmds, t_minishell *mshell)
{
	int	i;

	i = 0;
	if (cmds[1])
	{
		printf("env: %s: No such file or directory\n", cmds[1]);
		exit(EXIT_FAILURE);
	}
	while (mshell->g_mini_env[i])
	{
		printf("%s\n", mshell->g_mini_env[i]);
		i++;
	}
	exit(EXIT_SUCCESS);
}
