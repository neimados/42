/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:13:17 by dso               #+#    #+#             */
/*   Updated: 2022/02/09 10:22:05 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	d_check_end(char *input)
{
	int	i;
	int	j;

	i = d_strlen(input) - 1;
	j = 0;
	while (input[j] == ' ' && input[j])
		j++;
	if (i >= 0)
	{
		while (input[i] == ' ')
			i--;
		if (input[i] == '<' || input[i] == '>')
		{
			d_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
			return (1);
		}
		else if (input[j] == '|' || (input[i] == '|' && i == j))
		{
			d_putstr_fd("syntax error near unexpected token '|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	d_check_quotes(char *input, t_minishell *mshell)
{
	int	i;

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
		d_putstr_fd("Error: Unclosed quote\n", 2);
		return (1);
	}
	return (0);
}

int	d_count_tab(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}
