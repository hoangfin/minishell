/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:36:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/12 21:24:31 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"

void	ft_echo(t_command *cmd);
void	ft_cd(t_command *cmd);
void	ft_pwd(t_command *cmd);
void	ft_export(t_command *cmd, t_list *env_list);
void	ft_unset(t_command *cmd, t_list *env_list);
void	ft_env(t_list *env_list);
void	ft_exit(void);

#endif
