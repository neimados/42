/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:34:02 by dso               #+#    #+#             */
/*   Updated: 2022/02/15 11:14:28 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_set_terminal(struct termios *terminal)
{
	terminal->c_iflag &= ~terminal->c_iflag;
	terminal->c_iflag |= (ICRNL | IXON | IXANY | IMAXBEL | IUTF8);
	terminal->c_oflag &= ~terminal->c_oflag;
	terminal->c_oflag |= (OPOST | ONLCR);
	terminal->c_cflag &= ~terminal->c_cflag;
	terminal->c_cflag |= (CREAD | CS8);
	terminal->c_lflag &= ~terminal->c_lflag;
	terminal->c_lflag |= (ISIG | ICANON | IEXTEN | ECHO | NOFLSH);
	terminal->c_cc[VINTR] = 3;
	terminal->c_cc[VEOF] = 4;
}

static void	ft_set_terminal2(struct termios *terminal)
{
	terminal->c_iflag &= ~terminal->c_iflag;
	terminal->c_iflag |= (ICRNL | IXON | IXANY | IMAXBEL | IUTF8);
	terminal->c_oflag &= ~terminal->c_oflag;
	terminal->c_oflag |= (OPOST | ONLCR);
	terminal->c_cflag &= ~terminal->c_cflag;
	terminal->c_cflag |= (CREAD | CS8);
	terminal->c_lflag &= ~terminal->c_lflag;
	terminal->c_lflag |= (ISIG | ICANON | IEXTEN | ECHO);
	terminal->c_cc[VINTR] = 3;
	terminal->c_cc[VEOF] = 4;
}

static	void	d_terminal_error(void)
{
	d_putstr_fd("Terminal error\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_terminal(int echo)
{
	struct termios	terminal;

	if (isatty(STDIN_FILENO) == 1)
	{
		if (tcgetattr(STDIN_FILENO, &terminal) == 0)
		{
			if (echo == 1)
			{
				ft_set_terminal2(&terminal);
				terminal.c_cc[VEOF] = ' ';
				terminal.c_lflag |= (ECHOCTL);
			}
			else if (echo == 2)
			{
				ft_set_terminal(&terminal);
				terminal.c_lflag |= (ECHOCTL);
			}
			else
				ft_set_terminal(&terminal);
			if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal))
				d_terminal_error();
		}
		else
			d_terminal_error();
	}
}
