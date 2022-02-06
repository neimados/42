/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:32:59 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 18:36:55 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_input(void)
{
	char				*input;
	t_minishell			*mshell;

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
	(void)argv;
	if (argc != 1)
	{
		write (2, "No args allowed\n", 16);
		exit(EXIT_FAILURE);
	}
	if (ft_terminal() == 1)
	{
		write (2, "Terminal error\n", 15);
		exit(EXIT_FAILURE);
	}
	ft_block_signal(SIGQUIT);
	ft_signal(SIGINT, ft_handle_signal);
	ft_cp_env(envp);
	ft_input();
	return (0);
}
