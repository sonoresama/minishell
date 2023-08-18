/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:49:59 by eorer             #+#    #+#             */
/*   Updated: 2023/08/18 15:46:21 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*static int	bis_ft_strchr(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (1);
	else
		return (0);
}

static char	**ft_copy_tab(char **tab, t_shell *shell)
{
	int		i;
	char	**new_tab;

	i = 0;
	while (tab[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 1));
	if (!new_tab)
	{
		shell->error = MALLOC_ERROR;
		return (NULL);
	}
	i = 0;
	while (tab[i])
	{
		new_tab[i] = ft_strdup(tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

static void	ft_change_var(t_shell *shell, int i)
{
	shell->cmd->built_in = NULL;
	free(shell->cmd->exec.cmd_path);
	if (is_built_in(shell->cmd->exec.args[i]))
	{
		shell->cmd->exec.cmd_path = ft_strdup(shell->cmd->exec.args[i]);
		shell->cmd->built_in = is_built_in(shell->cmd->exec.cmd_path);
	}
	else
		shell->cmd->exec.cmd_path = path_cmd(shell->cmd->exec.args[i],
				shell, -1);
}*/

void	ft_env(t_shell *shell)
{
	t_env		*lst;
	int			i;
	char		**tmp;
	struct stat	buf;

	tmp = NULL;
	i = 1;
	ft_bzero(&buf, sizeof(struct stat));
	while (shell->cmd->exec.args[i])
	{
		if (ft_strncmp(shell->cmd->exec.args[i], "env", 4) != 0)
		{
			write(2, "env : bad argument\n", 19);
			shell->last_error = 127;
			return ;
		}
		i++;
	}
	lst = shell->env;
	while (lst)
	{
		printf("%s\n", lst->str);
		lst = lst->next;
	}
	shell->last_error = 0;
}
