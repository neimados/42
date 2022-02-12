/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:23:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/12 15:24:51 by dso              ###   ########.fr       */
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
	if (keycode == SIGINT)
	{
		printf("^C\n");
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
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
	if (keycode == SIGINT)
	{
		printf("\n");
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
}

void	ft_handle_signal_minishell(int keycode, siginfo_t *s, void *tmp)
{
	(void)tmp;
	(void)s;
	if (keycode == SIGINT)
	{
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
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
		if (!g_error)
			return ;
		g_error[0] = d_strdup("1");
	}
}

void	sigint_handler_child(int keycode)
{
	if (keycode == SIGINT)
		printf("^C\n");
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
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
	exit(1);
}

void	ft_set_terminal(struct termios *terminal)
{
	terminal->c_iflag &= ~terminal->c_iflag;
	terminal->c_iflag |= (ICRNL | IXON | IXANY | IMAXBEL | IUTF8);
	terminal->c_oflag &= ~terminal->c_oflag;
	terminal->c_oflag |= (OPOST | ONLCR);
	terminal->c_cflag &= ~terminal->c_cflag;
	terminal->c_cflag |= (CREAD | CS8);
	terminal->c_lflag &= ~terminal->c_lflag;
	terminal->c_lflag |= (ISIG | ICANON | IEXTEN | ECHO | NOFLSH);
}

void	ft_terminal(int echo)
{
	struct termios	terminal;

	if (isatty(STDIN_FILENO) == 1)
	{
		if (tcgetattr(STDIN_FILENO, &terminal) == 0)
		{
			ft_set_terminal(&terminal);
			if (echo == 1)
			{
				terminal.c_lflag &= (ISIG | ICANON | IEXTEN | ECHO | ECHOCTL | FLUSHO);
				//terminal.c_lflag |= (ECHOCTL);
				terminal.c_cc[VEOF] = ' ';
			}
			else if (echo == 2)
				terminal.c_lflag |= (ECHOCTL);
			else
			{
				terminal.c_cc[VINTR] = 3;
				terminal.c_cc[VEOF] = 4;
			}
			if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal))
			{
				d_putstr_fd("Terminal error\n", 2);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			d_putstr_fd("Terminal error\n", 2);
			exit(EXIT_FAILURE);
		}
	}
}