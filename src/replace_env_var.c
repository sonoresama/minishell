/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:48:02 by blerouss          #+#    #+#             */
/*   Updated: 2023/06/30 15:36:36 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_env_value(char *var, t_shell *shell)
{
	t_env	*lst;
	
	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(var, lst->name, ft_strlen(var)))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

static char	*dup_next_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
		i++;
	return (strndup(str, i));
}

static void	replace_var_env_in_str_bis(char **str, int *i, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	(*str)[(*i)] = '\0';
	tmp3 = dup_next_word(&(*str)[(*i) + 1]);
	tmp = get_env_value(tmp3, shell);
	if (tmp)
		tmp2 = join_three((*str), tmp, &(*str)[(*i) + ft_strlen(tmp3) + 1]);
	else
		tmp2 = ft_strjoin((*str), &(*str)[(*i) + ft_strlen(tmp3) + 1]);
	free((*str));
	(*str) = tmp2;
	(*i) += ft_strlen(tmp3);
	free(tmp3);
}

void	replace_var_env_in_str(char **str, t_shell *shell)
{
	int	i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (str && (*str) && (*str)[i])
	{
		while ((*str)[i] && (*str)[i] != '$')
			i++;
		if (!(*str)[i] || !(*str)[i + 1])
			return;
		if ((*str)[i] && (*str)[i + 1] && (*str)[i + 1] == '?')
		{
			(*str)[i] = '\0';
			tmp = ft_itoa(shell->last_error);
			tmp2 = join_three((*str), tmp, &(*str)[i + 2]);
			free((*str));
			free(tmp);
			(*str) = tmp2;
			i++;
		}
		else if ((*str)[i] && (*str)[i + 1])
			replace_var_env_in_str_bis(str, &i, shell);
	}
}

void	replace_var_env_in_lst(t_parsing *parsing, t_shell *shell)
{
	t_quote	*tmp;

	tmp = NULL;
	if (parsing && parsing->dquote)
		tmp = parsing->dquote;
	while (tmp)
	{
		replace_var_env_in_str(&tmp->str, shell);
		tmp = tmp->next;
	}
}
