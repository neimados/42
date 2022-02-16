/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:16:07 by dso               #+#    #+#             */
/*   Updated: 2022/02/15 12:18:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_loop_count_cmds(char *arg)
{
	int	sign;
	int	count;
	int	i;

	sign = 0;
	count = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '>' || arg[i] == '<')
		{
			sign++;
			i++;
		}
		else
		{
			if (sign == 0)
				count++;
			else
				sign = 0;
			while (arg[i] && (arg[i] != '>' && arg[i] != '<'))
				i++;
		}
	}
	return (count);
}

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
		count += d_loop_count_cmds(args[i]);
		i++;
	}
	return (count);
}

char	*d_trim_cmd(char *to_trim)
{
	int		i;
	int		j;
	int		count;
	char	*str;

	i = -1;
	j = -1;
	count = 0;
	while (to_trim[++i])
	{
		if (to_trim[i] != '\'' && to_trim[i] != '\"')
			count++;
	}
	str = d_calloc((count + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (to_trim[++i])
	{
		if (to_trim[i] != '\'' && to_trim[i] != '\"')
			str[++j] = to_trim[i];
	}
	free(to_trim);
	return (str);
}
