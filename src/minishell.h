/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:48:58 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/08 23:50:46 by hoatran          ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
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
}	t_minishell;

int		init_minishell(t_minishell *minishell, char **envp);
void	clean_up(t_minishell *minishell);

// when flag is false, echo() print with newline.
int		ft_echo(const char **str, t_bool flag);
// ◦ cd with only a relative or absolute path
int		ft_pwd(void);
void	ft_export(const char *env_var);
void	ft_unset(const char *env_var_key);
void	ft_env(t_minishell *minishell);
void	ft_exit(void);

#endif