/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/09/13 10:36:39 by eorer            ###   ########.fr       */
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
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stddef.h>

/* EXIT MACROS */

# define SYNTAX_ERROR 16
# define MALLOC_ERROR 17
# define REDIR_ERROR 18

/* STRUCTURES */

extern int						g_sig_handle;

typedef struct s_shell			t_shell;
typedef long long int			t_long;
typedef void					(*t_My_func)(t_shell *shell);

typedef struct s_exec
{
	char	*cmd_path;
	char	**args;
}	t_exec;

typedef struct s_cmd
{
	t_exec			exec;
	t_My_func		built_in;
	int				infile;
	int				outfile;
	char			**heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*str;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	t_env	*export;
	t_cmd	*cmd;
	char	*str;
	char	**maxi_env;
	int		last_error;
	int		error;
	int		fd_stdin;
	int		fd_stdout;
	int		pipein;
	int		pipeout;
}	t_shell;

typedef struct s_quote
{
	char			*str;
	struct s_quote	*next;
}		t_quote;

typedef struct s_parsing
{
	t_quote	*quote;
	t_quote	*dquote;
	char	**heredoc;
	char	**redir;
	char	**export;
}		t_parsing;

/* MAIN_FUNCTIONS */

void		init_sig_handler(void);
void		unset_sig_handler(void);
void		main_loop(t_shell *shell, char *str, t_parsing *parsing);

/* PARSING */

t_quote		*get_quote(char *str, int n, t_parsing *parsing);
t_quote		*get_dquote(char *str, int n, t_parsing *parsing);
t_parsing	*ft_fill_parsing(char *str, t_parsing *parsing, t_shell *shell);
void		ft_paste_quote_space(char **str_piped, t_parsing *parsing,
				t_shell *shell);
char		*path_cmd(char *cmd_name, t_shell *shell, int i);
int			ft_fill_parsing_export(char *str, t_parsing *parsing);
int			ft_parsing(t_shell *shell, char **str, t_parsing **parsing);
int			ft_cut_quote_space(char *str, t_parsing *parsing, t_shell *shell);
int			check_pipe(char *str, char **tab);

/* HANDLING_ENV */

void		ft_env_export(t_shell *shell, int i, char *old_tmp);
void		ft_join_with_last_error(char **str, int i, t_shell *shell);
int			replace_var_env_in_str(char **str, t_shell *shell);
int			replace_var_env_in_lst(t_parsing *parsing, t_shell *shell);
int			check_export(char *str, t_shell *shell);
int			search_equal(char *str);
int			update_env(t_shell *shell);
t_env		*ft_create_env(char **env);
t_env		*ft_create_var_env(char *str);
t_env		*ft_create_export(char **env);
t_env		*ft_create_var_export(char *str);

/* HANDLING_HEREDOC_REDIR */

void		ft_end_set_hdoc(t_quote *tmpd, t_quote *tmpq,
				char **hdoc, t_shell *sh);
void		ft_end_set_red(t_quote *tmpd, t_quote *tmpq,
				char **redir, t_shell *sh);
int			ft_copy_redir(char *str, t_parsing *parsing, t_shell *shell);
int			ft_fill_red_he(char *str, t_cmd *cmd, t_shell *shell,
				t_parsing *parsing);

/* BUILT_IN */

t_My_func	is_built_in(char *str);
void		ft_pwd(t_shell *shell);
void		ft_exit(t_shell *shell);
void		ft_env(t_shell *shell);
void		ft_cd(t_shell *shell);
int			replace_var_cd(t_env **lst, char *old_pwd,
				char *pwd, t_shell *shell);
void		ft_echo(t_shell *shell);
void		ft_export(t_shell *shell);
void		ft_unset(t_shell *shell);

/* EXECUTION */

void		clear_pipe(t_shell *shell);
void		ft_wait_parent(pid_t pid, t_shell *shell, t_cmd *cmd);
void		exec_cmd(t_shell *shell);
void		exec_cmd_for_child(t_shell *shell);
void		ft_cmd(t_shell *shell);
void		pipe_cmd(t_shell *shell);
int			ft_heredoc(char **heredoc, t_shell *shell, int i, int fd);
int			setup_end_function(int std_in, int fd, char *file);
int			handle_fd_value(int *fd, char *file, int std_in);
int			ctrl_c_heredoc(int std_in, int fd, char *file, t_shell *shell);
int			ctrl_bs_heredoc(int std_in, int fd, char *file, t_shell *shell);
int			unlink_heredoc_files(void);
int			get_input(t_cmd *cmd, int pipe_in, t_shell *shell);
int			get_output(t_cmd *cmd, int pipe_out);

/* INIT_STRUCT */

t_cmd		*ft_init_cmd(void);
t_env		*ft_init_env(void);
t_shell		*ft_init_shell(void);

/* FILL_STRUCT */

t_cmd		*ft_fill_cmd(char *str, t_shell *shell, t_parsing *parsing);
t_env		*ft_fill_env(char **env, int i);
t_shell		*ft_fill_shell(char **env);
int			ft_fill_exec(char *str, t_shell *shell, t_exec *exec,
				t_parsing *pars);
//void	ft_get_shlvl(t_shell *shell);

/* HANDLING_LST_ENV */

void		lst_add_end(t_env **lst, t_env *new);
t_env		*lst_last(t_env *lst);
t_env		*ft_init_lst(void);
int			ft_lstlen(t_env *env);

/* CLEAR_STRUCT */

int			ft_clear_cmd(t_cmd *cmd);
void		ft_clear_env(t_env **env);
void		ft_clear_shell(t_shell *shell);
void		ft_clear_quote(t_quote **quote);
void		ft_clear_parsing(t_parsing *parsing, char *str);

/* UTILITIES */

char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
char		*ft_strndup(char *str, int n);
char		*ft_strjoin(char *s1, char *s2);
char		*join_three(char *s1, char *s2, char *s3);
char		*ft_strdup(char *str);
char		*ft_strcut(char *str, int start, int end);
char		**ft_split(const char *s, char c);
char		**ft_split_2_separator(const char *s, char c, char d);
void		ft_bzero(void *s, size_t n);
void		ft_close(int fd);
void		ft_free_tab(char **tab);
void		*ft_memset(void *s, int c, size_t n);
void		free_tab(char **tableau);
t_long		ft_atoi(const char *nptr);
int			ft_thereisprint(char *str);
int			ft_strlen(char *str);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			search_equal(char *str);
int			double_chrcmp(char *str, char c, char d);

#endif
