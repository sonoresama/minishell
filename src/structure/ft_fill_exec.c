/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:58:50 by bastien           #+#    #+#             */
/*   Updated: 2023/09/05 18:06:57 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_check_export_2(char **args, t_parsing *p, int i, t_shell *sh)
{
	char	*str;

	if (!args[i + 1])
		return ;
	str = join_three(args[i], " ", args[i + 1]);
	if (!str)
	{
		sh->error = MALLOC_ERROR;
		return ;
	}
	if (!ft_strncmp(str, p->export[i - 1], ft_strlen(p->export[i - 1]) + 1))
	{
		free(args[i]);
		free(args[i + 1]);
		while (args[i + 2])
		{
			args[i + 1] = args[i + 2];
			i++;
		}
		args[i + 1] = NULL;
	}
	else
		free(args[i]);
	free(str);
}

static int	ft_check_export(char **args, t_parsing *pars, t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_strncmp(args[0], "export", 7) || !args[1])
		return (0);
	while (args[++i] && pars->export[i - 1])
	{
		if (ft_strchr(pars->export[i - 1], '$'))
		{
			replace_var_env_in_str(&pars->export[i - 1], shell);
			if (!pars->export[i - 1])
			{
				while (pars->export[i])
					free(pars->export[i++]);
			}
			ft_check_export_2(args, pars, i, shell);
			args[i] = ft_strdup(pars->export[i - 1]);
			if (!args[i])
			{
				while (args[++i])
					free(args[i]);
			}
		}
	}
	return (0);
}

int	ft_fill_exec(char *str, t_shell *shell, t_exec *exec, t_parsing *pars)
{
	int	i;

	i = 0;
	(*exec).args = ft_split_2_separator(str, ' ', '	');
	if (!(*exec).args)
		return (1);
	ft_paste_quote_space((*exec).args, pars, shell);
	if (is_built_in(exec->args[0]))
	{
		exec->cmd_path = ft_strdup(exec->args[0]);
		if (!exec->cmd_path || ft_check_export(exec->args, pars, shell))
			return (1);
	}
	else
	{
		exec->cmd_path = path_cmd((*exec).args[0], shell, -1);
		if (!exec->cmd_path)
			return (1);
		if (!ft_strchr(exec->cmd_path, '/'))
		{
			while (exec->cmd_path && exec->cmd_path[i])
				exec->cmd_path[i++] = '}';
		}
	}
	return (0);
}
