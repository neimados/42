/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/07 17:40:39 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(char **cmds, t_minishell *mshell)
{
	int	i;

	i = 0;
	if (cmds[1])
	{
		printf("pwd: too many arguments\n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", mshell->pwd);
	exit(EXIT_SUCCESS);
}
