/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:24:12 by dso               #+#    #+#             */
/*   Updated: 2022/02/02 17:43:49 by dso              ###   ########.fr       */
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
void	d_free_tab(char **tab);
void	d_init_struct(t_minishell *mshell);
t_cmds	*d_init_cmds(void);
void	*d_add_cmds(t_minishell *mshell, t_cmds *cmd);
int		d_count_tab(char **tmp);
int		d_check_quotes(char *input, t_minishell *mshell);
int		d_check_end(char *input);
int		d_count_cmds(char **args);
void	d_put_cmds(char **args, t_cmds *cmd, t_var *vars);
char	*d_create_heredoc(int i);
void	d_start_heredoc(char *hd_stop, char *heredoc);
char	*d_check_vars(char *tmp, t_var *vars);
int		d_put_args(char **args, t_cmds *cmd, t_var *vars, char *heredoc);

#endif