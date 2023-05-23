/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:31:31 by bastien           #+#    #+#             */
/*   Updated: 2023/05/23 17:27:02 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_My_func	is_built_in(char *str)
{
	if (!ft_strncmp(str, "exit", 4))
		return (&ft_exit);
	else if (!ft_strncmp(str, "pwd", 3))
		return (&ft_pwd);
	else if (!ft_strncmp(str, "cd", 2))
		return (&ft_cd);
	else if (!ft_strncmp(str, "echo", 4))
		return (&ft_echo);
	else if (!ft_strncmp(str, "env", 3))
		return (&ft_env);
	else if (!ft_strncmp(str, "export", 6))
		return (&ft_export);
//	else if (!ft_strncmp(str, "unset", 5))
//		return (&ft_unset);
	else
		return (NULL);
}

static void	ft_split_pipeline_in_cmd(char **str_piped, t_shell *shell, t_parsing * parsing)
{
	int		i;
	t_cmd		*tmp;

	i = 0;
	ft_paste_quote_space(str_piped, parsing, shell);
	shell->cmd = ft_fill_cmd(str_piped[i++], shell);
	tmp = shell->cmd;
	while (str_piped[i])
	{
		if (str_piped[i])
			tmp->next = ft_fill_cmd(str_piped[i], shell);
		tmp = tmp->next;
		i++;
	}
	ft_free_tab(str_piped);
}

t_shell	*ft_parsing(char **env, char *str)
{
	t_parsing	parsing;
	t_shell		*shell;

	if (!str || !str[0])
	{
		if (!str[0])
			free(str);
		return (NULL);
	}
	add_history(str);
	shell = ft_fill_shell(env);
	if (!shell)
		return (NULL);
	if (!strcmp(str, "exit"))
	{
		rl_clear_history();
		free(str);
		ft_clear_shell(shell);
		exit(0);
	}
	//gestion heredoc
	parsing.quote = NULL;
	ft_cut_quote_space(str, &parsing, shell);
	ft_split_pipeline_in_cmd(ft_split(str, '|'), shell, &parsing);
	free(str);
	return (shell);
}
