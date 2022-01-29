/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:57:09 by dso               #+#    #+#             */
/*   Updated: 2022/01/29 18:08:20 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	d_init_struct(t_minishell *mshell)
{
	mshell->nb_sq = 0;
	mshell->nb_dq = 0;
	mshell->nb_pipe = 0;
	mshell->heredoc = 0;
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


int	ft_parsing(char *input, t_minishell *mshell)
{
	int		i;
	int		j;
	char	**tmp;
	char	**args;

	d_init_struct(mshell);
	i = 0;
	j = 0;
	if (d_check_end(input) == 1)
		return (1);
	if (d_check_quotes(input, mshell) == 1)
		return (1);
	tmp = d_split(input, '|');
	if (!tmp)
		return (1);
	while (tmp[i])
	{
		args = d_split(tmp[i], ' ');
		if (!args)
			return (1);
		i++;
	}
	mshell->nb_pipe = i;
	return (0);
}