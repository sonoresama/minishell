/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:59:01 by eorer             #+#    #+#             */
/*   Updated: 2023/05/06 17:49:35 by emileorer        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//void	set_cmd(char *str, t_mini *mini)
//{
//	char	**split;
//
//	split = ft_split(" ", str);
//	if (!split)
//		return;
//	mini->cmd = ft_strdup(*split++);
//	if (*split[0] = '-')
//		mini->option == 
//}
//
char	*ft_strdup(char *str)
{
	char	*dup;
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	dup = malloc(i + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	set_mini(char *str, t_mini *mini)
{
	char	**split;
	int	i;

	i = 0;
	split = ft_split(str, ' ');
	if (!split)
		return ;
	mini->cmd = ft_strdup(split[i++]);
	if (*split[0] == '-' )
	{
		mini->option = split[i][1];
		mini->args = NULL;
	}
	else
	{
		mini->option = '\0';
		mini->args = NULL;
	}
	free_tab(split);
}
int	main(int argc, char **argv, char **env)
{
	char	*str;
	char	*cwd;

	(void)argc;
	(void)argv;
	cwd = ft_pwd();
	while (1)
	{
		str = readline("minishell$ ");
		if (!strcmp(str, "exit"))
			ft_exit();
		else if (!strcmp(str, "pwd"))
			printf("%s\n", cwd);
		else if (!strcmp(str, "env"))
			ft_env(env);
//		else if (!strcmp(mini.cmd, "echo"))
//			ft_echo(&mini);
		free(str);
	}
	return (0);
}
