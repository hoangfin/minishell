/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:23:33 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/28 23:53:05 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "command.h"
#include "builtin.h"
#include "utils.h"
#include <string.h>
#include <errno.h>
#include <sys/types.h>

/**
 * The `run()` function parses a string command line to a linked list of
 * `t_command *`. It then decides whether those commands should be run in
 * child processes or in the same process that `./minishell` is running on
*/
int	run(const char *str, t_minishell *minishell)
{
	t_command	*cmd;
	int			exit_status;

	exit_status = 0;
	minishell->cmd_list = parse_cmd(str);
	if (minishell->cmd_list == NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: xmalloc: %s\n", strerror(errno));
		return (1);
	}
	cmd = minishell->cmd_list->head->data;
	if (minishell->cmd_list->length == 1)
		exit_status = run_on_current_process(cmd, minishell);
	// else
	// 	exit_status = run_pipe_cmd(minishell->cmd_list, minishell);
	// ft_list_clear(&minishell->cmd_list, delete_cmd);
	return (exit_status);
}
