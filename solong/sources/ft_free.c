/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:51:47 by dso               #+#    #+#             */
/*   Updated: 2021/12/13 12:04:31 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	ft_free_map(t_struct *game)
{
	int	i;

	i = 0;
	while (game->map->map[i])
	{
		free(game->map->map[i]);
		i++;
	}
	free(game->map->map);
}

void	ft_free_all(t_struct *game)
{
	free(game->map);
	free(game->img);
	free(game->player);
	free(game);
	write(2, "Error\nInvalid map\n", 18);
	exit(0);
}

void	ft_free_init(t_struct *game)
{
	ft_free_map(game);
	free(game->map);
	free(game->img);
	free(game->player);
	free(game);
	write (1, "Error\nInit failed\n", 18);
	exit(0);
}

void	ft_free_end(t_struct *game)
{
	int	i;

	i = -1;
	ft_free_map(game);
	free(game->map);
	mlx_destroy_image(game->mlx, game->img->ground);
	mlx_destroy_image(game->mlx, game->img->wall);
	mlx_destroy_image(game->mlx, game->img->col);
	mlx_destroy_image(game->mlx, game->img->exit);
	while (++i < 4)
		mlx_destroy_image(game->mlx, game->img->player[i]);
	free(game->img);
	free(game->player);
	free(game);
}
