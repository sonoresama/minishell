/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:09:26 by eorer             #+#    #+#             */
/*   Updated: 2023/05/06 17:48:03 by emileorer        ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_mini{
	char	*cmd;
	char	option;
	char	**args;
}	t_mini;

void	ft_putchar(char c);
char	*ft_pwd(void);
void	ft_exit(void);
void	ft_env(char **env);
void	free_tab(char **tableau);

char	**ft_split(const char *s, char c);

#endif
