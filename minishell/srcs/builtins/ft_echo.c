/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:00:43 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 13:30:44 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_loop_echo(char *cmd, int *count)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] != '\'' && cmd[i] != '\"')
		{
			printf("%c", cmd[i]);
			*count += 1;
		}
		i++;
	}
}

void	ft_echo(char **cmds)
{
	int	i;
	int	n;
	int	size;
	int	count;

	i = 1;
	n = 0;
	size = d_count_tab(cmds);
	if (size == 1)
		exit(EXIT_SUCCESS);
	if (cmds[1][0] == '-' && cmds[1][1] == 'n')
	{
		n = 1;
		i = 2;
	}
	while (cmds[i])
	{
		d_loop_echo(cmds[i], &count);
		i++;
		if (i < size && count != 0)
			printf(" ");
		count = 0;
	}
	if (n == 0)
		printf("\n");
	exit(EXIT_SUCCESS);
}
