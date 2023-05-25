/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/24 17:05:58 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <dirent.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

/* EXIT MACROS */

# define FT_EXIT 10
# define FT_CD 11
# define FT_ENV 12
# define FT_PWD 13
# define FT_EXPORT 14
# define FT_UNSET 15

/* STRUCTURES */

typedef struct s_shell t_shell;
typedef long long int t_long;
typedef	int (*My_func)(t_shell *shell);

typedef struct	s_exec
{
	char	*cmd_path;
	char	**args;
}	t_exec;

typedef struct	s_cmd
{
	t_exec	exec;
	My_func	built_in;
	char	*infile;
	char	*outfile;
	int	heredoc;
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
	int	pipe_nb;
	int	pipe_a[2];
	int	pipe_b[2];
}	t_shell;


/* BUILT_IN */

int	ft_pwd(t_shell *shell);
int	ft_exit(t_shell *shell);
int	ft_env(t_shell *shell);
int	ft_cd(t_shell *shell);
int	ft_echo(t_shell *shell);
int	ft_export(t_shell *shell);
int	ft_unset(t_shell *shell);

/* FUNCTIONS */

char	*path_cmd(char *cmd_name, t_shell *shell, t_cmd *cmd);
t_env	*ft_create_env(char **env);
t_env	*ft_create_var_env(char *str);
void	ft_cmd(t_shell *shell);
int	search_equal(char *str);
My_func	is_built_in(char *str);
//int	setEnvironmentVariable(char *str, char **environ);
int	update_env(t_shell *shell);

/* UTILITIES */

char	*ft_strndup(char *str, int n);
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

#endif
