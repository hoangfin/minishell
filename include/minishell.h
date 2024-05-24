/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:48:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/23 21:39:57 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <sys/stat.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <string.h>
# include <limits.h>

typedef struct s_minishell
{
	t_list	*env_list;
	char	**path;
	int		exit_status;
	char	exit_status_str[sizeof(int) * 8 + 1];
}	t_minishell;

int			init_minishell(t_minishell *minishell, char **envp);
int			expand(char **str, t_minishell *minishell);
const char	*resolve_env(const char *key, size_t n, t_minishell *minishell);
void		set_exit_status(int exit_status, t_minishell *minishell);
void		clean_up(t_minishell *minishell);

#endif
