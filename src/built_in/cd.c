/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:00:30 by eorer             #+#    #+#             */
/*   Updated: 2023/08/10 17:53:15 by bastien          ###   ########.fr       */
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
	write(2, "cd: HOME n'est pas paramétré\n", 31);
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

static int	ft_fill_arg_cd(t_shell *shell, char **arg, struct stat st)
{
	char	*pwd;
	t_env	*lst;

	lst = shell->env;
	if (!shell->cmd->exec.args[1])
		(*arg) = get_home(shell);
	else
		(*arg) = shell->cmd->exec.args[1];
	if ((*arg) && !(*arg)[0])
		return (1);
	while (lst)
	{
		if (!strncmp(lst->name, "PWD", 4))
			pwd = lst->value;
		lst = lst->next;
	}
	if ((*arg) && (*arg)[0] && (*arg)[0] != '/' && pwd && stat(pwd, &st))
	{
		write(2, "chdir : erreur de détermination du répertoire actuel : ", 57);
		write(2, "getcwd : ne peut accéder aux répertoires parents : Aucun", 58);
		write(2, " fichier ou dossier de ce type\n", 31);
		shell->last_error = 1;
		return (1);
	}
	return (0);
}

void	ft_cd(t_shell *shell)
{
	char		*arg;
	char		*tmp;
	struct stat	st;

	shell->last_error = 0;
	ft_bzero(&st, sizeof(struct stat));
	if (shell->cmd->exec.args[1] && shell->cmd->exec.args[2])
	{
		write(2, "cd: trop d'arguments\n", 21);
		shell->last_error = 1;
		return ;
	}
	if (ft_fill_arg_cd(shell, &arg, st))
		return ;
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
