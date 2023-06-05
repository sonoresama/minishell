/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/06/05 11:54:36 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	split_in_cmd(char **str_piped, t_shell *shell, t_parsing *parsing)
{
	int			i;
	t_cmd		*tmp;

	i = 0;
	i = 0;
	if (shell->error)
		return ;
	shell->cmd = ft_fill_cmd(str_piped[i++], shell, parsing);
	tmp = shell->cmd;
	if (tmp->infile == -2)
		tmp->infile = 0;
	while (str_piped[i])
	{
		tmp->next = ft_fill_cmd(str_piped[i], shell, parsing);
		if (!str_piped[i + 1] && tmp->outfile == -2)
			tmp->outfile = 1;
		tmp = tmp->next;
		i++;
	}
	ft_free_tab(str_piped);
}

int	ft_parsing(t_shell *shell, char *str)
{
	t_parsing	parsing;

	if (!str || !str[0])
	{	
		free(str);
		return (-1);
	}
	add_history(str);
	parsing.quote = NULL;
	ft_cut_quote_space(str, &parsing, shell);
	split_in_cmd(ft_split(str, '|'), shell, &parsing);
	free(str);
	return (0);
}
