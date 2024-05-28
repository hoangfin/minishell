/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:20 by mito              #+#    #+#             */
/*   Updated: 2024/05/21 18:08:54 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "command.h"

static int	is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	print_exit(const char *arg, const char *err_msg, int exit_code)
{
	ft_fprintf(STDERR_FILENO, "minishell: exit: %s%s\n", arg, err_msg);
	return (exit_code);
}

int	ft_exit(t_command *cmd, int last_exit_status)
{
	int		exit_code;
	t_bool	overflow;

	overflow = false;
	if (cmd->argv[1] == NULL)
		return (last_exit_status);
	if (!is_str_digit(cmd->argv[1]))
		return (print_exit(cmd->argv[1], ": numeric argument required", 255));
	exit_code = ft_atol(cmd->argv[1], &overflow);
	if (overflow)
		return (print_exit(cmd->argv[1], ": numeric argument required", 255));
	if (count_arguments(cmd) > 2)
		return (print_exit(cmd->argv[1], ": too many arguments", 1));
	return (exit_code % 256);
}
