/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/07 15:40:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_check_map_ext(char *filename)
{
	int	i;
	
	i = ft_strlen(filename);
	if (i < 5)
		return (1);
	if (filename[i - 1] != 'r' || filename[i - 2] != 'e'
	|| filename[i - 3] != 'b' || filename[i - 4] != '.')
	{
		write(2, "Error\nExtension not .ber", 24);
		return (1);
	}
	return (0);
}
// int ft_check_map_items(char **map)
// {
	
// }

// int	ft_check_map_wall(char *str, int line)
// {
// 	int	i;

// 	i = 0;
// 	if (line == 1)
// 	{
// 		while (str[i])
// 		{
// 			if (str[i] != '1')
// 				return (1);
// 		}
// 	}
// 	else
// 	{
// 		if (str[0] != '1' || str[ft_strlen(line) - 1] != '1')
// 			return (1);
// 	}
// 	return (0);
// }

int	ft_check_map_size(int fd, t_map *map)
{
	char *str;

	str = get_next_line(fd);
	map->width = ft_strlen(str);
	while (str)
	{
		map->height = map->height + 1;
		if (ft_strlen(str) != map->width)
			return (1);
		free(str);
		str = get_next_line(fd);
	}
	if (map->height == map->width)
		return (1);
	return (0);
}

int	ft_check_map(char *filename, t_map *map)
{
	int	fd;
	
	if (ft_check_map_ext(filename) == 1)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
	{
		write(2, "Error\nInvalid map file", 22);
		return (1);
	}
	if (ft_check_map_size(fd, map) == 1)
	{
		write(2, "Error\nInvalid map", 17);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}