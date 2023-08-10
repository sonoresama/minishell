/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:31 by eorer             #+#    #+#             */
/*   Updated: 2023/08/10 17:46:20 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	ft_check_sortie(char *str, t_long n)
{
	int		i;
	t_long	tmp;
	t_long	tmp2;

	tmp2 = n;
	i = ft_strlen(str) - 1;
	while (str && i >= 0 && str[i] && ft_isdigit(str[i]))
	{
		tmp = tmp2 % 10;
		tmp2 = tmp2 / 10;
		if (tmp < 0)
			tmp *= -1;
		if (str[i] != tmp + '0')
			return (1);
		i--;
	}
	if (str && (((str[0] == '+' || ft_isdigit(str[0])) && n >= 0)
			|| (str[0] == '-' && n <= 0)))
		return (0);
	return (1);
}

void	ft_exit(t_shell *shell)
{
	t_long		sortie;
	t_cmd		*cmd;
	char	*tmp;

	sortie = shell->last_error;
	cmd = shell->cmd;
	if (cmd && cmd->exec.args && cmd->exec.args[1])
		sortie = ft_atoi(cmd->exec.args[1]);
	printf("exit\n");
	if (cmd && cmd->exec.args && cmd->exec.args[1] && ft_check_sortie(cmd->exec.args[1], sortie))
	{
		tmp = join_three("exit: ", cmd->exec.args[1], " : argument numérique nécessaire\n");
		if (!tmp)
		{
			shell->error = MALLOC_ERROR;
			return ;
		}
		write(2, tmp, ft_strlen(tmp));
		free(tmp);
		sortie = 2;
	}
	else if (cmd && cmd->exec.args && cmd->exec.args[1] && cmd->exec.args[2])
	{
		write(2, "exit: trop d'arguments\n", 23);
		shell->last_error = 1;
		return ;
	}
	ft_clear_shell(shell);
	rl_clear_history();
	exit(sortie);
}
