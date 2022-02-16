/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dso <dso@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:24:12 by dso               #+#    #+#             */
/*   Updated: 2022/02/16 14:49:37 by dso              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define BUFFER_SIZE 1

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

typedef struct s_cmds		t_cmds;
typedef struct s_minishell	t_minishell;
typedef struct s_var		t_var;
typedef struct s_parsing	t_parsing;

char	**g_error;

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

struct s_parsing
{
	int		i;
	int		j;
	int		k;
	int		l;
	int		sign;
	int		in;
	int		out;
	int		end;
	int		start;
	char	*tmp;
};

struct s_minishell
{
	t_cmds		*cmds;
	int			nb_sq;
	int			nb_dq;
	int			nb_pipe;
	char		**g_mini_env;
	char		*pwd;
	int			open_pipe;
};

// parsing
void	ft_input(char **envp, t_minishell *mshell);
void	ft_cp_env(char **envp, t_minishell *mshell);
int		ft_parsing(char *input, t_minishell *mshell);
char	**d_split(char *s, char c);
void	freemalloc(char **strs);
int		d_loop_countwords(char const *str, char c, int i);
int		d_loop_malloctab(int i, char const *str);
int		d_loop_filltab(t_parsing *p, char const *str, char **strs);
int		d_skip_filltab(t_parsing *p, char const *str);
char	*d_strdup(const char *str);
size_t	d_strlen(const char *str);
void	*d_calloc(size_t count, size_t size);
char	*d_strjoin(char *s1, char *s2);
char	*d_itoa(int n);
int		d_atoi(const char *str);
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
int		d_count_cmds(char **args);
int		d_put_cmds(char **args, t_cmds *cmd, t_minishell *mshell);
char	*d_trim_cmd(char *to_trim);
char	*d_create_heredoc(int i);
int		d_start_heredoc(char *hd_stop, char *heredoc, t_minishell *mshell);
int		d_check_hd_quotes(char *hd_stop, char c);
char	*d_trim_hdstop(char *hd_stop);
int		d_fork_error_heredoc(char *stop);
char	*d_check_vars(char *tmp, t_minishell *mshell);
char	*d_check_path(char *variable, char *env);
char	*d_var_err(void);
char	*d_loop_vars3(char *tmp, int i, t_minishell *mshell, char *str);
int		d_skip_vars3(char *tmp, int i);
int		d_put_args(char **args, t_cmds *cmd, char *heredoc, t_minishell *mshell);
void	d_putstr_fd(char *s, int fd);
void	d_putchar_fd(char c, int fd);
void	d_check_countwords(char c, int *i);
char	*d_strchr(const char *str, int c);
char	*get_next_line(int fd);
char	*d_strchr2(const char *str, int c);
char	*d_strjoin2(char *s1, char *s2);

// exec
void	k_loop_forks(t_minishell *minishell);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *str, int chr);
char	*ft_strjoin(char const *s1, char const *s2);

// builtin
void	ft_pwd(char **cmds, t_minishell *mshell);
void	ft_exit(t_minishell *mshell, char **cmds);
void	ft_env(char **cmds, t_minishell *mshell);
void	ft_echo(char **cmds);
void	ft_export(char **cmds, t_minishell *mshell);
void	ft_cd(char **cmds, t_minishell *mshell);
void	ft_unset(char **cmds, t_minishell *mshell);
void	k_error(char *str1, char *str2);

//signals
void	ft_terminal(int	echo);
void	sigint_handler(int keycode);
void	sigint_handler_child(int keycode);
void	sigint_handler_spec(int keycode);
void	sigint_handler_minishell(int keycode);
void	sigint_handler_hd(int keycode);

#endif

// CD TO FIX (Lien symbolique, .., leaks, unset PWD)