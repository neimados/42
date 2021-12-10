/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/07 15:40:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int ft_check_map_items(t_struct *game)
{
	if (game->map->col < 1 || game->map->exit < 1 || game->map->player != 1)
		return (1);
	return (0);
}

int	ft_parse_check(t_struct *game)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (game->map->map[i])
	{
		if (game->map->map[i][0] != '1' || game->map->map[i][game->map->width -1] != '1')
				return (1);
		while (game->map->map[i][j])
		{
			if (i == 0 || i == game->map->height - 1)
			{
				if (game->map->map[i][j] != '1')
					return (1);
			}
			else
			{
				if (game->map->map[i][j] == 'E')
					game->map->exit = game->map->exit + 1;
				else if (game->map->map[i][j] == 'C')
					game->map->col = game->map->col + 1;
				else if (game->map->map[i][j] == 'P')
				{
					game->map->player = game->map->player + 1;
					game->player->x = j;
					game->player->y = i;
				}
			}
			j++;
		}
		i++;
		j = 0;
	}
	if (ft_check_map_items(game) == 1)
		return (1);
	return (0);
}

int	ft_parse_map(char *filename, t_struct *game)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	game->map->map = malloc(sizeof(char *) * (game->map->height + 1));
	if (!game->map->map)
		return (1);
	game->map->map[game->map->height] = 0;
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		write(2, "Error\nInvalid map", 17);
		return (1);
	}
	str = get_next_line(fd);
	while (str != NULL)
	{
		game->map->map[i] = malloc(sizeof(char) * (game->map->width + 1));
		if (!game->map->map[i])
		{
			free(str);
			close(fd);
			return (1);
		}
		game->map->map[i] = ft_strdup(str);
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	if (ft_parse_check(game) == 1)
		return (1);
	return (0);
}