/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_on_sub_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 21:12:53 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/26 22:16:18 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/wait.h>
#include <errno.h>

int	run_on_sub_process(t_list *cmd_list, t_minishell *minishell)
{
	pid_t	*pid;
	t_node	*node;
	int		wstatus;

	node = cmd_list->head;
	while (node != NULL)
	{
		pid = fork();
		if (pid == 0)
			run_command(node->data, minishell);
		node = node->next;
	}
	while (1)
	{
		if (wait(&wstatus) == -1 && errno == ECHILD)
			break ;
		if (w)
	}
	return ()
}