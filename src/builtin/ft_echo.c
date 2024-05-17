/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:24:04 by mito              #+#    #+#             */
/*   Updated: 2024/05/13 16:27:09 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// int	ft_echo(t_command *cmd)
// {
// 	int i;

// 	i = 0;
// 	while (cmd->argv[i] != NULL)
// 	{
// 		if (ft_putstr_fd(cmd->argv[i], 1) < 0)
// 			return (-1);
// 		if (cmd->argv[i + 1] != NULL)
// 			if (ft_putchar_fd(' ', 1) < 0)
// 				return (-1);
// 		i++;
// 	}
// 	if (ft_strncmp(cmd->argv[1], "-n", 2) == 0)
// 	{
// 		if (ft_putchar_fd('\n', 1) < 0)
// 			return (-1);
// 	}
// 	return (0);
// }

int	ft_echo(t_command *cmd)
{
	int i;
	int has_opt;

	i = 0;
	has_opt = 0;
	if (ft_strncmp(cmd->argv[1], "-n", 2) == 0)
	{
		has_opt = 1;
		i = 2;
	}
	while (cmd->argv[i] != NULL)
	{
		if (ft_putstr_fd(cmd->argv[i], 1) < 0)
			return (1);
		if (cmd->argv[i + 1] != NULL)
			if (ft_putchar_fd(' ', 1) < 0)
				return (1);
		i++;
	}
	if (has_opt == 0) // with -n option, we don't put newline
	{
		if (ft_putchar_fd('\n', 1) < 0)
			return (1);
	}
	return (0);
}
