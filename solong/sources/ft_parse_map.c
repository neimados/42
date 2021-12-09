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

t_map	*ft_initmap(void)
{
	t_map	*new;

	new = malloc(sizeof(t_map));
	if (!new)
		return (NULL);
	new->width = 0;
	new->height = 0;
	new->col = 0;
	new->exit = 0;
	new->player = 0;
	return (new);
}

int ft_check_map_items(t_map *map)
{
	if (map->col < 1 || map->exit < 1 || map->player != 1)
		return (1);
	return (0);
}

int	ft_parse_check(t_map *map)
{
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		if (map->map[i][0] != '1' || map->map[i][map->width -1] != '1')
				return (1);
		while (map->map[i][j])
		{
			if (i == 0 || i == map->height - 1)
			{
				if (map->map[i][j] != '1')
					return (1);
			}
			else
			{
				if (map->map[i][j] == 'E')
					map->exit = map->exit + 1;
				else if (map->map[i][j] == 'C')
					map->col = map->col + 1;
				else if (map->map[i][j] == 'P')
					map->player = map->player + 1;
			}
			j++;
		}
		i++;
		j = 0;
	}
	if (ft_check_map_items(map) == 1)
		return (1);
	return (0);
}

int	ft_parse_map(char *filename, t_map *map)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		return (1);
	map->map[map->height] = 0;
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		write(2, "Error\nInvalid map", 17);
		return (1);
	}
	str = get_next_line(fd);
	while (str != NULL)
	{
		map->map[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map->map[i])
		{
			free(str);
			close(fd);
			return (1);
		}
		map->map[i] = ft_strdup(str);
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	if (ft_parse_check(map) == 1)
		return (1);
	return (0);
}