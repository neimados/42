/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/07 15:40:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_freeall(t_map *map, t_struct *game)
{
	int	i;

	i = 0;
	if (map->map[0])
	{
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	free(map);
	free(game);
	write(2, "Error\nInvalid map", 17);
	return (1);
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
				mlx_put_image_to_window (game->mlx, game->win, img->ground, 64 * y, 64 * x);
			else if (map->map[x][y] == '1')
				mlx_put_image_to_window (game->mlx, game->win, img->wall, 64 * y, 64 * x);
			else if (map->map[x][y] == 'C')
				mlx_put_image_to_window (game->mlx, game->win, img->col, 64 * y, 64 * x);
			else if (map->map[x][y] == 'E')
				mlx_put_image_to_window (game->mlx, game->win, img->exit, 64 * y, 64 * x);
			else if (map->map[x][y] == 'P')
				mlx_put_image_to_window (game->mlx, game->win, img->player, 64 * y, 64 * x);
			else
				return (1);
			y++;
		}
		x++;
		y = 0;
	}
	return (0);
}

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

int	main(int argc, char **argv)
{
	t_struct	*game;
	t_map		*map;
	t_img		*img;
	// int i;

	// i = 0;
	if (argc != 2)
	{
		write(2, "Error\nInvalid argument", 22);
		exit(0);
	}
	game = malloc(sizeof(t_struct));
	map = ft_initmap();
	img = malloc(sizeof(t_img));
	if (!map || !game || !img)
		exit(0);
	if (ft_check_map(argv[1], map) == 1)
	{
		free(map);
		free(game);
		exit(0);
	}
	if (ft_parse_map(argv[1], map) == 1)
	{
		ft_freeall(map, game);
		exit(0);
	}
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		write (1, "Error\nInit failed", 17);
		exit(0);
	}
	game->win = mlx_new_window(game->mlx, map->width * 64, map->height * 64, "so_long");
	if (game->win == NULL)
	{
		write (1, "Error\nInit failed", 17);
		exit(0);
	}
	if (ft_loadimg(img, game) == 1)
	{
		write (1, "Error\nSprites loading failed", 28);
		exit(0);
	}
	if (ft_print_img(map, game, img) == 1)
	{
		write (1, "Error\nMap printing failed", 25);
		exit(0);
	}
	//mlx_put_image_to_window (game->mlx, game->win, img->ground, 0, 0);
	mlx_loop(game->mlx);
	// while (map->map[i]) // PRINT MAP
	// {
	// 	printf("%s\n", map->map[i]);
	// 	i++;
	// }
	return (0);
}