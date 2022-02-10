/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:38:58 by dso               #+#    #+#             */
/*   Updated: 2022/02/09 18:50:38 by dso              ###   ########.fr       */
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

static char	*d_trim_hdstop(char *hd_stop)
{
	int		i;
	int		j;
	int		count;
	char	*str;

	i = -1;
	j = -1;
	count = 0;
	while (hd_stop[++i])
		if (hd_stop[i] != '\'' && hd_stop[i] != '\"')
			count++;
	str = d_calloc((count + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (hd_stop[++i])
		if (hd_stop[i] != '\'' && hd_stop[i] != '\"')
			str[++j] = hd_stop[i];
	return (str);
}

static int	d_loop_heredoc(int fd, char *hd_stop, t_minishell *mshell)
{
	char	*input;
	int		quotes;
	char	*str;
	char 	*stop;

	quotes = 0;
	(void)mshell;
	stop = d_trim_hdstop(hd_stop);
	if (!stop)
		return (1);
	if (d_check_hd_quotes(hd_stop, '\'') == 1 || d_check_hd_quotes(hd_stop, '\"') == 1)
		return (1);
	else if (d_check_hd_quotes(hd_stop, '\'') != 0 || d_check_hd_quotes(hd_stop, '\"') != 0)
		quotes++;
	//rl_getc_function = getc;
	// ft_signal2(SIGINT);
	while (1)
	{
		input = readline("> ");
		// if (d_strncmp(g_error[0], "1", 1) == 0)
		// {
		// 	close(fd);
		// 	ft_signal(SIGINT, ft_handle_signal);
		// 	return (0);
		// }
		if (input == NULL)
		{
			free(stop);
			return (0);
		}
		else if (d_strncmp(stop, input, d_strlen(stop)) == 0)
		{
			free(stop);
			return (0);
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
	}
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
		d_putstr_fd("heredoc parsing failed\n", 2);
		return (1);
	}
	ft_signal(SIGINT, ft_handle_signal);
	close(fd);
	return (0);
}
