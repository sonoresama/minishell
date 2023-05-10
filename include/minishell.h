/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 16:16:29 by eorer            ###   ########.fr       */
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

typedef struct s_mini{
	char	*cmd;
	char	**args;
}	t_mini;

typedef long long int t_long;

char	*ft_pwd(char *cwd);
void	ft_exit(t_mini *mini);
void	ft_env(char **env);
int	ft_cd(const char *path);
void	ft_echo(t_mini *mini);

/* UTILITIES */

void	free_tab(char **tableau);
char	**ft_split(const char *s, char c);
char	*ft_strdup(char *str);
int	ft_strlen(char *str);
int	ft_strncmp(const char *s1, const char *s2, unsigned int n);
t_long	ft_atoi(const char *nptr);

#endif
