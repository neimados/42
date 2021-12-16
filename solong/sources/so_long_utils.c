/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:51:47 by dso               #+#    #+#             */
/*   Updated: 2021/12/13 11:52:44 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	key_hook2(int keycode, t_struct *game)
{
	if (keycode == 13 && game->gameover == 0)
	{
		game->player->direction = 1;
		ft_move(game, game->player->x - 1, game->player->y);
	}
	else if (keycode == 2 && game->gameover == 0)
	{
		game->player->direction = 2;
		ft_move(game, game->player->x, game->player->y + 1);
	}
	else if (keycode == 0 && game->gameover == 0)
	{
		game->player->direction = 3;
		ft_move(game, game->player->x, game->player->y - 1);
	}
}

int	key_hook(int keycode, t_struct *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->win);
		ft_free_end(game);
		exit(0);
	}
	else if (keycode == 1 && game->gameover == 0)
	{
		game->player->direction = 0;
		ft_move(game, game->player->x + 1, game->player->y);
	}
	else
		key_hook2(keycode, game);
	return (0);
}

int	ft_close(t_struct *game)
{
	mlx_destroy_window(game->mlx, game->win);
	ft_free_end(game);
	exit(0);
}
