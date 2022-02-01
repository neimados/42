/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:24:12 by dso               #+#    #+#             */
/*   Updated: 2022/01/31 18:36:00 by dso              ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

char **g_mini_env;

typedef struct s_cmds		t_cmds;
typedef struct s_minishell	t_minishell;
typedef struct s_var		t_var;

struct s_cmds
{
	char		**cmd;
	char		*infile; // < infile
	int			type; //1 = > ; 2 = >> (append); 
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
};

void	ft_input(void);
void	ft_cp_env(char **envp);
int		ft_parsing(char *input, t_minishell *mshell);
char	**d_split(char *s, char c);
char	*d_strdup(const char *str);
size_t	d_strlen(const char *str);
void	*d_calloc(size_t count, size_t size);
char	*d_strjoin(char *s1, char *s2);
char	*d_itoa(int n);
int		d_strncmp(const char *a, const char *b, size_t size);
char	*d_substr(char const *s, unsigned int start, size_t len);

#endif