/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:48:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/02 20:04:54 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include "libft.h"
# include "command.h"

typedef struct s_executor
{
	int		**pipes;
	t_list	*cmd_list;
	pid_t	*pids;
	int		num_of_pipes;
	int		num_of_pids;
}	t_executor;

typedef struct s_minishell
{
	t_list		*env_list;
	t_list		*export_list;
	t_executor	*executor;
	int			exit_status;
	char		exit_status_str[sizeof(int) * 8 + 1];
}	t_minishell;

t_executor	*new_executor(const char *str);
int			run_executor(t_executor *executor, t_minishell *minishell);
void		delete_executor(void *executor_ptr);

int			init_minishell(t_minishell *minishell, char **envp);
int			execute(const char *str, t_minishell *minishell);
int			execute_command(t_command *cmd, t_minishell *minishell);
int			expand(char **str, t_minishell *minishell);

const char	*resolve_env(const char *key, size_t n, t_minishell *minishell);

void		start_minishell(t_minishell *minishell);
void		set_exit_status(int exit_status, t_minishell *minishell);
void		delete_minishell(void *minishell_ptr);

#endif
