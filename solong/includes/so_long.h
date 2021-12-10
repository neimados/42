/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:15:20 by dso               #+#    #+#             */
/*   Updated: 2021/12/10 13:14:00 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

# define BUFFER_SIZE 10
# define SPRITE_SIZE 64
# define GROUND "./sprites/ground.xpm"
# define WALL "./sprites/wall.xpm"
# define COL "./sprites/ball.xpm"
# define EXIT "./sprites/exit.xpm"
# define PLAYER "./sprites/player_S00.xpm"

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdio.h>

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

typedef struct s_player
{
	int	x;
	int	y;
	int	moves;
}			t_player;

typedef struct s_struct
{
	void	*mlx;
	void	*win;
	t_map		*map;
	t_img		*img;
	t_player	*player;
}			t_struct;

char	*get_next_line(int fd);
char	*ft_read(int fd, char *buffer);
char	*ft_strchr2(const char *str, int c);
char	*ft_findnl(char *buffer);
char	*ft_carry(char *buffer);
char	*ft_strjoin2(char *s1, char *s2);
t_map	*ft_initmap(void);
int		ft_check_map(char *filename, t_struct *game);
int		ft_parse_map(char *filename, t_struct *game);
int		ft_print_img(t_struct *game);
int		ft_loadimg(t_struct *game);
int		ft_freeall(t_struct *game);
void	ft_move(t_struct *game, int x, int y);

#endif