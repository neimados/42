/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:40:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 18:06:47 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*d_check_path(char *variable, char *env)
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

static char	*d_var_err(t_minishell *mshell)
{
	int		i;
	int		err;
	char	*var;

	i = 0;
	err = mshell->error;
	while (err != 0)
	{
		err /= 10;
		i++;
	}
	var = d_calloc((i + 1), sizeof(char));
	if (!var)
		return (NULL);
	var = d_itoa(mshell->error);
	return (var);
}

char	*d_check_vars(char *tmp, t_minishell *mshell)
{
	char	*str;
	int		i;
	int		j;
	int		count;
	int		start;
	char	*variable;
	char	*value;
	char	*carry;
	
	i = 0;
	j = 0;
	start = 0;
	count = 0;
	str = d_calloc(1, sizeof(char));
	while (tmp[i])
	{
		if (tmp[i] != '$')
		{
			start = i;
			if (tmp[i] == '\'')
			{
				i++;
				while (tmp[i] && tmp[i] != '\'')
					i++;
				i++;
			}
			else
			{
				while (tmp[i] && tmp[i] != '$')
					i++;
			}
			carry = d_substr(tmp, start, i - start);
			str = d_strjoin(str, carry);
			free(carry);
		}
		else
		{
			i++;
			if (tmp[i] >= '0' && tmp[i] <= '9')
				i++;
			else if (tmp[i] == '?')
			{
				value = d_var_err(mshell);
				if (!value)
					return (NULL);
				str = d_strjoin(str, value);
					free(value);
				i++;
			}
			else
			{
				start = i;
				while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"')
					i++;
				variable = d_substr(tmp, start, i - start);
				while (g_mini_env[j])
				{
					if (variable[0] == g_mini_env[j][0])
					{
						value = d_check_path(variable, g_mini_env[j]);
						if (value)
							str = d_strjoin(str, value);
						free(value);
					}
					j++;
				}
				free(variable);
			}
		}
	}
	i = 0;
	return (str);
}
