/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:32:59 by dso               #+#    #+#             */
/*   Updated: 2022/02/14 18:24:31 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_input(char **envp, t_minishell *mshell)
{
	char	*input;

	ft_cp_env(envp, mshell);
	while (1)
	{
		input = readline("\x1b[34m""minishell$> ""\x1b[34m");
		add_history(input);
		if (input == NULL)
		{
			printf("\b\bexit\n");
			free(mshell->pwd);
			d_free_tab(mshell->g_mini_env);
			free(mshell);
			d_free_tab(g_error);
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
			if (test->outfile)
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
	t_minishell			*mshell;

	mshell = malloc(sizeof(t_minishell));
	if (!mshell)
		exit(EXIT_FAILURE);
	g_error = d_calloc(3, sizeof(char *));
	if (!g_error)
		exit(EXIT_FAILURE);
	g_error[0] = d_strdup("0");
	d_init_struct(mshell);
	(void)argv;
	if (argc != 1)
	{
		d_putstr_fd("No args allowed\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_terminal(0);
	// ft_block_signal(SIGQUIT);
	// ft_signal(SIGINT, ft_handle_signal);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	ft_input(envp, mshell);
	return (0);
}
