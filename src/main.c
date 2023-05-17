/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/17 16:37:43 by eorer            ###   ########.fr       */
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
	else
		return (NULL);
}

t_cmd	*set_cmd(char *str, char **env, t_cmd *cmd)
{
	char	**split;
	int	i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return (NULL);
	cmd->built_in = is_built_in(split[0]);
	if (cmd->built_in)
		cmd->exec.cmd_path = ft_strdup(split[0]);
	else
		cmd->exec.cmd_path = path_cmd(split[0], env, cmd);
	cmd->exec.args = split;
	return (cmd);
}

void	check_output(t_shell *shell)
{
	if (WEXITSTATUS(shell->last_error) == FT_EXIT)
		exit(0);
	else if (WEXITSTATUS(shell->last_error) == FT_CD)
		ft_cd(shell->cmd);
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
	shell.env = env;
	while (1)
	{
		str = readline("minishell$ ");
		if (!str || !str[0])
		{
			free(str);
			continue;
		}
		add_history(str);
		set_cmd(str, shell.env, &cmd);
		shell.cmd = &cmd;
		if (!shell.cmd)
			continue ;
		printf("CMD : %s\n", shell.cmd->exec.cmd_path);
		printf("Arg 1 : %s\n", shell.cmd->exec.args[1]);
		ft_cmd(&shell);
		check_output(&shell);
		free_all(str, shell.cmd);
	}
	return (0);
}
