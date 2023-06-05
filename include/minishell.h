/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/06/05 11:56:13 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdarg.h>
# include <dirent.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>

/* EXIT MACROS */

# define FT_EXIT 10
# define FT_CD 11
# define FT_ENV 12
# define FT_PWD 13
# define FT_EXPORT 14
# define FT_UNSET 15
# define QUOTE_UNCLOSED 16
# define MALLOC_ERROR 17

/* STRUCTURES */

typedef struct s_shell t_shell;
typedef long long int t_long;
typedef	int (*t_My_func)(t_shell *shell);

typedef struct	s_exec
{
	char	*cmd_path;
	char	**args;
}	t_exec;

typedef struct	s_cmd
{
	t_exec	exec;
	t_My_func	built_in;
	int	infile;
	int	outfile;
	char	**heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_env
{
	char	*str;
	char	*name;
	char	*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_shell
{
	t_env	*env;
	t_cmd	*cmd;
	char	*str;
	char	**maxi_env;
	int	last_error;
	int	error;
	int	fd_stdin;
	int	fd_stdout;
	int	pipein;
	int	pipeout;
}	t_shell;

typedef struct s_quote
{
	char			*str;
	struct s_quote	*next;
}		t_quote;

typedef struct s_parsing
{
	t_quote	*quote;
	char	**dquote;
}		t_parsing;

/* BUILT_IN */

int	ft_pwd(t_shell *shell);
int	ft_exit(t_shell *shell);
int	ft_env(t_shell *shell);
int	ft_cd(t_shell *shell);
int	ft_echo(t_shell *shell);
int	ft_export(t_shell *shell);
int	ft_unset(t_shell *shell);

/* FUNCTIONS */

t_My_func	is_built_in(char *str);
t_env	*ft_create_env(char **env);
t_env	*ft_create_var_env(char *str);
char	*path_cmd(char *cmd_name, t_shell *shell);
void	ft_cmd(t_shell *shell);
int	search_equal(char *str);
int	update_env(t_shell *shell);

/* UTILITIES */

char	*ft_strndup(char *str, unsigned int n);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *str);
int	ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
t_long	ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
void	lst_add_end(t_env **lst, t_env *new);
char	*ft_strjoin(char *s1, char *s2);
char	*join_three(char *s1, char *s2, char *s3);
void	free_all(t_shell *shell);
void	free_cmd(t_cmd *cmd);
void	free_tab(char **tableau);

/* BOSS */

//init_struct.c
t_env		*ft_init_lst(void);
t_env		*ft_init_env(void);
t_shell		*ft_init_shell(void);
t_cmd		*ft_init_cmd(void);

//fill_strut.c
t_env		*ft_fill_env(char **env, int i);
t_shell		*ft_fill_shell(char **env);
t_cmd		*ft_fill_cmd(char *str, t_shell *shell, t_parsing *parsing);

//clear_struct.c
void		ft_clear_cmd(t_cmd *cmd);
void		ft_clear_env(t_env *env);
void		ft_clear_shell(t_shell *shell);
void		ft_clear_quote(t_quote **quote);

//heredoc_redir.c
void		ft_fill_redir_heredoc(char *str, t_cmd *cmd);

//utils.c
void		ft_print_tab(char **tab);
void		ft_free_tab(char **tab);

//utils2.c
void		*ft_memset(void *s, int c, size_t n);

//utils3.c
char		*ft_strcut(char *str, int start, int end);
int			ft_count_heredoc(char *str);
int			double_chrcmp(char *str, char c, char d);
char		*get_env_value(char *var, t_shell *shell);

//parsing.c
int		ft_parsing(t_shell *shell, char *str);

//cut_quote.c
void		ft_cut_quote_space(char *str, t_parsing *parsing, t_shell *shell);
void		ft_paste_quote_space(char **str_piped, t_parsing *parsing,
				t_shell *shell);

#endif
