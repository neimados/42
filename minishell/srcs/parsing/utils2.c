/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:01:29 by dso               #+#    #+#             */
/*   Updated: 2022/02/08 13:01:54 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > d_strlen(s))
		len = d_strlen(s);
	str = d_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (d_strlen(s) < start)
	{
		*str = '\0';
		return (str);
	}
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	d_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	d_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		d_putchar_fd(*s, fd);
		s++;
	}
}

void	ft_set_terminal(struct termios *terminal)
{
	terminal->c_iflag &= ~terminal->c_iflag;
	terminal->c_iflag |= ( ICRNL | IXON | IXANY | IMAXBEL | IUTF8);
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
				terminal.c_lflag &= (ISIG | ICANON | IEXTEN | ECHO | FLUSHO);
				terminal.c_cc[VEOF] = ' ';
			}
			else
				terminal.c_cc[VEOF] = EOF;
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
