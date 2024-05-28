/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:03:55 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/28 23:53:59 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "command.h"

int	execute(const char *str, t_minishell *minishell);
int	run(const char *str, t_minishell *minishell);
int	run_on_current_process(t_command *cmd, t_minishell *minishell);
int	run_builtin(t_command *cmd, t_minishell *minishell);
int	run_on_sub_process(t_list *cmd_list, t_minishell *minishell);

#endif

