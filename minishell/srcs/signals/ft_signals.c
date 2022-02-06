/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:42:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 18:42:19 by dso              ###   ########.fr       */
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
		printf("Signals Error\n");
		exit(EXIT_FAILURE);
	}
}
void	ft_signal(int keycode, void (*ft_handle_signal)(int, siginfo_t *, void *))
{
	struct sigaction	signals;

	signals.sa_sigaction = ft_handle_signal;
	signals.sa_flags = SA_SIGINFO;
	sigemptyset(&signals.sa_mask);
	sigaddset(&signals.sa_mask, keycode);
	if (sigaction(keycode, &signals, NULL))
	{
		printf("Signals Error\n");
		exit(EXIT_FAILURE);
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
	}
}

void	ft_set_terminal(struct termios *terminal)
{
	terminal->c_lflag &= ~terminal->c_lflag;
	terminal->c_lflag |= (ISIG | ICANON | IEXTEN | ECHO | NOFLSH);
	terminal->c_iflag &= ~terminal->c_iflag;
	terminal->c_iflag |= (ICRNL | IXON | IXANY | IMAXBEL | IUTF8);
	terminal->c_oflag &= ~terminal->c_oflag;
	terminal->c_oflag |= (OPOST | ONLCR);
	terminal->c_cflag &= ~terminal->c_cflag;
	terminal->c_cflag |= (CREAD | CS8);
}

int	ft_terminal(void)
{
	struct termios	terminal;

	if (isatty(STDIN_FILENO) == 1)
	{
		if (tcgetattr(STDIN_FILENO, &terminal) == 0)
		{
			ft_set_terminal(&terminal);
			if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal))
				return (1);
		}
		else
			return (1);
	}
	return (0);
}