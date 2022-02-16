/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 17:12:31 by dso               #+#    #+#             */
/*   Updated: 2022/02/15 16:19:28 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*d_write_cmd(char *arg, t_parsing *p, t_minishell *m, t_cmds *c)
{
	int		j;
	int		k;
	char	*tmp;
	char	*to_trim;

	j = p->j;
	k = p->k;
	tmp = d_substr(arg, 0, j);
	if (!tmp)
		return (NULL);
	to_trim = d_check_vars(tmp, m);
	if (!to_trim)
		return (NULL);
	free(tmp);
	c->cmd[k] = d_trim_cmd(to_trim);
	if (!c->cmd[k])
		return (NULL);
	return (c->cmd[k]);
}

static void	d_init_struct_parsing(t_parsing *p)
{
	p->i = 0;
	p->j = 0;
	p->k = 0;
	p->l = 0;
	p->sign = 0;
}

static int	d_skip_cmds(t_parsing *p, char *arg)
{
	int	j;

	j = p->j;
	while (arg[j] && arg[j] != '>' && arg[j] != '<')
		j++;
	return (j);
}

static int	d_loop_put_cmds(t_parsing *p, char *arg, t_minishell *m, t_cmds *c)
{
	t_parsing	pp;
	int			sign;
	int			k;

	sign = p->sign;
	pp.j = p->j;
	pp.k = p->k;
	k = p->k;
	if (sign == 0)
	{
		c->cmd[k] = d_write_cmd(arg, &pp, m, c);
		if (!c->cmd[k])
			return (-1);
		k++;
	}
	return (k);
}

int	d_put_cmds(char **args, t_cmds *cmd, t_minishell *mshell)
{
	t_parsing	p;

	d_init_struct_parsing(&p);
	while (args[p.i])
	{
		while (args[p.i][p.j])
		{
			if (args[p.i][p.j] == '>' || args[p.i][p.j] == '<')
			{
				p.sign += 1;
				p.j += 1;
			}
			else
			{
				p.j = d_skip_cmds(&p, args[p.i]);
				p.k = d_loop_put_cmds(&p, args[p.i], mshell, cmd);
				if (p.k == -1)
					return (1);
				p.sign = 0;
			}
		}
		p.i += 1;
		p.j = 0;
	}
	return (0);
}
