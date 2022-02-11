/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 20:45:40 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/02 18:34:10 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *str, int chr)
{
	int		i;

	i = ft_strlen((char *)str);
	while (i >= 0)
	{
		if (str[i] == (char)chr)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}
