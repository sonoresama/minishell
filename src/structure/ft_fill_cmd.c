/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:53:45 by bastien           #+#    #+#             */
/*   Updated: 2023/09/07 16:25:47 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_count_heredoc(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str && str[i])
	{
		if ((i == 0 || str[i - 1] == ' ')
			&& str[i] == '<' && str[i + 1] == str[i]
			&& str[i + 2 == ' '])
			count++;
		i++;
	}
	return (count);
}

static int	ft_eof(char *str, t_cmd *cmd, t_shell *shell, t_parsing *parsing)
{
	int		i;

	i = 0;
	i = ft_count_heredoc(str);
	if (i > 0)
	{
		cmd->heredoc = malloc(sizeof(char *) * (i + 1));
		if (!cmd->heredoc)
		{
			shell->error = MALLOC_ERROR;
			ft_clear_cmd(cmd);
			return (1);
		}
		while (i > -1)
			cmd->heredoc[i--] = NULL;
	}
	if (ft_fill_red_he(str, cmd, shell, parsing))
	{
		ft_clear_cmd(cmd);
		return (1);
	}
	return (0);
}

t_cmd	*ft_fill_cmd(char *str, t_shell *shell, t_parsing *parsing)
{
	t_cmd	*cmd;

	cmd = ft_init_cmd();
	if (!cmd)
	{
		shell->error = MALLOC_ERROR;
		return (NULL);
	}
	cmd->heredoc = NULL;
	cmd->infile = -2;
	cmd->outfile = -2;
	if (ft_eof(str, cmd, shell, parsing))
		return (NULL);
	if (cmd->infile == -1 || cmd->outfile == -1)
		shell->last_error = 1;
	else if (cmd->infile == -3)
	{
		cmd->infile = ft_heredoc(cmd->heredoc, shell);
		if (cmd->infile == -1)
		{
			shell->error = 10;
			ft_clear_cmd(cmd);
			return (NULL);
		}
	}
	if (ft_fill_exec(str, shell, &cmd->exec, parsing))
	{
		shell->error = MALLOC_ERROR;
		ft_clear_cmd(cmd);
		return (NULL);
	}
	cmd->built_in = is_built_in(cmd->exec.cmd_path);
	return (cmd);
}
