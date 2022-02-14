/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:40:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 14:58:22 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_loop_vars(char *tmp, int i, char *str)
{
	int		start;
	char	*carry;

	start = i;
	if (tmp[i] == '\'')
	{
		i++;
		while (tmp[i] && tmp[i] != '\'')
			i++;
		i++;
	}
	else
		while (tmp[i] && tmp[i] != '$')
			i++;
	carry = d_substr(tmp, start, i - start);
	if (!carry)
		return (NULL);
	str = d_strjoin(str, carry);
	free(carry);
	if (!str)
		return (NULL);
	return (str);
}

int	d_skip_vars(char *tmp, int i)
{
	if (tmp[i] == '\'')
	{
		i++;
		while (tmp[i] && tmp[i] != '\'')
			i++;
		i++;
	}
	else
		while (tmp[i] && tmp[i] != '$')
			i++;
	return (i);
}

char	*d_loop_vars2(char *tmp, int i, char *str, t_minishell *mshell)
{
	char	*value;

	i++;
	if (tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	if (tmp[i] == '?')
	{
		value = d_var_err();
		if (!value)
			return (NULL);
		str = d_strjoin(str, value);
		if (!str)
			return (NULL);
		free(value);
		i++;
	}
	else
		str = d_loop_vars3(tmp, i, mshell, str);
	return (str);
}

int	d_skip_vars2(char *tmp, int i)
{	
	i++;
	if (tmp[i] >= '0' && tmp[i] <= '9')
		i++;
	if (tmp[i] == '?')
		i++;
	else
		i = d_skip_vars3(tmp, i);
	return (i);
}

char	*d_check_vars(char *tmp, t_minishell *mshell)
{
	char	*str;
	int		i;

	i = 0;
	str = d_calloc(1, sizeof(char));
	if (!str)
		return (NULL);
	while (tmp[i])
	{
		if (tmp[i] != '$')
		{
			str = d_loop_vars(tmp, i, str);
			if (!str)
				return (NULL);
			i = d_skip_vars(tmp, i);
		}
		else
		{
			str = d_loop_vars2(tmp, i, str, mshell);
			if (!str)
				return (NULL);
			i = d_skip_vars2(tmp, i);
		}
	}
	return (str);
}
