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
		return (1);
	return (0);
}

int	ft_check_map_size(int fd, t_struct *game)
{
	char *str;

	str = get_next_line(fd);
	game->map->width = ft_strlen(str);
	while (str)
	{
		game->map->height = game->map->height + 1;
		if (ft_strlen(str) != game->map->width)
		{
			free(str);
			return (1);
		}
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	if (game->map->height == game->map->width)
		return (1);
	return (0);
}

int	ft_check_map(char *filename, t_struct *game)
{
	int	fd;
	
	if (ft_check_map_ext(filename) == 1)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		return (1);
	if (ft_check_map_size(fd, game) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int ft_check_map_items(t_struct *game)
{
	if (game->map->col < 1 || game->map->exit < 1 || game->map->player != 1)
		return (1);
	return (0);
}
