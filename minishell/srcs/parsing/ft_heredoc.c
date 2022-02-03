/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:38:58 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 17:39:34 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*d_create_heredoc(int i)
{
	char	*filename;
	char	*c;
	int		fd;
	
	c = d_itoa(i);
	filename = d_strdup("./srcs/heredoc/.heredoc");
	filename = d_strjoin(filename, c);
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (NULL);
	free(c);
	close(fd);
	return (filename);
}

void	d_start_heredoc(char *hd_stop, char *heredoc)
{
	char	*input;
	int		length;
	int		fd;

	fd = open(heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return ;
	length = d_strlen(hd_stop);
	input = readline("> ");
	if (input == NULL)
	{
		close(fd);
		return ;
	}
	while (1)
	{
		if (input == NULL)
		{
			close(fd);
			return ;
		}
		else if (d_strncmp(hd_stop, input, length) == 0)
			return ;
		write(fd, input, d_strlen(input));
		write(fd, "\n", 1);
		input = readline("> ");
	}
	close(fd);
}