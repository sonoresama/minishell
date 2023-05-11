/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/11 17:50:33 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct	s_cmd
{
	char	*str;
}		t_cmd;

//structure de travail

typedef struct	s_parsing
{
	char	*str;
	char	**str_piped;
	char	**quote;
	char	**dquote;
	int	utils;
}		t_parsing;


//Structure avec cmd parsed 

typedef struct	s_mini
{
	char	*cmd;
	struct t_cmd	*exec;
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
