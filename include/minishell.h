/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/17 16:55:54 by blerouss         ###   ########.fr       */
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
	char	*str;
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
	t_env	*env;
	t_exec	exec;
	My_func built_in;
	char	**args;
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

char	**ft_split(char const *str, char c);
char	*path_cmd(char *cmd, char **env);
char	*ft_strdup(char *str);
char	*ft_strndup(char *str, unsigned int n);
t_env	*ft_parse_env(char **env);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);
int	ft_pwd(t_cmd *cmd);
int	ft_exit(t_cmd *cmd);
int	ft_env(t_cmd *cmd);
int	ft_cd(t_cmd *cmd);
int	ft_echo(t_cmd *cmd);
void	parse_cmd(t_parsing *parsing, t_cmd *cmd);
void	ft_parsing(t_cmd *cmd, t_cmd *start);
void	ft_clear_cmd(t_cmd *cmd);
void	ft_init_cmd(t_cmd **cmd, t_cmd **start, char **env);
void	ft_init_cmd_2(t_cmd **cmd, t_cmd **start, t_env *env);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_print_tab(char **tab);
void	ft_free_tab(char **tab);

#endif
