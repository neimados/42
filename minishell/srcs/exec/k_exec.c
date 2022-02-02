/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   k_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:05:49 by kmammeri          #+#    #+#             */
/*   Updated: 2022/02/02 18:40:42 by kmammeri         ###   ########.fr       */
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
	// char	tmp[1000];

	i = 0;
	if (access(cmd[i], X_OK) == 0)
		execve(cmd[i], cmd, g_mini_env);
	// write(2, "test9\n", 6);
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
	// read(0, tmp, 1000);
	// dprintf(2, "%s\n", tmp);
	while (path[++i])
	{
		if (access(path[i], X_OK) == 0)
		{
			// write(2, "test10\n", 7);
			// dprintf(2, "%s\n", cmd[0]);
			execve(path[i], cmd, g_mini_env);
		}
	}
	free(path[0]);
	// write(2, "test11\n", 7);
	ft_error("Command not found\n", cmd[0], g_mini_env);
}

int	k_strncmp(const char *first, const char *second, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (0);
	while (i < len - 1 && first[i] == second[i] && first[i])
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}

void	k_is_builtin_fct(char **cmd)
{
	if (!k_strncmp(cmd[0], "echo", 4) || !k_strncmp(cmd[0], "cd", 2)
		|| !k_strncmp(cmd[0], "pwd", 3) || !k_strncmp(cmd[0], "export", 6)
		|| !k_strncmp(cmd[0], "unset", 5) || !k_strncmp(cmd[0], "env", 3)
		|| !k_strncmp(cmd[0], "exit", 4))
		//k_exec_builtins(minishell, cmd);
	{
		write(1, "test13\n", 7);
		exit(EXIT_SUCCESS);
	}
	else
	{
		// write(2, "test8\n", 6);
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
			// close(tmp->next->pipe[0]);  a voir
			if (tmp->type == 1)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL, g_mini_env);
				// write(2, "test0\n", 6);
			}
			else if (tmp->type == 2)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_APPEND
						| O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL, g_mini_env);
				// write(2, "test1\n", 6);
			}
		}
		else if (tmp->next)
		{
			if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
			close(tmp->next->pipe[1]);
			// write(2, "test2\n", 6);
		}
		k_is_builtin_fct(tmp->cmd);
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
			// write(2, "test3\n", 6);
		}
		else if (i != 0)
		{
			close (tmp->pipe[1]);
			fd_in = tmp->pipe[0];
			if (dup2(fd_in, STDIN_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
			close(fd_in);
			// write(2, "test4\n", 6);
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
				// write(2, "test5\n", 6);
			}
			else if (tmp->type == 2)
			{
				fd_out = open(tmp->outfile, O_WRONLY | O_APPEND
						| O_CREAT, 0666);
				if (dup2(fd_out, STDOUT_FILENO) == -1)
					ft_error(strerror(errno), NULL, g_mini_env);
				// write(2, "test6\n", 6);
			}
		}
		else if (tmp->next)
		{
			if (dup2(tmp->next->pipe[1], STDOUT_FILENO) == -1)
				ft_error(strerror(errno), NULL, g_mini_env);
			close(tmp->next->pipe[1]);
			// write(2, "test7\n", 6);
		}
		k_is_builtin_fct(tmp->cmd);
	}
}

void	k_loop_forks(t_minishell *minishell)
{
	int		i;
	int		nbcmd;
	pid_t	*forks;
	t_cmds	*tmp;

	tmp = minishell->cmds;
	nbcmd = minishell->nb_pipe + 1;
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
	waitpid(-1, NULL, 0);
	return ;
}
