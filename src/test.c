/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/10 17:47:15 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_mini(char *str, t_mini *mini)
{
	char	**split;
	int	i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return ;
	mini->cmd = ft_strdup(split[0]);
	mini->args = split + 1;
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	*cwd;
	t_mini	mini;

	(void)argc;
	(void)argv;
	cwd = NULL;
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		set_mini(str, &mini);
		if (!strcmp(mini.cmd, "exit"))
			ft_exit(&mini);
		else if (!strcmp(mini.cmd, "pwd"))
			cwd = ft_pwd(cwd);
		else if (!strcmp(mini.cmd, "env"))
			ft_env(env);
		else if (!strcmp(mini.cmd, "cd"))
			ft_cd(mini.args[0]);
		else if (!strcmp(mini.cmd, "echo"))
			ft_echo(&mini);
		free(str);
	}
	return (0);
}
