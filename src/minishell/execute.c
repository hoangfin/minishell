/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:21:35 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 22:43:07 by hoatran          ###   ########.fr       */
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

static int	execute_next(int cur_exit_status, char *str, t_minishell *mns)
{
	char	*logical_symbol;

	if (cur_exit_status == 0)
	{
		if (ft_strncmp(str, "&&", 2) == 0)
			return (execute(str + 2, mns));
		logical_symbol = find_and_logical(str + 2);
		if (logical_symbol != NULL)
			return (execute(logical_symbol + 2, mns));
	}
	if (cur_exit_status != 0)
	{
		if (ft_strncmp(str, "||", 2) == 0)
			return (execute(str + 2, mns));
		logical_symbol = find_or_logical(str + 2);
		if (logical_symbol != NULL)
			return (execute(logical_symbol + 2, mns));
	}
	return (cur_exit_status);
}

int	execute(char *str, t_minishell *minishell)
{
	char	*logical_op;
	char	*sub_str;
	int		exit_status;

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
	exit_status = execute_next(exit_status, logical_op, minishell);
	return (exit_status);
}
