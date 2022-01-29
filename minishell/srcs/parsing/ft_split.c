/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:51:50 by dso               #+#    #+#             */
/*   Updated: 2022/01/29 16:48:54 by dso              ###   ########.fr       */
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
			while (str[i] != c && str[i])
			{
				if(str[i] == '\'')
				{
					i++;
					while (str[i] && str[i] != '\'')
						i++;
					i++;
				}
				else if(str[i] == '\"')
				{
					i++;
					while (str[i] && str[i] != '\"')
						i++;
					i++;
				}
				else
					i++;
			}
		}
	}
	return (count);
}

static void	ft_malloctab(char const *str, char c, char **strs)
{	
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
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
				if(str[i] == '\'')
				{
					i++;
					count++;
					while (str[i] && str[i] != '\'')
					{
						i++;
						count++;
					}
					i++;
					count++;
				}
				else if(str[i] == '\"')
				{
					i++;
					count++;
					while (str[i] && str[i] != '\"')
					{
						i++;
						count++;
					}
					i++;
					count++;
				}
				else
				{
					i++;
					count++;
				}
			}
			strs[j] = d_calloc((count + 1), sizeof(char));
			if (!strs[j])
				return (freemalloc(strs));
			j++;
			count = 0;
		}
	}
}

static void	ft_filltab(char const *str, char c, char **strs, int words)
{
	int	i;
	int	j;
	int	k;

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
			}
			k = 0;
			if (j < words)
				j++;
		}
	}
}


char	**d_split(char *s, char c)
{
	char	**strs;
	int		words;

	if (!s)
		return (NULL);
	words = ft_countwords(s, c);
	strs = malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	strs[words] = NULL;
	ft_malloctab(s, c, strs);
	ft_filltab(s, c, strs, words);
	return (strs);
}