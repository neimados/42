/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 13:55:38 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/02 18:34:23 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_countword(char const *str, char c)
{
	int	i;
	int	countword;

	i = 0;
	countword = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
		{
			i++;
		}
		while (str[i] != c && str[i])
		{
			i++;
		}
		if (str[i - 1] != c)
			countword++;
		while (str[i] == c && str[i])
		{
			i++;
		}
	}
	return (countword);
}

static int	ft_countchar(char const *str, char c, int startword)
{
	int	lenword;

	lenword = 0;
	while (str[startword + lenword] != c && str[startword + lenword])
		lenword++;
	return (lenword);
}

static int	ft_startword(char const *str, char c, int nbword)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		word++;
		if (word == nbword + 1)
			return (i);
		while (str[i] != c && str[i])
			i++;
		while (str[i] == c && str[i])
			i++;
	}
	return (0);
}

static void	ft_freeall(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**ft_split(char const *s, char c)
{
	char	**strsplit;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	strsplit = malloc(sizeof(char *) * (ft_countword(s, c) + 1));
	if (!strsplit)
		return (NULL);
	while (i < ft_countword(s, c))
	{
		strsplit[i] = ft_substr(s, ft_startword(s, c, i), \
		ft_countchar(s, c, ft_startword(s, c, i)));
		if (!strsplit[i])
			ft_freeall(strsplit);
		i++;
	}
	strsplit[i] = 0;
	return (strsplit);
}
