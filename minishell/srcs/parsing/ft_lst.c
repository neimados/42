/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 11:11:12 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 18:07:39 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_init_struct(t_minishell *mshell)
{
	mshell->nb_sq = 0;
	mshell->nb_dq = 0;
	mshell->nb_pipe = 0;
	mshell->cmds = NULL;
}

t_cmds	*d_init_cmds(void)
{
	t_cmds	*cmds;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->cmd = NULL;
	cmds->infile = NULL;
	cmds->type = 0;
	cmds->heredoc = 0;
	cmds->outfile = NULL;
	cmds->next = NULL;
	return (cmds);
}

void	*d_add_cmds(t_minishell *mshell, t_cmds *cmd)
{
	t_cmds	*tmp;
	
	tmp = mshell->cmds;
	if (mshell->cmds == NULL)
		mshell->cmds = cmd;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = cmd;
	}
	return (0);
}