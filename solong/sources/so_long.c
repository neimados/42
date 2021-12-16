/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/13 11:42:49 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	ft_check_first(t_struct *game, char **argv)
{
	if (ft_check_map(argv[1], game) == 1)
		ft_free_all(game);
	if (ft_parse_map(argv[1], game) == 1)
	{
		ft_free_map(game);
		ft_free_all(game);
	}
}

void	ft_init_game(t_struct *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		ft_free_init(game);
	game->win = mlx_new_window(game->mlx, game->map->width * SPRITE_SIZE,
			game->map->height * SPRITE_SIZE, "so_long");
	if (game->win == NULL)
		ft_free_init(game);
	if (ft_loadimg(game) == 1)
		ft_free_init(game);
	if (ft_print_img(game) == 1)
		ft_free_init(game);
}

int	main(int argc, char **argv)
{
	t_struct	*game;

	if (argc != 2)
	{
		write(2, "Error\nInvalid argument\n", 23);
		exit(0);
	}
	game = ft_init_struct();
	if (!game)
		exit(0);
	ft_check_first(game, argv);
	ft_init_game(game);
	mlx_key_hook(game->win, key_hook, game);
	mlx_hook(game->win, 17, 1L << 17, ft_close, game);
	mlx_loop(game->mlx);
	return (0);
}
