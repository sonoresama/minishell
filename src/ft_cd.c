/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:00:30 by eorer             #+#    #+#             */
/*   Updated: 2023/07/31 18:37:14 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_home(t_shell *shell)
{
	t_env	*lst;

	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(lst->name, "HOME", 5))
			return (lst->value);
		lst = lst->next;
	}
	printf("cd: HOME n'est pas paramétré\n");
	shell->last_error = 1;
	return (NULL);
}

static void	ft_change_bis(t_shell *shell, t_env *lst, char *tmp, char *pwd)
{
	if (!lst)
		free(pwd);
	lst = shell->env;
	while (lst)
	{
		if (!ft_strncmp(lst->name, "OLDPWD", 7))
		{
			free(lst->value);
			lst->value = tmp;
			break ;
		}
		lst = lst->next;
	}
	if (!lst)
		free(tmp);
}

static void	ft_change_env_value(t_shell *shell)
{
	t_env	*lst;
	char	*tmp;
	char	*pwd;

	tmp = NULL;
	lst = shell->env;
	pwd = malloc(PATH_MAX);
	if (!pwd)
	{
		shell->error = MALLOC_ERROR;
		return ;
	}
	getcwd(pwd, PATH_MAX);
	while (lst)
	{
		if (!ft_strncmp(lst->name, "PWD", 4))
		{
			tmp = lst->value;
			lst->value = pwd;
			break ;
		}
		lst = lst->next;
	}
	ft_change_bis(shell, lst, tmp, pwd);
}

char	*ft_fill_arg_cd(t_shell *shell)
{
	char	*arg;

	if (!shell->cmd->exec.args[1])
		arg = get_home(shell);
	else
		arg = shell->cmd->exec.args[1];
	return (arg);
}

void	ft_cd(t_shell *shell)
{
	char	*arg;
	char	*tmp;
	struct stat st;

	shell->last_error = 0;
	if (shell->cmd->exec.args[1] && shell->cmd->exec.args[2])
	{
		printf("cd: trop d'arguments\n");
		shell->last_error = 1;
		return ;
	}
	arg = ft_fill_arg_cd(shell);
	if (arg && !arg[0])
		return ;
	if (stat(".", &st))
	{
		printf("chdir : erreur de détermination du répertoire actuel : getcwd : ne peut accéder aux répertoires parents : Aucun fichier ou dossier de ce type\n");
		shell->last_error = 1;
		return ;
	}
	printf("%s\n", arg);
	if (arg && chdir(arg) != 0)
	{
		tmp = ft_strjoin("cd: ", arg);
		perror(tmp);
		free(tmp);
		shell->last_error = 1;
		return ;
	}
	if (arg)
		ft_change_env_value(shell);
	update_env(shell);
}
