/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:51:47 by dso               #+#    #+#             */
/*   Updated: 2021/12/10 10:51:57 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_freeall(t_struct *game)
{
	int	i;

	i = 0;
	if (game->map->map[0])
	{
		while (game->map->map[i])
		{
			free(game->map->map[i]);
			i++;
		}
		free(game->map->map);
	}
	free(game->map);
	free(game);
	free(game);
	write(2, "Error\nInvalid map", 17);
	return (1);
}

t_map	*ft_initmap(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->width = 0;
	new->height = 0;
	new->col = 0;
	new->exit = 0;
	new->player = 0;
	return (new);
}