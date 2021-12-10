/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/07 15:40:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_move(t_struct *game, int x, int y)
{
	game->player->moves = game->player->moves + 1;
	game->map->map[x][y] = 'P';
	game->map->map[game->player->x][game->player->y] = '0';
	if (ft_print_img(game) == 1)
	{
		write (1, "Error\nMap printing failed", 25);
		exit(0);
	}
	game->player->x = x;
	game->player->y = y;
}