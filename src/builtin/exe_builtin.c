/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:44:10 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/27 18:17:40 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	exe_builtin(t_command *cmd, t_list *env_list, t_list *export_list, int last_exit_status)
{
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (ft_cd(cmd, env_list));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (ft_env(cmd, env_list));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (ft_exit(cmd, last_exit_status));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (ft_export(cmd, env_list, export_list));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (ft_unset(cmd, env_list, export_list));
	return (0);
}
