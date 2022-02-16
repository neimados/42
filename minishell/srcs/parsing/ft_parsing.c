/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:57:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/16 15:55:11 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_check_pipe(char *input, t_minishell *mshell)
{
	int	i;

	i = d_strlen(input) - 1;
	while (input[i] == ' ')
		i--;
	while (i > 0)
	{
		if (input[i] == '|')
		{
			mshell->open_pipe = 1;
			return ;
		}
		else
		{
			mshell->open_pipe = 0;
			return ;
		}
	}
	return ;
}

int	d_open_pipe(t_minishell *mshell, int heredoc_num)
{
	int		i;
	char	**tmp;
	char	**args;
	t_cmds	*cmd;
	char	*heredoc;
	char	*input;
	pid_t	fork_pipe;
	char	*fork_id;
	int		fd;
	int		status[1];

	i = 0;
	mshell->nb_sq = 0;
	mshell->nb_dq = 0;
	fork_pipe = fork();
	if (fork_pipe == -1)
		return (1);
	fork_id = d_itoa(fork_pipe);
	g_error[1] = d_strjoin(g_error[1], fork_id);
	free(fork_id);
	signal(SIGINT, sigint_handler_minishell);
	if (fork_pipe == 0)
	{
		signal(SIGINT, sigint_handler_hd);
		fd = open("/private/tmp/tmp_pipe", O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (fd == -1)
			exit(EXIT_FAILURE);
		input = readline("> ");
		if (input == NULL)
		{
			close(fd);
			free(input);
			d_putstr_fd("syntax error: unexpected end of file\n", 2);
			exit(EXIT_FAILURE);
		}
		write(fd, input, d_strlen(input));
		close(fd);
		free(input);
		exit(EXIT_SUCCESS);
	}
	waitpid(fork_pipe, status, 0);
	if (WEXITSTATUS(status[0])== 1)
	{
		mshell->open_pipe = 0;
		return (1);
	}
	fd = open("/private/tmp/tmp_pipe", O_RDONLY);
	if (fd == -1)
		return (1);
	input = get_next_line(fd);
	close(fd);
	unlink("/private/tmp/tmp_pipe");
	if (d_check_end(input) == 1)
		return (1);
	if (d_check_quotes(input, mshell) == 1)
		return (1);
	tmp = d_split(input, '|');
	if (!tmp)
		return (1);
	i = 0;
	while (tmp[i])
	{
		cmd = d_init_cmds();
		if (!cmd)
			return (1);
		args = d_split(tmp[i], ' ');
		if (!args)
			return (1);
		heredoc = d_create_heredoc(heredoc_num);
		if (!heredoc)
			return (1);
		if (d_put_args(args, cmd, heredoc, mshell) == 1)
		{
			d_free_tab(args);
			d_free_tab(tmp);
			d_free_tab(cmd->cmd);
			free(cmd);
			unlink(heredoc);
			free(heredoc);
			return (1);
		}
		d_add_cmds(mshell, cmd);
		if (!cmd->infile)
		{
			unlink(heredoc);
			free(heredoc);
		}
		else
		{
			if (d_strncmp(cmd->infile, heredoc, d_strlen(cmd->infile) != 0))
			{
				unlink(heredoc);
				free(heredoc);
			}
		}
		i++;
		d_free_tab(args);
		d_check_pipe(input, mshell);
	}
	d_free_tab(tmp);
	free(input);
	return (0);
}

int	ft_parsing(char *input, t_minishell *mshell)
{
	int		i;
	char	**tmp;
	char	**args;
	t_cmds	*cmd;
	char	*heredoc;

	i = 0;
	mshell->nb_sq = 0;
	mshell->nb_dq = 0;
	if (d_check_end(input) == 1)
		return (1);
	if (d_check_quotes(input, mshell) == 1)
		return (1);
	tmp = d_split(input, '|');
	if (!tmp)
		return (1);
	while (tmp[i])
	{
		cmd = d_init_cmds();
		if (!cmd)
			return (1);
		args = d_split(tmp[i], ' ');
		if (!args)
			return (1);
		heredoc = d_create_heredoc(i);
		if (!heredoc)
			return (1);
		if (d_put_args(args, cmd, heredoc, mshell) == 1)
		{
			d_free_tab(args);
			d_free_tab(tmp);
			d_free_tab(cmd->cmd);
			free(cmd);
			unlink(heredoc);
			free(heredoc);
			return (1);
		}
		d_add_cmds(mshell, cmd);
		if (!cmd->infile)
		{
			unlink(heredoc);
			free(heredoc);
		}
		else
		{
			if (d_strncmp(cmd->infile, heredoc, d_strlen(cmd->infile) != 0))
			{
				unlink(heredoc);
				free(heredoc);
			}
		}
		i++;
		d_free_tab(args);
		d_check_pipe(input, mshell);//OPEN PIPE
	}
	d_free_tab(tmp);
	while (mshell->open_pipe == 1) // OPEN PIPE
	{
		if (d_open_pipe(mshell, i) == 1)
			return (1);
		i++;
	}// OPEN PIPE
	// //TEST
	// t_cmds *test;
	// test = mshell->cmds;
	// while (test != NULL)
	// {
	// 	i = 0;
	// 	while (test->cmd[i])
	// 	{
	// 		printf("cmd : %s\n", test->cmd[i]);
	// 		i++;
	// 	}
	// 	printf("infile : %s\n", test->infile);
	// 	printf("outfile : %s\n", test->outfile);
	// 	printf("type : %d\n", test->type);
	// 	printf("\n");
	// 	test = test->next;
	// }
	// exit(0);
	// //TEST
	return (0);
}
