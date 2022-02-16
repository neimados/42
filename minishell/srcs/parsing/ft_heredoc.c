/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:38:58 by dso               #+#    #+#             */
/*   Updated: 2022/02/15 11:40:41 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_heredoc_child(char *stop, int quotes, int fd, t_minishell *mshell)
{
	char	*input;
	char	*str;

	while (1)
	{
		input = readline("> ");
		if (input == NULL)
			exit(1);
		else if (d_strncmp(stop, input, d_strlen(stop)) == 0)
		{
			free(input);
			exit(0);
		}
		if (quotes == 0)
		{
			str = d_check_vars(input, mshell);
			d_putstr_fd(str, fd);
			free(str);
		}
		else
			write(fd, input, d_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
}

static int	d_checks_heredoc(char *hd_stop)
{
	if (d_check_hd_quotes(hd_stop, '\'') == 1
		|| d_check_hd_quotes(hd_stop, '\"') == 1)
		return (-1);
	else if (d_check_hd_quotes(hd_stop, '\'') != 0
		|| d_check_hd_quotes(hd_stop, '\"') != 0)
		return (1);
	return (0);
}

static int	d_return_heredoc(char *stop, int *status)
{
	free(stop);
	if (WEXITSTATUS(status[0]) != 0)
		return (1);
	return (0);
}

static int	d_loop_heredoc(int fd, char *hd_stop, t_minishell *mshell)
{
	int		quotes;
	char	*stop;
	pid_t	fork_hd;
	int		status[1];

	quotes = d_checks_heredoc(hd_stop);
	if (quotes == -1)
		return (1);
	stop = d_trim_hdstop(hd_stop);
	free(hd_stop);
	if (!stop)
		return (1);
	fork_hd = fork();
	if (fork_hd == -1)
		return (d_fork_error_heredoc(stop));
	signal(SIGINT, sigint_handler_minishell);
	if (fork_hd == 0)
	{
		signal(SIGINT, sigint_handler_hd);
		d_heredoc_child(stop, quotes, fd, mshell);
	}
	waitpid(fork_hd, status, 0);
	return (d_return_heredoc(stop, status));
}

int	d_start_heredoc(char *hd_stop, char *heredoc, t_minishell *mshell)
{
	int		fd;

	fd = open(heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		d_putstr_fd("Failed to open heredoc\n", 2);
		return (1);
	}
	if (d_loop_heredoc(fd, hd_stop, mshell) == 1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	signal(SIGINT, sigint_handler);
	ft_terminal(0);
	return (0);
}
