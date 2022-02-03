/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:57:09 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 18:51:24 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_parsing(char *input, t_minishell *mshell)
{
	int		i;
	char	**tmp;
	char	**args;
	t_cmds	*cmd;
	char	*heredoc;

	d_init_struct(mshell);
	i = 0;
	if (d_check_end(input) == 1)
		return (1);
	if (d_check_quotes(input, mshell) == 1)
		return (1);
	tmp = d_split(input, '|');
	if (!tmp)
		return (1);
	mshell->nb_pipe = d_count_tab(tmp) - 1;
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
		if (d_put_args(args, cmd, mshell->vars, heredoc) == 1)
			return (1);
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
	}
	d_free_tab(tmp);
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
