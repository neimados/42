/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:32:59 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 17:57:08 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_signal(int keycode)
{
	if (keycode == SIGINT)
	{
		printf("\n");
		ft_input();
	}
	if (keycode == SIGQUIT)
	{
		printf("\b\b \b\b");
		//rl_replace_line("", 0); TO FIX
	}
}

void	ft_input(void)
{
	char				*input;
	struct sigaction	signals;
	t_minishell			*mshell;

	signals.sa_handler = ft_signal;
	sigaction(SIGINT, &signals, NULL);
	sigaction(SIGQUIT, &signals, NULL);
	mshell = malloc(sizeof(t_minishell));
	if (!mshell)
		exit(EXIT_FAILURE);
	while (1)
	{
		input = readline("minishell$> ");
		add_history(input);
		if (input == NULL)
		{
			printf("\b\bexit\n");
			//free
			//exit(EXIT_SUCCESS);
			free(mshell);
			return ;
		}
		if (ft_parsing(input, mshell) == 1)
		{
			//free;
		}
		else
		{
			//ft_exec;
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
			//TEST
		}
		free(input);
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
