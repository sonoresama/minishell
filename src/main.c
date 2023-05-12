/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/12 17:59:53 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

typedef	int (*My_func)(t_mini *mini);

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
	else
		return (NULL);
}

void	set_mini(char *str, char **env, t_mini *mini)
{
	char	**split;
	My_func	ft_built;
	int	i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return ;
	ft_built = is_built_in(split[0]);
	if (ft_built)
	{
		mini->built_in = ft_built;
		mini->exec.cmd_path = ft_strdup(split[0]);
		mini->exec.args = split;
	}
	else
	{
		mini->exec.cmd_path = path_cmd(split[0], env, mini);
		mini->exec.args = split;
	}
}

/*int	ft_built_in(t_mini *mini, char **env)
{
	int	error;

	error = 0;
	if (!ft_strncmp(mini->exec.cmd_path, "exit", ft_strlen("exit")))
		error = ft_exit(mini);
	else if (!ft_strncmp(mini->exec.cmd_path, "pwd", ft_strlen("pwd")))
		error = ft_pwd(mini);
	else if (!ft_strncmp(mini->exec.cmd_path, "env", ft_strlen("env")))
		ft_env(env);
	else if (!ft_strncmp(mini->exec.cmd_path, "cd", ft_strlen("cd")))
		error = ft_cd(mini);
	else if (!ft_strncmp(mini->exec.cmd_path, "echo", ft_strlen("echo")))
		error = ft_echo(mini);
	return (error);
}*/

void	exec_cmd(t_mini *mini, char **env)
{
	if (mini->built_in)
	{
		mini->built_in(mini);
		exit(0);
	}
	else
		execve(mini->exec.cmd_path, mini->exec.args, env);
	
}
int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_mini	mini;
	pid_t	pid;

	(void)argc;
	(void)argv;
	ft_bzero(&mini, sizeof(t_mini));
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		set_mini(str, env, &mini);
		printf("CMD Path : %s\n", mini.exec.cmd_path);
		printf("Arg 1 : %s\n", mini.exec.args[0]);
		pid = fork();
		if (pid == (pid_t)-1)
			perror("ERREUR ");
		else if (pid != 0)
			exec_cmd(&mini, env);
		wait(NULL);
		free(str);
//		free_mini(&mini);
	}
	return (0);
}
