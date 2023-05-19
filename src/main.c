/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/19 17:25:03 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

My_func	is_built_in(char *str)
{
	if (!ft_strncmp(str, "exit", ft_strlen("exit")))
		return (&ft_exit);
	else if (!ft_strncmp(str, "pwd", ft_strlen("pwd")))
		return (&ft_pwd);
	else if (!ft_strncmp(str, "cd", ft_strlen("cd")))
		return (&ft_cd);
	else if (!ft_strncmp(str, "echo", ft_strlen("echo")))
		return (&ft_echo);
	else if (!ft_strncmp(str, "env", ft_strlen("env")))
		return (&ft_env);
	else if (!ft_strncmp(str, "export", ft_strlen("export")))
		return (&ft_export);
	else if (!ft_strncmp(str, "unset", ft_strlen("unset")))
		return (&ft_unset);
	else
		return (NULL);
}

void	set_cmd(char *str, t_shell *shell, t_cmd *cmd)
{
	char	**split;
	int	i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return ;
	cmd->built_in = is_built_in(split[0]);
	if (cmd->built_in)
		cmd->exec.cmd_path = ft_strdup(split[0]);
	else
		cmd->exec.cmd_path = path_cmd(split[0], shell, cmd);
	cmd->exec.args = split;
	return ;
}

void	check_output(t_shell *shell)
{
	if (WEXITSTATUS(shell->last_error) == FT_EXIT)
		exit(0);
	else if (WEXITSTATUS(shell->last_error) == FT_CD)
		ft_cd(shell);
	else if (WEXITSTATUS(shell->last_error) == FT_EXPORT)
		ft_export(shell);
	return ;
}

void	free_all(char *str, t_cmd *cmd)
{
	free(str);
	free_cmd(cmd);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_shell	shell;
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	ft_bzero(&shell, sizeof(t_shell));
	ft_bzero(&cmd, sizeof(t_cmd));
	shell.env = ft_create_env(env);
	shell.maxi_env = env;
	if (!shell.env)
	{
		perror("MALLOC ");
		return (1);
	}
	while (1)
	{
		str = readline("minishell$ ");
		if (!str || !str[0])
		{
			free(str);
			continue;
		}
		add_history(str);
		set_cmd(str, &shell, &cmd);
		shell.cmd = &cmd;
//		printf("CMD : %s\n", shell.cmd->exec.cmd_path);
//		printf("ARG 1 : %s\n", shell.cmd->exec.args[1]);
		if (!shell.cmd)
			continue ;
		ft_cmd(&shell);
		check_output(&shell);
		free_all(str, shell.cmd);
	}
	return (0);
}
