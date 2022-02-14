/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:56:43 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 14:59:10 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_check_path(char *variable, char *env)
{
	int		i;
	int		start;
	char	*value;

	i = 0;
	start = 0;
	while (variable[i])
	{
		if (variable[i] != env[i])
			return (NULL);
		i++;
	}
	if (env[i] != '=')
		return (NULL);
	i++;
	start = i;
	while (env[i])
		i++;
	value = d_substr(env, start, i - start);
	return (value);
}

char	*d_var_err(void)
{
	char	*var;

	var = d_strdup(g_error[0]);
	return (var);
}

char	*d_loop_vars3(char *tmp, int i, t_minishell *mshell, char *str)
{
	int		start;
	char	*variable;
	char	*value;
	int		j;

	start = i;
	j = 0;
	while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != ' ')
		i++;
	variable = d_substr(tmp, start, i - start);
	while (mshell->g_mini_env[j])
	{
		if (variable[0] == mshell->g_mini_env[j][0])
		{
			value = d_check_path(variable, mshell->g_mini_env[j]);
			if (value)
			{
				str = d_strjoin(str, value);
				free(value);
			}
		}
	j++;
	}
	free(variable);
	return (str);
}

int	d_skip_vars3(char *tmp, int i)
{
	while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != ' ')
		i++;
	return (i);
}
