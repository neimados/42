/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:40:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/11 10:40:00 by dso              ###   ########.fr       */
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

static char	*d_var_err(void)
{
	char	*var;

	var = d_strdup(g_error[0]);
	return (var);
}

static int	d_check_braces(char *tmp)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (tmp[i])
	{
		if (tmp[i] == '{')
			sign++;
		else if (tmp[i] == '}')
			sign = 0;
		i++;
	}
	if (sign == 0)
		return (0);
	d_putstr_fd("Error: Unclosed braces\n", 2);
	return (1);
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
	int		braces;
	
	i = 0;
	j = 0;
	start = 0;
	count = 0;
	braces = 0;
	str = d_calloc(1, sizeof(char));
	while (tmp[i])
	{
		if (tmp[i] != '$')
		{
			if (braces != 0)
			{
				if (tmp[i] == '}')
				{
					i++;
					braces = 0;
				}
			}
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
			else if (tmp[i] == '{')
			{
				if (d_check_braces(tmp) == 1)
					return (NULL);
				i++;
				braces++;
			}
			if (tmp[i] == '?')
			{
				value = d_var_err();
				if (!value)
					return (NULL);
				str = d_strjoin(str, value);
				free(value);
				i++;
			}
			else
			{
				start = i;
				if (braces != 0)
					while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"' && tmp[i] != '}' && tmp[i] != ' ')
						i++;
				else
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
				j = 0;
				free(variable);
			}
		}
	}
	return (str);
}
