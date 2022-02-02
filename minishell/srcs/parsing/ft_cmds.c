/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 17:28:29 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_count_cmds(char **args)
{
	int		i;
	int		j;
	int		sign;
	int		count;

	i = 0;
	j = 0;
	sign = 0;
	count = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '>' || args[i][j] == '<')
			{
				sign++;
				j++;
			}
			else
			{
				if (sign == 0)
					count++;
				else
					sign = 0;
				while (args[i][j] && (args[i][j] != '>' && args[i][j] != '<'))
					j++;
			}
		}
		i++;
		j = 0;
	}
	return (count);
}

void	d_put_cmds(char **args, t_cmds *cmd, t_var *vars)
{
	int		i;
	int		j;
	int		k;
	int		sign;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	sign = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '>' || args[i][j] == '<')
			{
				sign++;
				j++;
			}
			else
			{
				while (args[i][j] && args[i][j] != '>' && args[i][j] != '<')
					j++;
				if (sign == 0)
				{
					tmp = d_substr(args[i], 0, j);
					cmd->cmd[k++] = d_check_vars(tmp, vars);
					free(tmp);
				}
				else
					sign = 0;
			}
		}
		i++;
		j = 0;
	}
}