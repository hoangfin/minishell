/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:21:35 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/04 15:27:52 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "utils.h"

static int	run(const char *str, t_minishell *minishell)
{
	int	exit_status;

	minishell->executor = new_executor(str);
	if (minishell->executor == NULL)
		return (perror("minishell: malloc"), 1);
	exit_status = run_executor(minishell->executor, minishell);
	delete_executor(minishell->executor);
	minishell->executor = NULL;
	return (exit_status);
}

// cmd1 && (cmd2 || cmd3)
// cmd1 && cmd2 || cmd3
// (cmd1 && (cmd2 || cmd3)) || (cmd4 && cmd5) && cmd6
// (cmd1 && cmd2) || (cmd3 && cmd4) || cmd5 && cmd6

/**
 *
*/
int	execute(const char *str, t_minishell *minishell)
{
	const char	*logical_op;
	char		*sub_str;
	int			exit_status;

	logical_op = find_logical_op(str);
	if (logical_op == NULL)
	{
		ungroup((char *)str);
		logical_op = find_logical_op(str);
	}
	if (logical_op == NULL)
		return (run(str, minishell));
	sub_str = ft_substr(str, 0, logical_op - str);
	if (sub_str == NULL)
		return (1);
	exit_status = execute(sub_str, minishell);
	free(sub_str);
	if (exit_status == 0 && ft_strncmp(logical_op, "&&", 2) == 0)
		exit_status = execute(logical_op + 2, minishell);
	if (exit_status != 0 && ft_strncmp(logical_op, "||", 2) == 0)
		exit_status = execute(logical_op + 2, minishell);
	return (exit_status);
}
