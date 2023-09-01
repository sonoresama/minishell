/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 15:27:31 by eorer             #+#    #+#             */
/*   Updated: 2023/09/01 17:35:18 by eorer            ###   ########.fr       */
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
	if ((i == -1 || i == 0) &&  str && (((str[0] == '+' || ft_isdigit(str[0]))
		&& n >= 0) || (str[0] == '-' && n <= 0)))
		return (0);
	return (1);
}

int	print_error(t_shell *shell)
{
	char	*tmp;

	tmp = join_three("exit: ", shell->cmd->exec.args[1],
			" : argument numérique nécessaire\n");
	if (!tmp)
	{
		shell->error = MALLOC_ERROR;
		return (1);
	}
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	return (0);
}

void	ft_exit(t_shell *shell)
{
	t_long		sortie;

	sortie = shell->last_error;
	if (shell->cmd && shell->cmd->exec.args && shell->cmd->exec.args[1])
		sortie = ft_atoi(shell->cmd->exec.args[1]);
	if (g_sig_handle == 10)
		printf("exit\n");
	if (shell->cmd && shell->cmd->exec.args && shell->cmd->exec.args[1]
		&& ft_check_sortie(shell->cmd->exec.args[1], sortie))
	{
		if (print_error(shell))
			return ;
		sortie = 2;
	}
	else if (shell->cmd && shell->cmd->exec.args && shell->cmd->exec.args[1]
		&& shell->cmd->exec.args[2])
	{
		write(2, "exit: trop d'arguments\n", 23);
		shell->last_error = 1;
		return ;
	}
	ft_clear_shell(shell);
	rl_clear_history();
	exit(sortie);
}
