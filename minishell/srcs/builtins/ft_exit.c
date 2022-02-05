/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 12:36:56 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	d_check_digit(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(t_minishell *mshell, char **cmds)
{
	t_cmds	*test;

	if (cmds[1])
		if (d_check_digit(cmds[1]) == 1)
			printf("exit: %s: numeric argument required\n", cmds[1]);
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
	free(mshell);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
