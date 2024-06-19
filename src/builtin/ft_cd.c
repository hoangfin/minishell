/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:02:39 by mito              #+#    #+#             */
/*   Updated: 2024/06/19 23:07:45 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "builtin.h"
#include "utils.h"
#include "minishell.h"
#include "constants.h"

static int	update_pwd(const char *current_path, t_list *list)
{
	const char	*pwd;
	const char	*old_pwd;
	char		*temp;

	pwd = find_env("PWD", list);
	if (pwd != NULL)
	{
		old_pwd = find_env("OLDPWD", list);
		if (old_pwd == NULL)
		{
			temp = ft_join_strings(2, "OLDPWD=", pwd);
			if (temp == NULL)
				return (-1);
			if (ft_list_push(list, temp) < 0)
				return (free(temp), -1);
		}
		update_env("OLDPWD", pwd, list);
	}
	update_env("PWD", current_path, list);
	return (0);
}

static int	go_home(t_minishell *minishell)
{
	const char	*home_path = find_env("HOME", minishell->env_list);

	if (home_path == NULL)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s\n", "HOME not set");
		return (-1);
	}
	if (chdir(home_path) == -1)
	{
		ft_fprintf(\
			2, "minishell: cd: %s: %s\n", home_path, strerror(errno) \
		);
		return (-1);
	}
	ft_strlcpy(minishell->cwd, home_path, PATH_MAX);
	update_pwd(home_path, minishell->env_list);
	update_pwd(home_path, minishell->export_list);
	return (0);
}

static int	go_to_dir(const char *path, t_minishell *minishell)
{
	char	buffer[PATH_MAX];

	if (chdir(path) == -1)
	{
		ft_fprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		ft_fprintf(\
			STDERR_FILENO, \
			"%s: %s: %s\n", \
			"minishell: cd: error retrieving current directory", \
			"getcwd: cannot access parent directories", \
			strerror(errno) \
		);
		return (1);
	}
	ft_strlcpy(minishell->cwd, buffer, PATH_MAX);
	update_pwd(buffer, minishell->env_list);
	update_pwd(buffer, minishell->export_list);
	return (0);
}

int	ft_cd(t_command *cmd, void *minishell)
{
	if (cmd->argv[1] == NULL)
	{
		if (go_home(minishell) < 0)
			return (1);
		return (0);
	}
	if (cmd->argv[1][0] == '\0')
		return (0);
	return (go_to_dir(cmd->argv[1], minishell));
}
