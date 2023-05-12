/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/12 19:30:48 by blerouss         ###   ########.fr       */
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

typedef struct	s_mini
{
	char	*cmd;
	char	**args;
	char	*redirection;
	char	*infile;
	char	*outfile;
	char	*quote;
	char	*dquote;
	int	heredoc;//(bool)
	int	append;//(bool)
	struct	s_mini	*next;
}		t_mini;

char	**ft_split(char const *str, char c);

#endif
