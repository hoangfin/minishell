/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:02:39 by mito              #+#    #+#             */
/*   Updated: 2024/06/11 17:25:44 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "builtin.h"
#include "utils.h"

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

static int go_home(t_list *env_list)
{
	const char	*home_path;

	home_path = find_env("HOME", env_list);
	if (chdir(home_path) == -1)
		return (-1);
	update_pwd(home_path, env_list);
	return (0);
}
int ft_cd(t_command *cmd, t_list *env_list, t_list *export_list)
{
	char	buffer[1024];

    if (cmd->argv[1] == NULL)
	{
        if (go_home(env_list) < 0)
		{
			ft_fprintf(STDERR_FILENO, "minishell: %s: %s\n",
				cmd->argv[0], "HOME not set");
			return (1);
		}
		return (0);
	}
	if (cmd->argv[1][0] == '\0')
		return (0);
	if (chdir(cmd->argv[1]) == -1)
	{
		ft_fprintf(STDERR_FILENO, "minishell: cd: %s: %s\n",
			cmd->argv[1], strerror(errno));
		return (1);
	}
	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (1);
	update_pwd(buffer, env_list);
	update_pwd(buffer, export_list);
    return (0);
}

