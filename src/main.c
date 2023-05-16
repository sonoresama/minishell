/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/16 17:03:50 by eorer            ###   ########.fr       */
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

void	set_cmd(char *str, char **env, t_cmd *cmd)
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
		cmd->exec.cmd_path = path_cmd(split[0], env, cmd);
	cmd->exec.args = split;
	cmd->env = env;
}

void	check_output(t_cmd *cmd)
{
	if (WEXITSTATUS(cmd->last_error) == FT_EXIT)
		exit(0);
	else if (WEXITSTATUS(cmd->last_error) == FT_CD)
		ft_cd(cmd);
}

void	free_all(char *str, t_cmd *cmd)
{
	free(str);
	free_cmd(cmd);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_cmd	cmd;

	(void)argc;
	(void)argv;
	ft_bzero(&cmd, sizeof(t_cmd));
	while (1)
	{
		str = readline("cmdshell$ ");
		if (!str || !str[0])
		{
			free(str);
			continue;
		}
		add_history(str);
		set_cmd(str, env, &cmd);
		ft_cmd(&cmd);
		check_output(&cmd);
		free_all(str, &cmd);
	}
	return (0);
}
