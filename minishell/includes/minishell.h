/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:24:12 by dso               #+#    #+#             */
/*   Updated: 2022/01/29 17:52:41 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

char **g_mini_env;

typedef struct s_cmds		t_cmds;
typedef struct s_minishell	t_minishell;
typedef struct s_var		t_var;

struct s_cmds
{
	char		**cmd;
	char		*infile; // < infile
	int			type; //1 = > ; 2 = >>
	char		*outfile; // > outfile (open)
	t_cmds		*next;
};

struct s_var
{
	char	*name;
	char	*value;
	t_var	*next;
};

struct s_minishell
{
	t_cmds		*cmds;
	t_var		*vars;
	int			nb_sq;
	int			nb_dq;
	int			nb_pipe;
	int			heredoc; // << + function write outfile + unlink
};

void	ft_input(void);
void	ft_cp_env(char **envp);
int		ft_parsing(char *input, t_minishell *mshell);
char	**d_split(char *s, char c);
char	*d_strdup(const char *str);
size_t	d_strlen(const char *str);
void	*d_calloc(size_t count, size_t size);

#endif