/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:00:43 by dso               #+#    #+#             */
/*   Updated: 2022/02/04 17:33:29 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **cmds)
{
	int	i;
	int	j;
	int	n;
	int	size;
	int	count;

	i = 1;
	j = 0;
	n = 0;
	size = d_count_tab(cmds);
	if (cmds[1][0] == '-' && cmds[1][1] == 'n')
	{
		n = 1;
		i = 2;
	}
	while (cmds[i])
	{
		while (cmds[i][j])
		{
			if (cmds[i][j] != '\'' && cmds[i][j] != '\"')
			{
				printf("%c", cmds[i][j]);
				count++;
			}
			j++;
		}
		i++;
		j = 0;
		if (i < size && count != 0)
			printf(" ");
		count = 0;
	}
	if (n == 0)
		printf("\n");
	exit(EXIT_SUCCESS);
}
