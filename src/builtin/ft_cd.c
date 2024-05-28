/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:02:39 by mito              #+#    #+#             */
/*   Updated: 2024/05/27 14:22:54 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"

static void	update_pwd(const char *current_path, t_list *env_list)
{
	const char	*pwd;
	const char	*old_pwd;

	pwd = find_env("PWD", env_list);
	if (pwd != NULL)
		update_env("OLDPWD", pwd, env_list);
	update_env("PWD", current_path, env_list);
}

static int go_home(t_list *env_list)
{
	const char	*home_path;
	const char	*pwd;

	home_path = find_env("HOME", env_list);
	if (chdir(home_path) == -1)
		return (-1);
	update_pwd(home_path, env_list);
	return (0);
}
int ft_cd(t_command *cmd, t_list *env_list)
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
    return (0);
}

