/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:23:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 18:15:06 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigint_handler(int keycode)
{
	if (keycode == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		if (!g_error)
			return ;
		g_error[0] = d_strdup("1");
	}
}

void	sigint_handler_child(int keycode)
{
	if (keycode == SIGINT)
		printf("\n");
	d_free_tab(g_error);
	g_error = d_calloc(3, sizeof(char *));
	if (!g_error)
		return ;
	g_error[0] = d_strdup("130");
}

void	sigint_handler_spec(int keycode)
{
	if (keycode == SIGINT)
	{
		printf("\n");
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		if (!g_error)
			return ;
		g_error[0] = d_strdup("1");
	}
}

void	sigint_handler_minishell(int keycode)
{
	if (keycode == SIGINT)
	{
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		if (!g_error)
			return ;
		g_error[0] = d_strdup("1");
	}
}

void	sigint_handler_hd(int keycode)
{
	if (keycode == SIGINT)
	{
		printf("\n");
	}
	exit(1);
}
