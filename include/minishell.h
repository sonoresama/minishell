/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/12 17:56:33 by eorer            ###   ########.fr       */
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

typedef struct s_mini t_mini;
typedef long long int t_long;
typedef	int (*My_func)(t_mini *mini);

typedef struct	s_cmd
{
	char	*cmd_path;
	char	**args;
}	t_cmd;

struct	s_mini
{
	t_cmd	exec;
	My_func built_in;
	char	*redirection;
	char	*infile;
	char	*outfile;
	char	*quote;
	char	*dquote;
	int	heredoc;//(bool)
	int	append;//(bool)
	struct	s_mini	*next;
};

/* BUILT_IN */

int	ft_pwd(t_mini *mini);
int	ft_exit(t_mini *mini);
void	ft_env(char **env);
int	ft_cd(t_mini *mini);
int	ft_echo(t_mini *mini);

/* FUNCTIONS */

char	*path_cmd(char *cmd, char **env, t_mini *mini);

/* UTILITIES */

void	free_tab(char **tableau);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *str);
int	ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
t_long	ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char *s1, char *s2);

#endif
