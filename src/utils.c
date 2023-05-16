/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:08:50 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 17:10:22 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return(i);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_init_mini(t_mini **mini, t_mini **start)
{
	(*mini) = malloc(sizeof(t_mini));
	if ((*mini) == NULL)
	{
		perror("Allocation error : ");
		exit(1);
	}
	if (start)
		(*start) = (*mini);
	(*mini)->args = NULL;
	(*mini)->redirection = NULL;
	(*mini)->infile = NULL;
	(*mini)->outfile = NULL;
	(*mini)->quote = NULL;
	(*mini)->dquote = NULL;
	(*mini)->next = NULL;
	(*mini)->heredoc = 0 ;
	(*mini)->append = 0 ;
}

void	ft_clear_mini(t_mini *mini)
{
	t_mini	*tmp;

	while (mini)
	{
		if (mini->args)
		{
			ft_print_tab(mini->args);
			ft_free_tab(mini->args);
		}
		tmp = mini;
		mini = mini->next;
		free(tmp);
	}
}
