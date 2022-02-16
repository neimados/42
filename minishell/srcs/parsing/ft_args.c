/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:42:37 by dso               #+#    #+#             */
/*   Updated: 2022/02/16 18:00:13 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	d_fd_args(int out, t_cmds *cmd)
// {
// 	int	fd;

// 	fd = 0;
// 	if (out == 1)
// 	{
// 		cmd->type = 1;
// 		fd = open(cmd->outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
// 	}
// 	else if (out == 2)
// 	{
// 		cmd->type = 2;
// 		fd = open(cmd->outfile, O_RDWR | O_APPEND | O_CREAT, 0777);
// 	}
// 	return (fd);
// }

// int	d_args_out(t_minishell *mshell, t_cmds *cmd, t_parsing *p, char *arg)
// {
// 	int		end;
// 	int		fd;
// 	char	*tmp;

// 	end = 0;
// 	fd = 0;
// 	tmp = d_substr(arg, p->start, p->j - p->start);
// 	if (!tmp)
// 		return (-1);
// 	if (cmd->outfile)
// 		free(cmd->outfile);
// 	cmd->outfile = d_check_vars(tmp, mshell);
// 	free(tmp);
// 	if (!cmd->outfile)
// 		return (-1);
// 	fd = d_fd_args(p->out, cmd);
// 	if (fd == -1)
// 		end = 1;
// 	close(fd);
// 	return (end);
// }

// int	d_args_in1(t_minishell *mshell, t_cmds *cmd, t_parsing *p, char *arg)
// {
// 	int		end;
// 	int		fd;
// 	char	*tmp;

// 	end = 0;
// 	fd = 0;
// 	tmp = d_substr(arg, p->start, p->j - p->start);
// 	if (!tmp)
// 		return (-1);
// 	if (cmd->infile)
// 		free(cmd->infile);
// 	cmd->infile = d_check_vars(tmp, mshell);
// 	free(tmp);
// 	if (!cmd->infile)
// 		return (-1);
// 	fd = open(cmd->infile, O_RDONLY);
// 	if (fd == -1)
// 		end = 1;
// 	close(fd);
// 	return (end);
// }

// int	d_args_in2(t_minishell *mshell, t_cmds *cmd, char *heredoc, char *hd_stop)
// {
// 	int		end;
// 	int		fd;

// 	end = 0;
// 	fd = 0;
// 	if (d_start_heredoc(hd_stop, heredoc, mshell) == 1)
// 		return (-1);
// 	if (end == 0)
// 	{
// 		cmd->heredoc = 1;
// 		cmd->infile = heredoc;
// 	}
// 	return (end);
// }

// void	d_args_struct(t_parsing *p)
// {
// 	p->i = 0;
// 	p->j = 0;
// 	p->in = 0;
// 	p->out = 0;
// 	p->start = 0;
// 	p->end = 0;
// }

// int	d_count_sign_args(char c, t_parsing *p)
// {
// 	int	i;

// 	i = p->j;
// 	if (c == '<')
// 		p->in += 1;
// 	else if (c == '>')
// 		p->out += 1;
// 	i++;
// 	return (i);
// }

// int	d_put_args(char **args, t_cmds *cmd, char *heredoc, t_minishell *mshell)
// {
// 	t_parsing	p;
// 	char		*hd_stop;

// 	d_args_struct(&p);
// 	cmd->cmd = d_calloc((d_count_cmds(args) + 1), sizeof(char *));
// 	if (!cmd->cmd)
// 		return (1);
// 	while (args[p.i])
// 	{
// 		while (args[p.i][p.j])
// 		{
// 			if (args[p.i][p.j] == '<' || args[p.i][p.j] == '>')
// 				p.j = d_count_sign_args(args[p.i][p.j], &p);
// 			else
// 			{
// 				p.start = p.j;
// 				while (args[p.i][p.j] && args[p.i][p.j] != '>' && args[p.i][p.j] != '<')
// 					p.j += 1;
// 				if (p.in != 0)
// 				{
// 					if (p.in == 1 && p.end == 0)
// 						p.end = d_args_in1(mshell, cmd, &p, args[p.i]);
// 					else if (p.in == 2)
// 					{
// 						hd_stop = d_substr(args[p.i], p.start, p.j - p.start);
// 						if (!hd_stop)
// 							return (1);
// 						p.end = d_args_in2(mshell, cmd, heredoc, hd_stop);
// 					}
// 					p.in = 0;
// 				}
// 				else if (p.out != 0)
// 				{
// 					if (p.end == 0)
// 						p.end = d_args_out(mshell, cmd, &p, args[p.i]);
// 					p.out = 0;
// 				}
// 				if (p.end == -1)
// 					return (1);
// 			}
// 		}
// 		p.i += 1;
// 		p.j = 0;
// 	}
// 	if (d_put_cmds(args, cmd, mshell) == 1)
// 		return (1);
// 	if (p.end == 1)
// 	{
// 		d_free_tab(g_error);
// 		g_error = d_calloc(3, sizeof(char *));
// 		g_error[0] = d_strdup("1");
// 	}
// 	return (0);
// }


int	d_put_args(char **args, t_cmds *cmd, char *heredoc, t_minishell *mshell)
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
	int		count;

	i = 0;
	j = 0;
	in = 0;
	out = 0;
	start = 0;
	fd = 0;
	end = 0;
	count = d_count_cmds(args);
	cmd->cmd = d_calloc((count + 1), sizeof(char *));
	if (!cmd->cmd)
		return (1);
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
						cmd->infile = d_check_vars(tmp, mshell);
						free(tmp);
						fd = open(cmd->infile, O_RDONLY);
						if (fd == -1)
							end = 1;
						close(fd);
					}
					else if (in == 2)
					{
						hd_stop = d_substr(args[i], start, j - start);
						if (d_start_heredoc(hd_stop, heredoc, mshell) == 1)
							return (1);
						if (end == 0)
						{
							cmd->heredoc = 1;
							cmd->infile = heredoc;
						}
					}
					in = 0;
				}
				else if (out != 0)
				{
					if (end == 0)
					{
						tmp = d_substr(args[i], start, j - start);
						cmd->outfile= d_check_vars(tmp, mshell);
						free(tmp);
						if (out == 1)
						{
							cmd->type = 1;
							fd = open(cmd->outfile, O_RDWR | O_TRUNC | O_CREAT, 0777);
							if (fd == -1)
								end = 1;
						}
						else if (out == 2)
						{
							cmd->type = 2;
							fd = open(cmd->outfile, O_RDWR | O_APPEND | O_CREAT, 0777);
							if (fd == -1)
								end = 1;
						}
						close(fd);
					}
					out = 0;
				}
			}
		}
		i++;
		j = 0;
	}
	d_put_cmds(args, cmd, mshell);
	if (end == 1)
	{
		d_putstr_fd(cmd->infile, 2);
		d_putstr_fd(" : No such file or directory\n", 2);
		d_free_tab(g_error);
		g_error = d_calloc(3, sizeof(char *));
		g_error[0] = d_strdup("1");
	}
	return (0);
}
