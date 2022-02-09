/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:38:58 by dso               #+#    #+#             */
/*   Updated: 2022/02/09 17:52:16 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_create_heredoc(int i)
{
	char	*filename;
	char	*c;
	int		fd;

	c = d_itoa(i);
	filename = d_strdup(".heredoc");
	filename = d_strjoin(filename, c);
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		fd = 0;
		free(filename);
		filename = d_strdup("/private/tmp/.heredoc");
		filename = d_strjoin(filename, c);
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd == -1)
		{
			free(filename);
			free(c);
			d_putstr_fd("Failed to create heredoc\n", 2);
			return (NULL);
		}
	}
	free(c);
	close(fd);
	return (filename);
}

static int	d_check_hd_quotes(char *hd_stop, char c)
{
	int	i;
	int	sign;
	
	i = 0;
	sign = 0;
	while (hd_stop[i])
	{
		if (hd_stop[i] == c)
			sign++;
		i++;
	}
	if (sign % 2 != 0)
	{
		d_putstr_fd("Unclosed quotes\n", 2);
		return (1);
	}
	return (sign);
}

static void	d_loop_heredoc(int fd, char *hd_stop, int length, t_minishell *mshell)
{
	char	*input;
	int		quotes;
	// char	*str;

	input = NULL;
	quotes = 0;
	(void)mshell;
	if (d_check_hd_quotes(hd_stop, '\'') == 1 || d_check_hd_quotes(hd_stop, '\"') == 1)
		return ;
	else if (d_check_hd_quotes(hd_stop, '\'') != 0 || d_check_hd_quotes(hd_stop, '\"') != 0)
		quotes++;
	ft_signal(SIGINT, ft_handle_signal_spec);
	//rl_getc_function = getc;
	while (1)
	{
		input = readline("> ");
		if (d_strncmp(g_error[0], "1", 1) == 0)
		{
			close(fd);
			return ;
		}
		if (input == NULL)
		{
			close(fd);
			return ;
		}
		else if (d_strncmp(hd_stop, input, length) == 0)
			return ;
		// if (quotes != 0)
		// 	str = d_check_vars(input, mshell);
		write(fd, input, d_strlen(input));
		write(fd, "\n", 1);
	}
}

void	d_start_heredoc(char *hd_stop, char *heredoc, t_minishell *mshell)
{
	int		length;
	int		fd;

	fd = open(heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
	{
		d_putstr_fd("Failed to open heredoc\n", 2);
		return ;
	}
	length = d_strlen(hd_stop);
	d_loop_heredoc(fd, hd_stop, length, mshell);
	close(fd);
}
