/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:51:50 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 18:32:14 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_countwords(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c && str[i])
			while (str[i] == c && str[i])
				i++;
		else
		{
			count++;
			i = d_loop_countwords(str, c, i);
		}
	}
	return (count);
}

static void	ft_malloctab(char const *str, char c, char **strs, int i)
{	
	int	j;
	int	count;

	j = -1;
	count = 0;
	while (str[i])
	{
		if (str[i] == c && str[i])
			while (str[i] == c && str[i])
				i++;
		else
		{
			while (str[i] != c && str[i])
			{
				if (str[i] == '\'' || str[i] == '\"')
					i = d_loop_malloctab(i, str);
				else
					i++;
			}
			count = i - count;
			strs[++j] = d_calloc((count + 1), sizeof(char));
			if (!strs[j])
				return (freemalloc(strs));
		}
	}
}

static void	d_fill_filltab(t_parsing *p, int i, int j, int k)
{
	p->i = i;
	p->j = j;
	p->k = k;
}

static void	ft_filltab(char const *str, char c, char **strs)
{
	int			i;
	int			j;
	int			k;
	t_parsing	p;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c && str[i])
			while (str[i] == c && str[i])
				i++;
		else
		{
			while (str[i] != c && str[i])
			{
				d_fill_filltab(&p, i, j, k);
				k = d_loop_filltab(&p, str, strs);
				i = d_skip_filltab(&p, str);
			}
			k = 0;
			j++;
		}
	}
}

char	**d_split(char *s, char c)
{
	char	**strs;
	int		words;
	int		i;

	i = 0;
	if (!s)
	{
		d_putstr_fd("Split error 1\n", 2);
		return (NULL);
	}
	words = ft_countwords(s, c);
	strs = malloc(sizeof(char *) * (words + 1));
	if (!strs)
	{
		d_putstr_fd("Split error 2\n", 2);
		return (NULL);
	}
	strs[words] = NULL;
	ft_malloctab(s, c, strs, i);
	ft_filltab(s, c, strs);
	return (strs);
}
