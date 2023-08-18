/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:58:50 by bastien           #+#    #+#             */
/*   Updated: 2023/08/18 11:58:52 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fill_exec(char *str, t_shell *shell, t_exec *exec, t_parsing *pars)
{
	int	i;

	i = 0;
	(*exec).cmd_path = NULL;
	(*exec).args = ft_split_2_separator(str, ' ', '	');
	if (!(*exec).args)
		return (1);
	ft_paste_quote_space((*exec).args, pars, shell);
	if (is_built_in(exec->args[0]))
		exec->cmd_path = ft_strdup(exec->args[0]);
	else
	{
		exec->cmd_path = path_cmd((*exec).args[0], shell, -1);
		if (!ft_strchr(exec->cmd_path, '/'))
		{
			while (exec->cmd_path && exec->cmd_path[i])
				exec->cmd_path[i++] = '}';
		}
	}
	return (0);
}
