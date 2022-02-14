/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:35:26 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 18:31:46 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	freemalloc(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
	return ;
}

int	d_loop_countwords(char const *str, char c, int i)
{
	while (str[i] != c && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			i++;
		}
		else
			i++;
	}
	return (i);
}

int	d_loop_malloctab(int i, char const *str)
{
	int	j;

	j = i;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	return (i);
}

int	d_loop_filltab(t_parsing *p, char const *str, char **strs)
{
	int	i;
	int	j;
	int	k;

	i = p->i;
	j = p->j;
	k = p->k;
	if (str[i] == '\'')
	{
		strs[j][k++] = str[i++];
		while (str[i] && str[i] != '\'')
			strs[j][k++] = str[i++];
		strs[j][k++] = str[i++];
	}
	else if (str[i] == '\"')
	{
		strs[j][k++] = str[i++];
		while (str[i] && str[i] != '\"')
			strs[j][k++] = str[i++];
		strs[j][k++] = str[i++];
	}
	else
		strs[j][k++] = str[i++];
	return (k);
}

int	d_skip_filltab(t_parsing *p, char const *str)
{
	int	i;

	i = p->i;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	else
		i++;
	return (i);
}
