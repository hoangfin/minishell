/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:36:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/19 20:36:35 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"

int	ft_echo(t_command *cmd);
int	ft_cd(t_command *cmd, void *minishell);
int	ft_pwd(void *minishell);
int	ft_export(t_command *cmd, t_list *env_list, t_list *export_list);
int	ft_unset(t_command *cmd, t_list *env_list, t_list *export_list);
int	ft_env(t_command *cmd, t_list *env_list);
int	ft_exit(t_command *cmd, void *minishell);

#endif
