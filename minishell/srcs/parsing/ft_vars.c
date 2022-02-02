/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:40:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 17:40:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_check_vars(char *tmp, t_var *vars)
{
	char	*str;
	t_var	*var;
	int		i;
	int		count;
	int		start;
	char	*variable;
	char	*carry;
	
	i = 0;
	start = 0;
	count = 0;
	var = vars;
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
			else
			{
				start = i;
				while (tmp[i] && tmp[i] != '\'' && tmp[i] != '\"')
					i++;
				variable = d_substr(tmp, start, i - start);
				while (var != NULL)
				{
					if (d_strncmp(variable, var->name, d_strlen(variable)) == 0)
						str = d_strjoin(str, var->value);
					var = var->next;
				}
				free(variable);
			}
		}
	}
	return (str);
}