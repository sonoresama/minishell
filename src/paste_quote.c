/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <blerouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 14:46:05 by blerouss          #+#    #+#             */
/*   Updated: 2023/07/22 14:47:32 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*final_join(int *j, char *str_piped, t_quote **quote, t_shell *sh)
{
	t_quote	*qtmp;
	int		k;
	char	*tmp;

	k = 1;
	tmp = NULL;
	while (str_piped && str_piped[(*j) + k]
		&& str_piped[(*j) + k] != str_piped[(*j)])
		k++;
	if (str_piped[(*j) + k])
	{
		str_piped[(*j)] = '\0';
		tmp = join_three(str_piped, (*quote)->str, &str_piped[(*j) + k + 1]);
		if (!tmp)
			sh->error = MALLOC_ERROR;
		qtmp = (*quote)->next;
		(*j) += ft_strlen((*quote)->str);
		free((*quote)->str);
		free((*quote));
		(*quote) = qtmp;
		free(str_piped);
		return (tmp);
	}
	j++;
	return (str_piped);
}

void	ft_paste_quote_space(char **str, t_parsing *parsing, t_shell *shell)
{
	int	i;
	int	j;

	(void)shell;
	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (str && str[i] && str[i][j])
		{
			while (str[i][j] && str[i][j] != '\'' && str[i][j] != '\"')
				j++;
			if (str[i][j])
			{
				if (str[i][j] == '\'')
					str[i] = final_join(&j, str[i], &parsing->quote, shell);
				else if (str[i][j] == '\"')
					str[i] = final_join(&j, str[i], &parsing->dquote, shell);
				if (str[i] == NULL)
					return ;
			}
		}
		i++;
	}
}
