/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishel.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmammeri <kmammeri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:41:13 by kmammeri          #+#    #+#             */
/*   Updated: 2022/01/31 17:16:39 by kmammeri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHEL_H
# define MINISHEL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

char						**g_mini_env;

typedef struct s_cmds		t_cmds;
typedef struct s_minishell	t_minishell;
typedef struct s_var		t_var;

struct s_cmds
{
	char		**cmd;
	char		*infile; // <
	char		*outfile; // >
	int			type; // > = 1 ; >> = 2
	int			pipe[2]; // ajout du pipe de la cmd ( pipe = 0 si sep = ;) 
	pid_t		pid_child; // ajout 
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
	int			nb_cmds;
	int			nb_sq;
	int			nb_dq;// +escape backslash
	int			nb_pipe;
	int			heredoc; // << + function write outfile + unlink
};

void	ft_input(void);
void	ft_cp_env(char **envp);
int		ft_parsing(char *input, t_minishell *mshell);
char	**d_split(char *s, char c);
char	*d_strdup(const char *str);
void	k_loop_forks(t_minishell *minishell);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *str, int chr);
char	*ft_strjoin(char const *s1, char const *s2);

#endif