/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_underscore_var.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:11:47 by mito              #+#    #+#             */
/*   Updated: 2024/06/12 18:22:12 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

int	update_underscore_var(t_minishell *minishell)
{
	t_command	*cmd;
	size_t		count;

	if (minishell->executor->num_of_pids > 1)
	{
		if (update_env("_", "", minishell->env_list) < 0)
			return (-1);
		return (0);
	}
	cmd = (t_command *)minishell->executor->cmd_list->head->data;
	count = count_str_array((const char **)cmd->argv);
	if (update_env("_", cmd->argv[count - 1], minishell->env_list) < 0)
		return (-1);
	return (0);
}
