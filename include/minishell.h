/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 17:42:42 by blerouss         ###   ########.fr       */
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

typedef struct	s_mini
{
	char	*cmd;
	struct t_cmd	*exec;
	char	*redirection;
	char	*infile;
	char	*outfile;
	int	heredoc;//(bool)
	int	append;//(bool)
	struct	s_mini	*next;
}		t_mini;

char	**ft_split(char const *str, char c);

#endif
