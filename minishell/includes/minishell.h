/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:24:12 by dso               #+#    #+#             */
/*   Updated: 2022/02/05 18:03:45 by dso              ###   ########.fr       */
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
# include <termios.h>

char						**g_mini_env;

typedef struct s_cmds		t_cmds;
typedef struct s_minishell	t_minishell;
typedef struct s_var		t_var;

struct s_cmds
{
	char		**cmd;
	char		*infile; // < infile
	int			type; //1 = > ; 2 = >> (append); 
	int			heredoc;
	char		*outfile; // > outfile (open)
	t_cmds		*next;
	int			pipe[2]; // ajout du pipe de la cmd ( pipe = 0 si sep = ;) 
	pid_t		pid_child;
};

struct s_minishell
{
	t_cmds		*cmds;
	int			nb_sq;
	int			nb_dq;
	int			nb_pipe;
	int			error;
};

// parsing
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
void	d_put_cmds(char **args, t_cmds *cmd, t_minishell *mshell);
char	*d_create_heredoc(int i);
void	d_start_heredoc(char *hd_stop, char *heredoc);
char	*d_check_vars(char *tmp, t_minishell *mshell);
int		d_put_args(char **args, t_cmds *cmd, char *heredoc, t_minishell *mshell);

// exec
void	k_loop_forks(t_minishell *minishell);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *str, int chr);
char	*ft_strjoin(char const *s1, char const *s2);

// builtin
void	ft_pwd(char **cmds);
void	ft_exit(t_minishell *mshell, char **cmds);
void	ft_env(char **cmds);
void	ft_echo(char **cmds);
void	ft_export(char **cmds);
void	ft_cd(char **cmds);
void	ft_unset(char **cmds);
void	k_error(char *str1, char *str2, char **env);

//signals
void	ft_block_signal(int keycode);
void	ft_signal(int keycode, void (*f)(int, siginfo_t *, void *));
void	ft_handle_signal(int keycode, siginfo_t *s, void *tmp);
int		ft_terminal(void);
void	ft_set_terminal(struct termios *terminal);

#endif