/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:50:24 by dso               #+#    #+#             */
/*   Updated: 2021/12/10 13:18:49 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_loadimg(t_img *img, t_struct *game)
{
	img->wall = mlx_xpm_file_to_image(game->mlx, WALL, &img->width, &img->height);
	img->ground = mlx_xpm_file_to_image(game->mlx, GROUND, &img->width, &img->height);
	img->col = mlx_xpm_file_to_image(game->mlx, COL, &img->width, &img->height);
	img->exit = mlx_xpm_file_to_image(game->mlx, EXIT, &img->width, &img->height);
	img->player = mlx_xpm_file_to_image(game->mlx, PLAYER, &img->width, &img->height);
	if (img->wall == NULL || img->ground == NULL || img->col == NULL || img->exit == NULL)
		return (1);
	return (0);
}

int	ft_print_img(t_map *map, t_struct *game, t_img *img)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	while (map->map[x])
	{
		while (map->map[x][y])
		{
			if (map->map[x][y] == '0')
				mlx_put_image_to_window (game->mlx, game->win, img->ground, SPRITE_SIZE * y, SPRITE_SIZE * x);
			else if (map->map[x][y] == '1')
				mlx_put_image_to_window (game->mlx, game->win, img->wall, SPRITE_SIZE * y, SPRITE_SIZE * x);
			else if (map->map[x][y] == 'C')
			{
				mlx_put_image_to_window (game->mlx, game->win, img->ground, SPRITE_SIZE * y, SPRITE_SIZE * x);
				mlx_put_image_to_window (game->mlx, game->win, img->col, SPRITE_SIZE * y, SPRITE_SIZE * x);
			}
			else if (map->map[x][y] == 'E')
				mlx_put_image_to_window (game->mlx, game->win, img->exit, SPRITE_SIZE * y, SPRITE_SIZE * x);
			else if (map->map[x][y] == 'P')
			{
				mlx_put_image_to_window (game->mlx, game->win, img->ground, SPRITE_SIZE * y, SPRITE_SIZE * x);
				mlx_put_image_to_window (game->mlx, game->win, img->player, SPRITE_SIZE * y, SPRITE_SIZE * x - 64);
			}
			else
				return (1);
			y++;
		}
		x++;
		y = 0;
	}
	return (0);
}
