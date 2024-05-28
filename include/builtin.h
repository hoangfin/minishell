/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:36:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/27 18:17:52 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"

int	ft_echo(t_command *cmd);
int	ft_cd(t_command *cmd, t_list *env_list);
int	ft_pwd(t_command *cmd);
int	ft_export(t_command *cmd, t_list *env_list, t_list *export_list);
int	ft_unset(t_command *cmd, t_list *env_list, t_list *export_list);
int	ft_env(t_command *cmd, t_list *env_list);
int	ft_exit(t_command *cmd, int last_exit_status);
int	exe_builtin(t_command *cmd, t_list *env_list, t_list *export_list, int last_exit_status);

#endif
