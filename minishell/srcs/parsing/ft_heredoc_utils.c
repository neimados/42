/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:41:19 by dso               #+#    #+#             */
/*   Updated: 2022/02/15 11:42:26 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*d_create_hd_error(char *c, char *filename)
{
	free(filename);
	free(c);
	d_putstr_fd("Failed to create heredoc\n", 2);
	return (NULL);
}

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
			return (d_create_hd_error(c, filename));
	}
	free(c);
	close(fd);
	return (filename);
}

int	d_check_hd_quotes(char *hd_stop, char c)
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

char	*d_trim_hdstop(char *hd_stop)
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

int	d_fork_error_heredoc(char *stop)
{
	free(stop);
	return (1);
}
