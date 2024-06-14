/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:20 by mito              #+#    #+#             */
/*   Updated: 2024/06/12 13:56:42 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "command.h"
#include "minishell.h"

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_exit(
	t_minishell *minishell,
	const char *arg,
	const char *err_msg,
	int exit_code
)
{
	ft_fprintf(STDERR_FILENO, "minishell: exit: %s: %s\n", arg, err_msg);
	delete_minishell(minishell);
	exit(exit_code);
}

int	ft_exit(t_command *cmd, void *minishell)
{
	const t_minishell	*mns = (t_minishell *)minishell;
	int					exit_code;
	t_bool				overflow;

	overflow = false;
	if (cmd->argv[1] == NULL)
	{
		delete_minishell(minishell);
		exit(mns->exit_status);
	}
	if (!is_str_digit(cmd->argv[1]))
		print_exit(minishell, cmd->argv[1], "numeric argument required", 255);
	exit_code = ft_atol(cmd->argv[1], &overflow);
	if (overflow)
		print_exit(minishell, cmd->argv[1], "numeric argument required", 255);
	if (count_arguments(cmd) > 2)
		return (ft_fprintf(2, "minishell: exit: too many arguments\n"), 1);
	delete_minishell(minishell);
	exit(exit_code % 256);
}
