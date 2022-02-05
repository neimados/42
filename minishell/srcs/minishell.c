/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:32:59 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 17:36:32 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_signal(int keycode)
{
	if (keycode == SIGINT)
	{
		printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		ft_input();
	}
	if (keycode == SIGQUIT)
	{
		printf("\b\b \b\b");
		//rl_replace_line("", 0);
	}
}

void	ft_input(void)
{
	char				*input;
	struct sigaction	signals;
	t_minishell			*mshell;
	int					tmp;

	signals.sa_handler = ft_signal;
	sigaction(SIGINT, &signals, NULL);
	sigaction(SIGQUIT, &signals, NULL);
	mshell = malloc(sizeof(t_minishell));
	if (!mshell)
		exit(EXIT_FAILURE);
	while (1)
	{
		tmp = errno;
		input = readline("minishell$> ");
		errno = tmp;
		add_history(input);
		if (input == NULL)
		{
			printf("\b\bexit\n");
			//free
			free(mshell);
			exit(EXIT_SUCCESS);
		}
		if (ft_parsing(input, mshell) == 0)
		{
			k_loop_forks(mshell);
		}
		//TEST
		t_cmds	*test;
		test = mshell->cmds;
		while (test != NULL)
		{
			d_free_tab(test->cmd);
			if (test->infile)
				free(test->infile);
			else if (test->outfile)
				free(test->outfile);
			test = test->next;
			free(mshell->cmds);
			mshell->cmds = test;
		}
		free(input);
		//TEST
	}
}

int	main (int argc, char **argv, char **envp)
{
	struct	sigaction signals;

	(void)argv;
	if (argc != 1)
	{
		write (2, "No args allowed\n", 16);
		exit(EXIT_FAILURE);
	}
	signals.sa_handler = ft_signal;
	sigaction(SIGINT, &signals, NULL);//ctrl+C
	sigaction(SIGQUIT, &signals, NULL);//ctrl+\'
	ft_cp_env(envp);
	ft_input();
	return (0);
}
