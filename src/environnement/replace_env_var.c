/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:48:02 by blerouss          #+#    #+#             */
/*   Updated: 2023/08/30 13:49:14 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_env_value(char *var, t_shell *shell)
{
	t_env	*lst;

	if (var[0] == '\0')
		return (NULL);
	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(var, lst->name, ft_strlen(var) + 1))
			return (lst->value);
		lst = lst->next;
	}
	return (NULL);
}

static char	*dup_next_word(char *str, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
		i++;
	tmp = strndup(str, i);
	if (!tmp)
	{
		shell->error = MALLOC_ERROR;
		return (NULL);
	}
	return (tmp);
}

static int	prec_word_is_heredoc(char *str, int i)
{
	while (i > 0 && str[i] != '>' && str[i] != '<' && str[i] != ' '
		&& str[i] != '	' && str[i] != '|')
		i--;
	while (i > 0 && (str[i] == ' ' || str[i] == '	'))
		i--;
	if (str[i] == '<' || str[i] == '>' || (str[i] == '<'
			&& str[i - 1] == '<') || (str[i] == '>' && str[i - 1] == '>'))
		return (1);
	return (0);
}

static void	replace_var_env_in_str_bis(char **str, int *i, t_shell *shell)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	if (prec_word_is_heredoc((*str), (*i)))
	{
		(*i)++;
		return ;
	}
	(*str)[(*i)] = '\0';
	tmp3 = dup_next_word(&(*str)[(*i) + 1], shell);
	if (!tmp3)
	{
		free((*str));
		return ;
	}
	tmp = get_env_value(tmp3, shell);
	tmp2 = join_three((*str), tmp, &(*str)[(*i) + ft_strlen(tmp3) + 1]);
	if (tmp)
		(*i) += ft_strlen(tmp);
	if (!tmp2)
		shell->error = MALLOC_ERROR;
	free((*str));
	(*str) = tmp2;
	free(tmp3);
}

int	replace_var_env_in_str(char **str, t_shell *shell)
{
	int		i;

	i = 0;
	while (str && (*str) && (*str)[i])
	{
		while ((*str)[i] && (*str)[i] != '$')
			i++;
		if (((*str)[i] && !(*str)[i + 1]) || ((*str)[i]
			&& !((((*str)[i + 1] >= 'a' && (*str)[i + 1] <= 'z')
			|| ((*str)[i + 1] >= 'A' && (*str)[i + 1] <= 'Z')
			|| ((*str)[i + 1] >= '0' && (*str)[i + 1] <= '9')
			|| (*str)[i + 1] == '_') || (*str)[i + 1] == '\''
			|| (*str)[i + 1] == '\"' || (*str)[i + 1] == '?')))
		{
			i++;
			continue ;
		}
		if ((*str)[i] && (*str)[i + 1] && (*str)[i + 1] == '?')
			ft_join_with_last_error(str, i++, shell);
		else if ((*str)[i] && (*str)[i + 1])
			replace_var_env_in_str_bis(str, &i, shell);
		if (shell->error == MALLOC_ERROR)
			return (1);
	}
	return (0);
}
