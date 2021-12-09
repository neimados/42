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
	return (0);
}