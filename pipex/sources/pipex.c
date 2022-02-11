/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 10:32:39 by dso               #+#    #+#             */
/*   Updated: 2022/01/24 13:35:14 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	child_process(int *end, char **argv, char **envp)
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		return (1);
	if (dup2(end[1], STDOUT_FILENO) == -1)
	{
		close(infile);
		return (1);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		close(infile);
		return (1);
	}
	close(end[0]);
	close(infile);
	if (ft_cmd(argv[2], envp) == 1)
		return (1);
	return (0);
}

int	parent_process(int *end, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (outfile == -1)
		return (1);
	if (dup2(end[0], STDIN_FILENO) == -1)
	{
		close(outfile);
		return (1);
	}
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		close(outfile);
		return (1);
	}
	close(end[1]);
	close(outfile);
	if (ft_cmd(argv[3], envp) == 1)
		return (1);
	return (0);
}

void	ft_pipex(char **argv, char **envp)
{
	int		end[2];
	pid_t	fork1;

	if (pipe(end) == -1)
		ft_error();
	fork1 = fork();
	if (fork1 == -1)
		ft_error();
	if (fork1 == 0)
	{
		if (child_process(end, argv, envp) == 1)
			ft_error();
	}
	// if (argv[3][0] == 'l' && argv[3][1] == 's')
	// 	waitpid(fork1, NULL, 0);
	
	if (parent_process(end, argv, envp) == 1)
	{
		waitpid(fork1, NULL, 0);
		ft_error();
	}
	waitpid(fork1, NULL, 0);
	close(end[0]);
	close(end[1]);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(2, "Invalid Arguments\n", 18);
		exit (EXIT_FAILURE);
	}
	ft_pipex(argv, envp);
	return (0);
}
