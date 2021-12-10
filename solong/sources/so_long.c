/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/10 15:43:32 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	key_hook(int keycode, t_struct *game)
{
	if (keycode == 53)
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}
	return (0);
}

int	ft_close()
{
	exit(0);
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
	game->win = mlx_new_window(game->mlx, map->width * SPRITE_SIZE, map->height * SPRITE_SIZE, "so_long");
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
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, 17, 1L<<17, ft_close, game);
	mlx_loop(game->mlx);
	// while (map->map[i]) // PRINT MAP
	// {
	// 	printf("%s\n", map->map[i]);
	// 	i++;
	// }
	return (0);
}