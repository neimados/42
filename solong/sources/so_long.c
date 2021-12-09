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

int	main(int argc, char **argv)
{
	t_struct	*game;
	t_map		*map;
	// int i;

	// i = 0;
	if (argc != 2)
	{
		write(2, "Error\nInvalid argument", 22);
		exit(0);
	}
	game = malloc(sizeof(t_struct));
	map = ft_initmap();
	if (!map || !game)
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
	// while (map->map[i])
	// {
	// 	printf("%s\n", map->map[i]);
	// 	i++;
	// }
	return (0);
}