/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 16:58:31 by bastien          ###   ########.fr       */
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

typedef struct s_mini t_mini;
typedef	int (*My_func)(t_mini *mini);

//structure de travail

typedef struct	s_parsing
{
	char	*str;
	char	**str_piped;
	char	**cmd_line;
	char	**quote;
	char	**dquote;
	int	utils;
}		t_parsing;


//Structure avec cmd parsed 

struct	s_mini
{
	My_func built_in;
	char	**args;
	char	*redirection;
	char	*infile;
	char	*outfile;
	char	*quote;
	char	*dquote;
	int	heredoc;//(bool)
	int	append;//(bool)
	struct	s_mini	*next;
};

char	**ft_split(char const *str, char c);
char	*path_cmd(char *cmd, char **env);
char	*ft_strdup(char *str);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strlen(char *str);
void	parse_cmd(t_parsing *parsing, t_mini *mini);
void	ft_parsing(t_mini *mini, t_mini *start, char **env);
void	ft_clear_mini(t_mini *mini);
void	ft_init_mini(t_mini **mini, t_mini **start);
void	ft_print_tab(char **tab);
void	ft_free_tab(char **tab);

#endif
