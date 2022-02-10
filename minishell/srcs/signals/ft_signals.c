/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:23:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/09 18:04:29 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_block_signal(int keycode)
{
	struct sigaction	signals;

	signals.sa_handler = SIG_IGN;
	signals.sa_flags = 0;
	sigemptyset(&signals.sa_mask);
	sigaddset(&signals.sa_mask, keycode);
	if (sigaction(keycode, &signals, NULL))
	{
		d_putstr_fd("Signals Error\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_signal(int keycode
, void (*ft_handle_signal)(int, siginfo_t *, void *))
{
	struct sigaction	signals;

	signals.sa_sigaction = ft_handle_signal;
	signals.sa_flags = SA_SIGINFO;
	sigemptyset(&signals.sa_mask);
	sigaddset(&signals.sa_mask, keycode);
	if (sigaction(keycode, &signals, NULL))
	{
		d_putstr_fd("Signals Error\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_handle_signal_child(int keycode, siginfo_t *s, void *tmp)
{
	char	**pid;
	int		i;

	(void)tmp;
	(void)s;
	(void)keycode;
	pid = d_split(g_error[1], ' ');
	if (!pid)
		return ;
	i = 0;
	while (pid[i])
	{	
		kill(d_atoi(pid[i]), SIGINT);
		i++;
	}
	d_free_tab(g_error);
	g_error = d_calloc(3, sizeof(char *));
	g_error[0] = d_strdup("130");
	printf("^C\n");
}

void	ft_handle_signal_spec(int keycode, siginfo_t *s, void *tmp)
{
	(void)tmp;
	(void)s;
	(void)keycode;
	d_free_tab(g_error);
	g_error = d_calloc(3, sizeof(char *));
	g_error[0] = d_strdup("1");
}

void	ft_handle_signal(int keycode, siginfo_t *s, void *tmp)
{
	(void)tmp;
	(void)s;
	if (keycode == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
}
