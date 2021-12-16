#include "../includes/pipex.h"
#include <stdio.h>


int	ft_search_path_line(char *envp)
{
	int	i;

	i = 0;
	if (envp[0] == 'P' && envp[1] == 'A' && envp[2] == 'T'
	&& envp[3] == 'H')
		return (1);
	return (0);
}

int	ft_cmd(char *argv, char **envp)
{
	char	**cmds;
	char	**paths;
	char	*path;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	cmds = ft_split(argv, ' ');
	while (ft_search_path_line(envp[i]) == 0 && envp[i])
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (cmds[i])
	{
		while (paths[j])
		{
			path = malloc(sizeof(char) * (ft_strlen(paths[j] + 2)));
			while(paths[j][k])
			{
				path[k] = paths[j][k];
				k++;
			}
			path[k] = '/';
			path[k + 1] = '\0';
			path = ft_strjoin(path, cmds[i]);
			if (access(path, F_OK) == 0)
			{
				execve(path, cmds, envp);
				free(path);
				return (0);
			}
			free(path);
			j++;
			k = 0;
		}
		i++;
		j = 0;
	}
	return (1);
}

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
	//close(infile);
	if (ft_cmd(argv[2], envp) == 1)
		return (1);
		
	return (0);
}

int	parent_process(int *end, char **argv, char **envp)
{
	int	outfile;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
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
	close(end[0]);
	//close(outfile);
	if (ft_cmd(argv[3], envp) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		end[2];
	pid_t	fork1;
	
	if (argc != 5)
	{
		write(2, "Invalid Arguments\n", 18);
		exit (EXIT_FAILURE);
	}
	if (pipe(end) == -1)
	{
		write(2, "Pipe Error\n", 11);
		exit (EXIT_FAILURE);
	}
	fork1 = fork();
	if (fork1 == -1)
	{
		write(2, "Fork Error\n", 11);
		exit (EXIT_FAILURE);
	}
	if (fork1 == 0)
	{
		if (child_process(end, argv, envp) == 1)
			exit (EXIT_FAILURE);
	}
	waitpid(fork1, NULL, 0);
	if (parent_process(end, argv, envp) == 1)
		exit (EXIT_FAILURE);
	close(end[0]);
	close(end[1]);
	return (0);
}