/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 17:23:11 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../include/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd t_cmd;
typedef	int (*My_func)(t_cmd *cmd);

typedef struct	s_exec
{
	char	*cmd_path;
	char	**args;
}	t_exec;

typedef struct	s_parsing
{
	char	**str_piped;
	char	**cmd_line;
	char	**quote;
	char	**dquote;
	int	utils;
}		t_parsing;

typedef struct	s_env
{
	char	*str;
	char	*name;
	char	*value;
	struct s_env	*next;
}		t_env;

struct	s_cmd
{
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
	t_env	*env;
	char	**maxi_env;
	int	last_error;
	t_cmd	*cmd;
}	t_shell;

char	**ft_split(char const *str, char c);
char	*path_cmd(char *cmd_name, t_shell *shell);
char	*ft_strdup(char *str);
char	*ft_strndup(char *str, unsigned int n);
t_env	*ft_init_env(void);
t_env	*ft_fill_env(char **env);
t_shell	*ft_init_shell(void);
t_shell	*ft_fill_shell(char **env);
t_cmd	*ft_init_cmd(void);
t_cmd	*ft_fill_cmd(char *str, t_shell *shell);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);
int	ft_pwd(t_cmd *cmd);
int	ft_exit(t_cmd *cmd);
int	ft_env(t_cmd *cmd);
int	ft_cd(t_cmd *cmd);
int	ft_echo(t_cmd *cmd);
void	parse_cmd(t_parsing *parsing, t_cmd *cmd);
t_shell	*ft_parsing(char **env, char *str);
void	ft_clear_cmd(t_cmd *cmd);
void	ft_clear_env(t_env *env);
void	ft_clear_shell(t_shell *shell);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_print_tab(char **tab);
void	ft_free_tab(char **tab);

#endif
