/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:05:49 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/05 17:46:50 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *str1, char *str2, char **env)
{
	char	*str0;
	int		i;

	i = 0;
	while (env[i] && (env[i][0] != 'S' || env[i][1] != 'H' || env[i][2] != 'E'
	|| env[i][3] != 'L' || env[i][4] != 'L'))
		i++;
	if (env[i][0] != 'S' && env[i][1] != 'H' && env[i][2] != 'E'
	&& env[i][3] != 'L' && env[i][4] != 'L')
		str0 = NULL;
	else
		str0 = ft_strrchr(env[i], '/');
	write(2, str0 + 1, ft_strlen(str0 + 1));
	if (str1)
		write(2, ": ", 2);
	write(2, str1, ft_strlen(str1));
	if (str2)
		write(2, ": ", 2);
	write(2, str2, ft_strlen(str2));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	k_exec_cmd(char **cmd)
{
	int		i;
	char	**path;

	i = 0;
	if (access(cmd[i], X_OK) == 0)
		execve(cmd[i], cmd, g_mini_env);
	while (g_mini_env[i] && (g_mini_env[i][0] != 'P' || g_mini_env[i][1] != 'A'
	|| g_mini_env[i][2] != 'T' || g_mini_env[i][3] != 'H'))
		i++;
	path = ft_split(g_mini_env[i] + 5, ':');
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], cmd[0]);
		i++;
	}
	i = -1;
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
			execve(path[i], cmd, g_mini_env);
	}
	free(path[0]);
	ft_error("Command not found", cmd[0], g_mini_env);
}

void	k_exec_builtins(char **cmd , t_minishell *minishell)
{
	int	len;

	len = d_strlen(cmd[0]);
	if (!d_strncmp(cmd[0], "echo", len))
		ft_echo(cmd);
	else if (!d_strncmp(cmd[0], "cd", len))
		ft_exit(minishell, cmd);
	else if (!d_strncmp(cmd[0], "pwd", len))
		ft_pwd(cmd);
	else if (!d_strncmp(cmd[0], "export", len))
		ft_exit(minishell, cmd);
	else if (!d_strncmp(cmd[0], "unset", len))
		ft_exit(minishell, cmd);
	else if (!d_strncmp(cmd[0], "env", len))
		ft_env(cmd);
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
		k_exec_cmd(cmd);
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
			fd_in = open(tmp->next->infile, O_RDONLY);
			if (fd_in == -1)
				ft_error(strerror(errno), tmp->next->infile, g_mini_env);
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
			close(fd_in);
		}
		if (tmp->outfile)
		{
			if (tmp->type == 1)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL, g_mini_env);
			}
			else if (tmp->type == 2)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_APPEND
						| O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL, g_mini_env);
			}
		}
		else if (tmp->next)
		{
			if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
			close(tmp->next->pipe[1]);
		}
		k_is_builtin_fct(tmp->cmd, minishell);
	}
	while (tmp && i - 1 > 0)
	{
		if (tmp->next)
		{
			close(tmp->pipe[0]);
			close(tmp->pipe[1]);
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
				ft_error(strerror(errno), tmp->infile, g_mini_env);
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
			close(fd_in);
		}
		else if (i != 0)
		{
			close (tmp->pipe[1]);
			fd_in = tmp->pipe[0];
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
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
					ft_error(strerror(errno), NULL, g_mini_env);
			}
			else if (tmp->type == 2)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_APPEND
						| O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL, g_mini_env);
			}
		}
		else if (tmp->next)
		{
			if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
			close(tmp->next->pipe[1]);
		}
		k_is_builtin_fct(tmp->cmd, minishell);
	}
}

void	k_loop_forks(t_minishell *minishell)
{
	int		i;
	int		nbcmd;
	pid_t	*forks;
	t_cmds	*tmp;
	t_cmds	*tmp2;

	if (minishell->cmds == NULL)
		return ;
	if (minishell->cmds->cmd[0] == NULL)
		return ;	
	tmp = minishell->cmds;
	tmp2 = tmp;
	nbcmd = minishell->nb_pipe + 1;
	i = d_strlen(tmp->cmd[0]);
	if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "exit", i))
	{
		ft_exit(minishell, tmp->cmd);
		return ;
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "export", i))
	{
		ft_export(tmp->cmd);
		return ;
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "cd", i))
	{
		ft_cd(tmp->cmd);
		return ;
	}
	else if (nbcmd == 1 && !d_strncmp(tmp->cmd[0], "unset", i))
	{
		ft_unset(tmp->cmd);
		return ;
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
		tmp = tmp->next;
		i++;
	}
	i -= 1;
	while (i >= 0)
	{
		if (tmp2)
		{
			if (tmp2->heredoc == 1)
				unlink(tmp2->infile);
			tmp2 = tmp2->next;
		}
		if (tmp2)
		{
			close(tmp2->pipe[0]);
			close(tmp2->pipe[1]);
		}
		waitpid(forks[i], NULL, 0);
		i--;
	}
	return ;
}
