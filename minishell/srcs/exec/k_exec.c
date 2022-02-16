/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:05:49 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/15 18:10:34 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include <string.h>

void	ft_error(char *str1, char *str2)
{
	write(2, "minishell: ", 11);
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	if (!d_strncmp(g_error[0], "127", 3))
		exit(127);
	else
		exit(errno);
}

void	k_exec_cmd(char **cmd, t_minishell *minishell)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	if (access(cmd[i], X_OK) == 0)
		execve(cmd[i], cmd, minishell->g_mini_env);
	while (minishell->g_mini_env[i] && (minishell->g_mini_env[i][0] != 'P' || minishell->g_mini_env[i][1] != 'A'
	|| minishell->g_mini_env[i][2] != 'T' || minishell->g_mini_env[i][3] != 'H'))
		i++;
	if (minishell->g_mini_env[i])
		path = ft_split(minishell->g_mini_env[i] + 5, ':');
	else
		ft_error(cmd[0], "No such file or directory");
	i = 0;
	while (path && path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd[0]);
		i++;
	}
	i = -1;
	while (path && path[++i])
	{
		if (access(path[i], X_OK) == 0)
			execve(path[i], cmd, minishell->g_mini_env);
	}
	if (path)
		free(path[0]);
	g_error[0] = "127";
	i = 0;
	ft_error(cmd[0], "command not found");
}

void	k_exec_builtins(char **cmd, t_minishell *minishell)
{
	int	len;
	int	i;

	len = d_strlen(cmd[0]);
	i = 0;
	if (!d_strncmp(cmd[0], "echo", len))
		ft_echo(cmd);
	else if (!d_strncmp(cmd[0], "cd", len))
		ft_exit(minishell, cmd);
	else if (!d_strncmp(cmd[0], "pwd", len))
		ft_pwd(cmd, minishell);
	else if (!d_strncmp(cmd[0], "export", len))
		ft_exit(minishell, cmd);
	else if (!d_strncmp(cmd[0], "unset", len))
		ft_exit(minishell, cmd);
	else if (!d_strncmp(cmd[0], "env", len))
	{
		while (minishell->g_mini_env[i] && (minishell->g_mini_env[i][0] != 'P' || minishell->g_mini_env[i][1] != 'A'
		|| minishell->g_mini_env[i][2] != 'T' || minishell->g_mini_env[i][3] != 'H'))
		i++;
		if (minishell->g_mini_env[i])
			ft_env(cmd, minishell);
		else
			ft_error(cmd[0], "No such file or directory");
	}
	else if (!d_strncmp(cmd[0], "exit", len))
		ft_exit(minishell, cmd);
}

void	k_is_builtin_fct(char **cmd, t_minishell *minishell)
{
	int	len;

	len = d_strlen(cmd[0]);
	if (!d_strncmp(cmd[0], "echo", len) || !d_strncmp(cmd[0], "cd", len)
		|| !d_strncmp(cmd[0], "pwd", len) || !d_strncmp(cmd[0], "export", len)
		|| !d_strncmp(cmd[0], "unset", len) || !d_strncmp(cmd[0], "env", len)
		|| !d_strncmp(cmd[0], "exit", len))
		k_exec_builtins(cmd, minishell);
	else
	{
		k_exec_cmd(cmd, minishell);
	}
}

