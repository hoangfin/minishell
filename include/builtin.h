/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:36:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/13 14:33:38 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "command.h"

int	ft_echo(t_command *cmd);
int	ft_cd(t_command *cmd);
int	ft_pwd(void);
int	ft_export(t_command *cmd, t_list *env_list);
int	ft_unset(t_command *cmd, t_list *env_list);
int	ft_env(t_list *env_list);
int	ft_exit(void);

#endif
