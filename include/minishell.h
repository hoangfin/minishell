/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:48:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/15 17:45:37 by hoatran          ###   ########.fr       */
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

int			close_pipes(t_executor *executor);
int			execute_command(t_command *cmd, t_minishell *minishell);
int			execute(const char *str, t_minishell *minishell);
int			expand(char **str, t_minishell *minishell);
int			heredoc(char *delimiter, t_minishell *minishell);
int			init_minishell(t_minishell *minishell, char **envp);

int			redirect(\
				t_list *io_list, \
				int pipe_r, \
				int pipe_w, \
				t_minishell *minishell \
			);

int			run_executor(t_executor *executor, t_minishell *minishell);
int			run_minishell(t_minishell *minishell);

char		*resolve_env(const char *key, size_t n, t_minishell *minishell);

void		delete_executor(void *executor_ptr);
void		delete_minishell(void *minishell_ptr);
void		exit_on_error(\
				const char *err_src, \
				const char *err_msg, \
				t_minishell *minishell, \
				int exit_code \
			);
void		set_exit_status(int exit_status, t_minishell *minishell);

#endif
