/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:57:09 by dso               #+#    #+#             */
/*   Updated: 2022/01/31 18:38:26 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_init_struct(t_minishell *mshell)
{
	mshell->nb_sq = 0;
	mshell->nb_dq = 0;
	mshell->nb_pipe = 0;
}

int	d_check_end(char *input)
{
	int	i;
	int	j;

	i = d_strlen(input) - 1;
	j = 0;
	while (input[i] == ' ')
		i--;
	while (input[j] == ' ')
		j++;
	if (input[i] == '<' || input[i] == '>')
	{
		printf("syntax error near unexpected token 'newline'\n");
		return (1);
	}
	else if (input[i] == '|' || input[j] == '|')
	{
		printf("syntax error near unexpected token '|'\n");
		return (1);
	}
	return (0);
}

int	d_check_quotes(char *input, t_minishell *mshell)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			mshell->nb_sq += 1;
		else if (input[i] == '\"')
			mshell->nb_dq += 1;
		i++;
	}
	if (mshell->nb_sq % 2 != 0 || mshell->nb_dq % 2 != 0)
	{
		write (2, "Error: Unclosed quote\n", 22);
		return (1);
	}
	return (0);
}

t_cmds	*d_init_lst(void)
{
	t_cmds	*cmds;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->cmd = NULL;
	cmds->infile = NULL;
	cmds->type = 0;
	cmds->outfile = NULL;
	cmds->next = NULL;
	return (cmds);
}

void	*d_add_lst(t_minishell *mshell, t_cmds *cmd)
{
	t_cmds	*tmp;
	
	tmp = mshell->cmds;
	if (mshell->cmds == NULL)
		mshell->cmds = cmd;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp = cmd;
	}
	return (0);
}

int	d_put_args(char **args, t_cmds *cmd)
{
	(void)args;
	(void)cmd;
	// int	i;

	// i = 0;
	// while (args[i])
	// {
	// 	if (args[i] == '<')
	// 	{

	// 	}
	// 	else if (args[i] == '>')
	// 	{
			
	// 	}
	// 	else
	// 	{
			
	// 	}
	// }
	return (0);
}

int	d_count_pipe(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	return (i - 1);
}

int	ft_parsing(char *input, t_minishell *mshell)
{
	int		i;
	char	**tmp;
	char	**args;
	t_cmds	*cmd;

	d_init_struct(mshell);
	i = 0;
	if (d_check_end(input) == 1)
		return (1);
	if (d_check_quotes(input, mshell) == 1)
		return (1);
	tmp = d_split(input, '|');
	if (!tmp)
		return (1);
	mshell->nb_pipe = d_count_pipe(tmp);
	//create heredoc files
	while (tmp[i])
	{
		cmd = d_init_lst();
		if (!cmd)
			return (1);
		args = d_split(tmp[i], ' ');
		if (!args)
			return (1);
		if (d_put_args(args, cmd) == 1)
			return (1);
		d_add_lst(mshell, cmd);
		i++;
	}
	return (0);
}