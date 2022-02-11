/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:23:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/11 18:22:55 by dso              ###   ########.fr       */
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
	// char	**pid;
	// int		i;

	(void)tmp;
	(void)s;
	(void)keycode;
	d_putstr_fd("TEST", 2);
	// pid = d_split(g_error[1], ' ');
	// if (!pid)
	// 	return ;
	// i = 0;
	// while (pid[i])
	// {	
	// 	if (pid[i] > 0)
	// 		kill(d_atoi(pid[i]), SIGKILL);
	// 	i++;
	// }
}

// void	ft_handle_signal_child(int keycode, siginfo_t *s, void *tmp)
// {
// 	char	**pid;
// 	char	*tmp1;
// 	pid_t	fork_c;

// 	(void)tmp;
// 	(void)s;
// 	(void)keycode;
// 	tmp1 = ft_strjoin("kill ", g_error[1]);
// 	pid = d_split(tmp1, ' ');
// 	free(tmp1);
// 	if (!pid)
// 		return ;
// 	fork_c = fork();
// 	if (fork_c == 0)
// 		execve("/bin/kill", pid, NULL);
// 	waitpid(fork_c, NULL, 0);
// 	printf("\n");
// 	d_free_tab(g_error);
// 	g_error = d_calloc(3, sizeof(char *));
// 	g_error[0] = d_strdup("130");
// }

void	ft_handle_signal_spec(int keycode, siginfo_t *s, void *tmp)
{
	(void)tmp;
	(void)s;
	(void)keycode;
	d_free_tab(g_error);
	g_error = d_calloc(3, sizeof(char *));
	g_error[0] = d_strdup("1");
	exit(0);
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


void sigint_handler(int keycode)
{
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

void	sigint_handler_child(int keycode)
{
	if (keycode == SIGINT)
	{
		printf("");
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
	exit(SIGINT);
}