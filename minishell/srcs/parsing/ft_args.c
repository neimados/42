/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:42:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 18:14:19 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	d_put_args(char **args, t_cmds *cmd, t_var *vars, char *heredoc)
{
	int		i;
	int		j;
	int		in;
	int		out;
	int		start;
	int		fd;
	char	*hd_stop;
	int		end;
	char	*tmp;

	i = 0;
	j = 0;
	in = 0;
	out = 0;
	start = 0;
	fd = 0;
	end = 0;
	cmd->cmd = d_calloc((d_count_cmds(args) + 1), sizeof(char *));
	if (!cmd->cmd)
		return (1);
	d_put_cmds(args, cmd, vars);
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '<' || args[i][j] == '>')
			{
				if (args[i][j] == '<')
					in++;
				else if (args[i][j] == '>')
					out++;
				j++;
			}
			else
			{
				start = j;
				while (args[i][j] && args[i][j] != '>' && args[i][j] != '<')
					j++;
				if (in != 0)
				{
					if (in == 1 && end == 0)
					{
						tmp = d_substr(args[i], start, j - start);
						cmd->infile= d_check_vars(tmp, vars);
						free(tmp);
						fd = open(cmd->infile, O_RDONLY);
						if (fd == -1)
							end = 1;
						close(fd);
					}
					else if (in == 2)
					{
						hd_stop = d_substr(args[i], start, j - start);
						d_start_heredoc(hd_stop, heredoc);
						if (end == 0)
						cmd->infile = heredoc;
					}
					in = 0;
				}
				else if (out != 0)
				{
					if (end == 0)
					{
						if (out == 1)
						{
							cmd->type = 1;
							fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
							if (fd == -1)
								end = 1;
						}
						else if (out == 2)
						{
							cmd->type = 2;
							fd = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0777);
							if (fd == -1)
								end = 1;
						}
						tmp = d_substr(args[i], start, j - start);
						cmd->outfile= d_check_vars(tmp, vars);
						free(tmp);
						close(fd);
					}
					out = 0;
				}
			}
		}
		i++;
		j = 0;
	}
	if (end == 1)
		printf("%s\n", strerror(errno));
	return (0);
}