void	k_child(t_minishell *minishell, int i)
{
	t_cmds	*tmp;
	t_cmds	*tmp2;
	int		fd_in;
	int		fd_out;

	
	tmp = minishell->cmds;
	if (i == 0)
	{
		if (tmp->infile)
		{
			fd_in = open(tmp->infile, O_RDONLY);
			if (fd_in == -1)
				ft_error(strerror(errno), tmp->infile);
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_error(strerror(errno), NULL);
			close(fd_in);
		}
		if (tmp->outfile)
		{
			if (tmp->type == 1)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL);
			}
			else if (tmp->type == 2)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_APPEND
						| O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL);
			}
		}
		else if (tmp->next)
		{
			if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL);
			close(tmp->next->pipe[1]);
		}
		k_is_builtin_fct(tmp->cmd, minishell);
	}
	while (tmp && i - 1 > 0)
	{
		if (tmp->next)
		{
			close(tmp->next->pipe[0]);
			close(tmp->next->pipe[1]);
		}
		tmp = tmp->next;
		i--;
	}
	tmp2 = tmp;
	tmp = tmp->next;
	if (tmp)
	{
		if (tmp->infile)
		{
			close(tmp->pipe[0]);
			fd_in = open(tmp->infile, O_RDONLY);
			if (fd_in == -1)
				ft_error(strerror(errno), tmp->infile);
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_error(strerror(errno), NULL);
			close(fd_in);
		}
		else if (i != 0)
		{
			close (tmp->pipe[1]);
			fd_in = tmp->pipe[0];
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_error(strerror(errno), NULL);
			close(fd_in);
		}
		if (tmp->outfile)
		{
			if (tmp->next)
				close(tmp->next->pipe[0]);
			if (tmp->type == 1)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL);
			}
			else if (tmp->type == 2)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_APPEND
						| O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL);
			}
		}
		else if (tmp->next)
		{
			if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL);
			close(tmp->next->pipe[1]);
		}
		k_is_builtin_fct(tmp->cmd, minishell);
	}
}

void	k_loop_forks(t_minishell *minishell)
{
	int		i;
	int		j;
	char	*pidtmp;
	int		nbcmd;
	pid_t	*forks;
	t_cmds	*tmp;
	t_cmds	*tmp2;
	int		stat[1];

	if (minishell->cmds == NULL)
		return ;
	if (minishell->cmds->cmd[0] == NULL)
		return ;
	tmp = minishell->cmds;
	tmp2 = tmp;
	nbcmd = 0;
	while (tmp2)
	{
		nbcmd++;
		tmp2 = tmp2->next;
	}
	tmp2 = tmp;
	i = d_strlen(tmp->cmd[0]);
	if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "exit", i))
	{
		ft_exit(minishell, tmp->cmd);
		return ;
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "export", i))
	{
		ft_export(tmp->cmd, minishell);
		return ;
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "cd", i))
	{
		ft_cd(tmp->cmd, minishell);
		return ;
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "unset", i))
	{
		ft_unset(tmp->cmd, minishell);
		return ;
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "cat", i))
	{
		ft_terminal(2);
		signal(SIGINT, sigint_handler_spec);
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "./minishell", i))
	{
		ft_terminal(0);
		signal(SIGINT, sigint_handler_minishell);
	}
	else
	{
		ft_terminal(1);
		signal(SIGINT, sigint_handler_child);
	}
	forks = malloc(sizeof(pid_t) * nbcmd);
	i = 0;
	while (i < nbcmd)
	{
		if (tmp->next)
			pipe(tmp->next->pipe);
		forks[i] = fork();
		if (forks[i] == 0)
		{
			if (tmp->next && !tmp->next->next)
				close(tmp->next->pipe[0]);
			k_child(minishell, i);
		}
		g_error[1] = d_strjoin(g_error[1], " ");
		pidtmp = d_itoa(forks[i]);
		g_error[1] = d_strjoin(g_error[1], pidtmp);
		free(pidtmp);
		tmp = tmp->next;
		i++;
	}
	i -= 1;
	j = i;
	tmp2 = minishell->cmds->next;
	while (tmp2)
	{
		close(tmp2->pipe[0]);
		close(tmp2->pipe[1]);
		tmp2 = tmp2->next;
	}
	while (i >= 0)
	{
		waitpid(forks[i], stat, 0);
		if (i == j)
		{
			if (d_strncmp(g_error[0], "130", 3) != 0 && WEXITSTATUS(stat[0]) != 2)
			{
				free(g_error[0]);
				g_error[0] = d_itoa(WEXITSTATUS(stat[0]));
			}
		}
		i--;
	}
	tmp2 = minishell->cmds;
	while (tmp2)
	{
		if (tmp2->heredoc == 1)
			unlink(tmp2->infile);
		tmp2 = tmp2->next;
	}
	free(forks);
	signal(SIGINT, sigint_handler);
	ft_terminal(0);
	return ;
}
