/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:44:10 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/28 23:44:25 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"

int	run_builtin(t_command *cmd, t_minishell *minishell)
{
	const char	*cmd_name = cmd->argv[0];

	if (ft_strcmp(cmd_name, "cd") == 0)
		return (ft_cd(cmd, minishell->env_list));
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd_name, "env") == 0)
		return (ft_env(cmd, minishell->env_list));
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (ft_exit(cmd, minishell->exit_status));
	if (ft_strcmp(cmd_name, "export") == 0)
		return (ft_export(cmd, minishell->env_list, minishell->export_list));
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (ft_unset(cmd, minishell->env_list, minishell->export_list));
	return (0);
}
