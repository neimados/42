/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/13 14:10:50 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	ft_check_letter(t_struct *game, unsigned long i, unsigned long j)
{
	if (game->map->map[i][j] == 'E')
		game->map->exit = game->map->exit + 1;
	else if (game->map->map[i][j] == 'C')
		game->map->col = game->map->col + 1;
	else if (game->map->map[i][j] == 'P')
	{
		game->map->player = game->map->player + 1;
		if (game->map->player == 1)
		{
			game->player->x = i;
			game->player->y = j;
		}
		else
			game->map->map[i][j] = '0';
	}
}

static int	ft_parse_check2(t_struct *game, unsigned long i)
{
	unsigned long	j;

	j = -1;
	while (game->map->map[i][++j])
	{
		if (i == 0 || i == game->map->height - 1)
		{
			if (game->map->map[i][j] != '1')
				return (1);
		}
		else
			ft_check_letter(game, i, j);
	}
	return (0);
}

int	ft_parse_check(t_struct *game)
{
	unsigned long	i;

	i = 0;
	while (game->map->map[i])
	{
		if (game->map->map[i][0] != '1'
			|| game->map->map[i][game->map->width -1] != '1')
			return (1);
		if (ft_parse_check2(game, i) == 1)
			return (1);
		i++;
	}
	if (ft_check_map_items(game) == 1)
		return (1);
	return (0);
}

static int	ft_gnl(int fd, t_struct *game)
{
	char	*str;
	int		i;
	int		j;

	str = get_next_line(fd);
	i = 0;
	j = -1;
	while (str != NULL)
	{
		game->map->map[i] = malloc(sizeof(char) * (game->map->width + 1));
		if (!game->map->map[i])
		{
			free(str);
			close(fd);
			return (1);
		}
		while (str[++j])
			game->map->map[i][j] = str[j];
		game->map->map[i][j] = '\0';
		i++;
		j = -1;
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}

int	ft_parse_map(char *filename, t_struct *game)
{
	int		fd;

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
	if (ft_gnl(fd, game) == 1)
		return (1);
	if (ft_parse_check(game) == 1)
		return (1);
	return (0);
}
