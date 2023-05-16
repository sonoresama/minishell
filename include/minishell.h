/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 17:35:40 by eorer            ###   ########.fr       */
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

/* EXI MACROS */

# define FT_EXIT 10
# define FT_CD 11
# define FT_ENV 12
# define FT_PWD 13

/* STRUCTURES */

typedef struct s_cmd t_cmd;
typedef long long int t_long;
typedef	int (*My_func)(t_cmd *cmd);

typedef struct	s_exec
{
	char	*cmd_path;
	char	**args;
}	t_exec;

struct	s_cmd
{
	char	**env;
	t_exec	exec;
	My_func built_in;
	char	*redirection;
	char	*infile;
	char	*outfile;
	char	*quote;
	char	*dquote;
	int	heredoc;//(bool)
	int	append;//(bool)
	struct	s_cmd	*next;
};

typedef struct	s_shell
{
	char	**env;
	int	last_error;
	t_cmd	*cmd;
	
}	t_shell;


/* BUILT_IN */

int	ft_pwd(t_cmd *cmd);
int	ft_exit(t_cmd *cmd);
int	ft_env(t_cmd *cmd);
int	ft_cd(t_cmd *cmd);
int	ft_echo(t_cmd *cmd);

/* FUNCTIONS */

char	*path_cmd(char *cmd_name, char **env, t_cmd *cmd);
void	ft_cmd(t_cmd *cmd);

/* UTILITIES */

void	free_tab(char **tableau);
void	free_cmd(t_cmd *cmd);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *str);
int	ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
t_long	ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char *s1, char *s2);

#endif
