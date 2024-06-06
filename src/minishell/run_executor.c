/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:26:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/06 15:38:40 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <errno.h>
#include "minishell.h"
#include "constants.h"
#include "utils.h"

static int	run_on_current_process(t_command *cmd, t_minishell *minishell)
{
	const int	stdin = dup(STDIN_FILENO);
	const int	stdout = dup(STDOUT_FILENO);
	int			exit_status;

	if (stdin < 0 || stdout < 0)
		return (perror("minishell: dup"), 1);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		ft_printf("exit\n");
	if (
		redirect_input(cmd->input_list, -1) < 0
		|| redirect_output(cmd->output_list, -1) < 0
	)
		return (1);
	exit_status = execute_command(cmd, minishell);
	unlink(HERE_DOC_TEMP_FILE);
	if (dup2_close(stdin, STDIN_FILENO) < 0)
		return (1);
	if (dup2_close(stdout, STDOUT_FILENO) < 0)
		return (1);
	return (exit_status);
}

static int	run_on_sub_process(int i, t_command *cmd, t_minishell *minishell)
{
	const t_executor	*executor = minishell->executor;
	int					pipedes_in;
	int					pipedes_out;
	int					exit_status;

	pipedes_in = INT_MIN;
	pipedes_out = INT_MIN;
	if (executor->pipes != NULL && i > 0)
		pipedes_in = dup(executor->pipes[i - 1][0]);
	if (executor->pipes != NULL && i < executor->num_of_pids - 1)
		pipedes_out = dup(executor->pipes[i][1]);
	if (pipedes_in == -1 || pipedes_out == -1)
		return (perror("minishell: dup"), 1);
	close_pipes(executor->pipes);
	if (
		redirect_input(cmd->input_list, pipedes_in) < 0
		|| redirect_output(cmd->output_list, pipedes_out) < 0
	)
		return (1);
	exit_status = execute_command(cmd, minishell);
	delete_minishell(minishell);
	exit(exit_status);
}

static int	start_workers(t_executor *executor, t_minishell *minishell)
{
	const t_node	*node = executor->cmd_list->head;
	int				i;

	i = 0;
	while (i < executor->num_of_pids)
	{
		executor->pids[i] = fork();
		if (executor->pids[i] < 0)
		{
			perror("minishell: fork");
			close_pipes(executor->pipes);
			wait_all(executor->pids, executor->num_of_pids);
			return (-1);
		}
		if (executor->pids[i] == 0)
			run_on_sub_process(i, node->data, minishell);
		node = node->next;
		i++;
	}
	if (close_pipes(executor->pipes) < 0)
		return (-1);
	return (0);
}

/**
 * Run list of commands in struct `t_executor` whether in child processes or
 * in the same process that `./minishell` is running on.
 *
 * @param executor The pointer to struct `t_executor`.
 * @param minishell The pointer to struct `t_minishell`.
 *
 * @returns Exit status code between `0` and `255`. The `0` number indicates
 * 			success, non-zero number means error.
*/
int	run_executor(t_executor *executor, t_minishell *minishell)
{
	t_command	*cmd;
	int			exit_status;

	cmd = (t_command *)executor->cmd_list->head->data;
	if (executor->cmd_list->length == 1 && executor->num_of_pids == 0)
		return (run_on_current_process(cmd, minishell));
	if (start_workers(executor, minishell) < 0)
		return (1);
	exit_status = wait_all(executor->pids, executor->num_of_pids);
	if (access(HERE_DOC_TEMP_FILE, F_OK) != -1)
		unlink(HERE_DOC_TEMP_FILE);
	return (exit_status);
}
