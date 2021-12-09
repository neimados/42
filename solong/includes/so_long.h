/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:15:20 by dso               #+#    #+#             */
/*   Updated: 2021/12/06 18:16:04 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# define BUFFER_SIZE 10
# define GROUND "./sprites/ground.xpm"
# define WALL "./sprites/wall.xpm"
# define COL "./sprites/ball.xpm"
# define EXIT "./sprites/exit.xpm"
# define PLAYER "./sprites/pikachu.xpm"

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdio.h>

typedef struct s_struct
{
	void	*mlx;
	void	*win;
}			t_struct;

typedef struct s_map
{
	char	**map;
	size_t	width;
	size_t	height;
	int		col;
	int		exit;
	int		player;
}			t_map;

typedef struct s_img
{
	void	*wall;
	void	*ground;
	void	*col;
	void	*exit;
	void	*player;
	int		width;
	int		height;
}			t_img;

char	*get_next_line(int fd);
char	*ft_read(int fd, char *buffer);
char	*ft_strchr2(const char *str, int c);
char	*ft_findnl(char *buffer);
char	*ft_carry(char *buffer);
char	*ft_strjoin2(char *s1, char *s2);
t_map	*ft_initmap(void);
int		ft_check_map(char *filename, t_map *map);
int		ft_parse_map(char *filename, t_map *map);

#endif