/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 15:16:00 by dso              ###   ########.fr       */
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

static char	*d_trim_cmd(char *to_trim)
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
		if(to_trim[i] != '\'' && to_trim[i] != '\"')
			count++;
	}
	str = d_calloc((count + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (to_trim[++i])
	{
		if(to_trim[i] != '\'' && to_trim[i] != '\"')
			str[++j] = to_trim[i];
	}
	free(to_trim);
	return (str);
}

void	d_put_cmds(char **args, t_cmds *cmd, t_minishell *mshell)
{
	int		i;
	int		j;
	int		k;
	int		sign;
	char	*tmp;
	char	*to_trim;

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
					to_trim = d_check_vars(tmp, mshell);
					free(tmp);
					cmd->cmd[k] = d_trim_cmd(to_trim);
					if (!cmd->cmd[k])
						return ;
					k++;
				}
				else
					sign = 0;
			}
		}
		i++;
		j = 0;
	}
}
