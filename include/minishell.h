/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:48:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/28 23:20:00 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct s_minishell
{
	t_list	*env_list;
	t_list	*export_list;
	char	**path;
	t_list	*cmd_list;
	int		exit_status;
	char	exit_status_str[sizeof(int) * 8 + 1];
}	t_minishell;

int			init_minishell(t_minishell *minishell, char **envp);

int			expand(char **str, t_minishell *minishell);

const char	*resolve_env(const char *key, size_t n, t_minishell *minishell);

void		start_minishell(t_minishell *minishell);
void		set_exit_status(int exit_status, t_minishell *minishell);
void		delete_minishell(void *minishell);

#endif
