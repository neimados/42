/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:50:24 by dso               #+#    #+#             */
/*   Updated: 2021/12/11 17:16:55 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_loadimg(t_struct *game)
{
	game->img->wall = mlx_xpm_file_to_image(game->mlx, WALL, &game->img->width, &game->img->height);
	game->img->ground = mlx_xpm_file_to_image(game->mlx, GROUND, &game->img->width, &game->img->height);
	game->img->col = mlx_xpm_file_to_image(game->mlx, COL, &game->img->width, &game->img->height);
	game->img->exit = mlx_xpm_file_to_image(game->mlx, EXIT, &game->img->width, &game->img->height);
	game->img->player[0] = mlx_xpm_file_to_image(game->mlx, PLAYER0, &game->img->width, &game->img->height);
	game->img->player[1] = mlx_xpm_file_to_image(game->mlx, PLAYER1, &game->img->width, &game->img->height);
	game->img->player[2] = mlx_xpm_file_to_image(game->mlx, PLAYER2, &game->img->width, &game->img->height);
	game->img->player[3] = mlx_xpm_file_to_image(game->mlx, PLAYER3, &game->img->width, &game->img->height);
	if (game->img->wall == NULL || game->img->ground == NULL
	|| game->img->col == NULL || game->img->exit == NULL)
		return (1);
	return (0);
}

static int	ft_print_loop(t_struct *game, int x, int y)
{
	if (game->map->map[x][y] == '0')
		mlx_put_image_to_window (game->mlx, game->win, game->img->ground, SPRITE_SIZE * y, SPRITE_SIZE * x);
	else if (game->map->map[x][y] == '1')
		mlx_put_image_to_window (game->mlx, game->win, game->img->wall, SPRITE_SIZE * y, SPRITE_SIZE * x);
	else if (game->map->map[x][y] == 'C')
	{
		mlx_put_image_to_window (game->mlx, game->win, game->img->ground, SPRITE_SIZE * y, SPRITE_SIZE * x);
		mlx_put_image_to_window (game->mlx, game->win, game->img->col, SPRITE_SIZE * y, SPRITE_SIZE * x);
	}
	else if (game->map->map[x][y] == 'E')
		mlx_put_image_to_window (game->mlx, game->win, game->img->exit, SPRITE_SIZE * y, SPRITE_SIZE * x);
	else if (game->map->map[x][y] == 'P')
	{
		mlx_put_image_to_window (game->mlx, game->win, game->img->ground, SPRITE_SIZE * y, SPRITE_SIZE * x);
		mlx_put_image_to_window (game->mlx, game->win, game->img->player[game->player->direction], SPRITE_SIZE * y, SPRITE_SIZE * x - 64);
	}
	else
		return (1);
	return (0);
}

int	ft_print_img(t_struct *game)
{
	int	x;
	int y;
	char *move;

	x = 0;
	y = 0;
	while (game->map->map[x])
	{
		while (game->map->map[x][y])
		{
			if (ft_print_loop(game, x, y) == 1)
				return (1);
			y++;
		}
		x++;
		y = 0;
	}
	move = ft_itoa(game->player->moves);
	ft_putstr_fd("Move(s) : ", 1);
	ft_putstr_fd(move, 1);
	ft_putchar_fd('\n', 1);
	free(move);
	return (0);
}
