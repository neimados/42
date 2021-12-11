/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/11 17:15:29 by dso              ###   ########.fr       */
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
	else if (keycode == 1 && game->gameover == 0)
	{
		game->player->direction = 0;
		ft_move(game, game->player->x + 1, game->player->y);
	}
	else if (keycode == 13 && game->gameover == 0)
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
	return (0);
}

int	ft_close()
{
	exit(0);
}

t_struct *ft_init_struct()
{
	t_struct *new;

	new = malloc(sizeof(t_struct));
	new->img = malloc(sizeof(t_img));
	new->map = malloc(sizeof(t_map));
	new->map = ft_initmap();
	new->player = malloc(sizeof(t_player));
	new->player->moves = 0;
	new->player->direction = 0;
	new->gameover = 0;
	return (new);
}

int	main(int argc, char **argv)
{
	t_struct	*game;
	// int i;

	// i = 0;
	if (argc != 2)
	{
		write(2, "Error\nInvalid argument", 22);
		exit(0);
	}
	game = ft_init_struct();
	if (!game)
		exit(0);
	if (ft_check_map(argv[1], game) == 1)
	{
		free(game->map);
		free(game);
		free(game);
		exit(0);
	}
	if (ft_parse_map(argv[1], game) == 1)
	{
		ft_freeall(game);
		exit(0);
	}
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		write (1, "Error\nInit failed", 17);
		exit(0);
	}
	game->win = mlx_new_window(game->mlx, game->map->width * SPRITE_SIZE, game->map->height * SPRITE_SIZE, "so_long");
	if (game->win == NULL)
	{
		write (1, "Error\nInit failed", 17);
		exit(0);
	}
	if (ft_loadimg(game) == 1)
	{
		write (1, "Error\nSprites loading failed", 28);
		exit(0);
	}
	if (ft_print_img(game) == 1)
	{
		write (1, "Error\nMap printing failed", 25);
		exit(0);
	}
	//printf("x : %d, y : %d", game->player->x, game->player->y);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, 17, 1L<<17, ft_close, game);
	mlx_loop(game->mlx);
	// while (game->map->map[i]) // PRINT MAP
	// {
	// 	printf("%s\n", game->map->map[i]);
	// 	i++;
	// }
	return (0);
}