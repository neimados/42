/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/13 10:29:04 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_move(t_struct *game, int x, int y)
{
	if (game->map->map[x][y] != '1')
	{
		if (game->map->map[x][y] == 'C')
			game->map->col = game->map->col - 1;
		else if (game->map->map[x][y] == 'E' && game->map->col != 0)
			return ;
		if (game->map->map[x][y] == 'E' && game->map->col == 0)
		{
			game->gameover = 1;
			game->map->map[game->player->x][game->player->y] = '0';
		}
		else
			game->map->map[x][y] = 'P';
		game->player->moves = game->player->moves + 1;
		game->map->map[game->player->x][game->player->y] = '0';
		if (ft_print_img(game) == 1)
			ft_free_init(game);
		game->player->x = x;
		game->player->y = y;
	}
}
