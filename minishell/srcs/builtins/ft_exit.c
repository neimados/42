/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 17:28:29 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_minishell *mshell)
{
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
	free(mshell);
	exit(EXIT_SUCCESS);
}