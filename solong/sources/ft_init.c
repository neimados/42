/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 12:06:03 by dso               #+#    #+#             */
/*   Updated: 2021/12/11 17:18:01 by dso              ###   ########.fr       */
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

t_struct *ft_init_struct()
{
	t_struct *new;

	new = malloc(sizeof(t_struct));
	new->img = malloc(sizeof(t_img));
	new->map = ft_initmap();
	new->player = malloc(sizeof(t_player));
	new->player->moves = 0;
	new->player->direction = 0;
	new->gameover = 0;
	return (new);
}
