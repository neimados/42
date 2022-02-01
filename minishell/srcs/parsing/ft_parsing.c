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
		tmp->next = cmd;
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

char	*d_create_heredoc(int i)
{
	char	*filename;
	char	*c;
	int		fd;
	
	c = d_itoa(i);
	filename = d_calloc(24, sizeof(char));
	filename = d_strdup("./srcs/heredoc/.heredoc");
	filename = d_strjoin(filename, c);
	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (NULL);
	free(c);
	close(fd);
	return (filename);
}

int	d_count_cmds(char **args)
{
	int		i;
	int		j;
	int		sign;
	int		count;

	i = 0;
	j = 0;
	sign = 0;
	count = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '>' || args[i][j] == '<')
			{
				sign++;
				j++;
			}
			else
			{
				if (sign == 0)
					count++;
				else
					sign = 0;
				while (args[i][j] && (args[i][j] != '>' && args[i][j] != '<'))
					j++;
			}
		}
		i++;
		j = 0;
	}
	return (count);
}

void	d_put_cmds(char **args, t_cmds *cmd)
{
	int		i;
	int		j;
	int		k;
	int		sign;

	i = 0;
	j = 0;
	k = 0;
	sign = 0;
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '>' || args[i][j] == '<')
			{
				sign++;
				j++;
			}
			else
			{
				while (args[i][j] && args[i][j] != '>' && args[i][j] != '<')
					j++;
				if (sign == 0)
					cmd->cmd[k++] = d_substr(args[i], 0, j);
				else
					sign = 0;
			}
		}
		i++;
		j = 0;
	}
}

void	d_start_heredoc(char *hd_stop, char *heredoc)
{
	char	*input;
	int		length;
	int		fd;

	fd = open(heredoc, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return ;
	length = d_strlen(hd_stop);
	input = readline("> ");
	if (input == NULL)
	{
		close(fd);
		return ;
	}
	while (1)
	{
		if (input == NULL)
		{
			close(fd);
			return ;
		}
		else if (d_strncmp(hd_stop, input, length) == 0)
			return ;
		write(fd, input, d_strlen(input));
		write(fd, "\n", 1);
		input = readline("> ");
	}
	close(fd);
}

int	d_put_args(char **args, t_cmds *cmd, char *heredoc)
{
	int		i;
	int		j;
	int		in;
	int		out;
	int		start;
	int		fd;
	char	*hd_stop;
	int		end;

	i = 0;
	j = 0;
	in = 0;
	out = 0;
	start = 0;
	fd = 0;
	end = 0;
	cmd->cmd = d_calloc((d_count_cmds(args) + 1), sizeof(char *));
	if (!cmd->cmd)
		return (1);
	d_put_cmds(args, cmd);
	while (args[i])
	{
		while (args[i][j])
		{
			if (args[i][j] == '<' || args[i][j] == '>')
			{
				if (args[i][j] == '<')
					in++;
				else if (args[i][j] == '>')
					out++;
				j++;
			}
			else
			{
				start = j;
				while (args[i][j] && args[i][j] != '>' && args[i][j] != '<')
					j++;
				if (in != 0)
				{
					if (in == 1 && end == 0)
					{
						cmd->infile = d_substr(args[i], start, j - start);
						fd = open(cmd->infile, O_RDONLY);
						if (fd == -1)
							end = 1;
						close(fd);
					}
					else if (in == 2)
					{
						hd_stop = d_substr(args[i], start, j - start);
						d_start_heredoc(hd_stop, heredoc);
						if (end == 0)
						cmd->infile = heredoc;
					}
					in = 0;
				}
				else if (out != 0)
				{
					if (out == 1)
						cmd->type = 1;
					else if (out == 2)
						cmd->type = 2;
					out = 0;
					cmd->outfile = d_substr(args[i], start, j - start);
					fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
					if (fd == -1)
						end = 1;
					close(fd);
				}
			}
		}
		i++;
		j = 0;
	}
	if (end == 1)
		printf("%s\n", strerror(errno));
	return (0);
}

void	d_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

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
		cmd = d_init_lst();
		if (!cmd)
			return (1);
		args = d_split(tmp[i], ' ');
		if (!args)
			return (1);
		heredoc = d_create_heredoc(i);
		if (!heredoc)
			return (1);
		if (d_put_args(args, cmd, heredoc) == 1)
			return (1);
		d_add_lst(mshell, cmd);
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
	}
	d_free_tab(tmp);
	d_free_tab(args);
	//TEST
	t_cmds *test;
	test = mshell->cmds;
	while (test != NULL)
	{
		i = 0;
		while (test->cmd[i])
		{
			printf("cmd : %s\n", test->cmd[i]);
			i++;
		}
		printf("infile : %s\n", test->infile);
		printf("outfile : %s\n", test->outfile);
		printf("type : %d\n", test->type);
		printf("\n");
		test = test->next;
	}
	d_free_tab(mshell->cmds->cmd);
	//TEST
	return (0);
}