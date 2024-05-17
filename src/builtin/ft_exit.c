/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:26:20 by mito              #+#    #+#             */
/*   Updated: 2024/05/15 15:47:30 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

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

int	ft_exit(t_command *cmd)
{
	int exit_code;
	int i;

	exit_code = 1;
	i = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (count_arguments(cmd) == 1) // when it is only "exit"
		exit_code = 0;
	else if (count_arguments(cmd) == 2)
	{
		if (!(is_str_digit(cmd->argv[1]))) // if it contains non-numeric char
		{
			ft_fprintf(STDERR_FILENO, "%s%s\n", cmd->argv[1], ": numeric argument required");
			exit_code = 255;
		}
		else
			exit_code = ft_atoi(cmd->argv[1], false); // true or false?
	}
	else // if there are more than 1 args
	{
		if (is_str_digit(cmd->argv[1])) // check if the first arg contains non-numeric chars
		{
			ft_fprintf(STDERR_FILENO, "%s%s\n", cmd->argv[1], ": numeric argument required");
			exit_code = 255;
		}
		else
			ft_fprintf(STDERR_FILENO, "%s%s\n", cmd->argv[0], ": too many arguments");
	}
	return (exit_code);
}
