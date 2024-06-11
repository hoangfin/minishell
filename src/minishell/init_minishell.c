/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:36:12 by mito              #+#    #+#             */
/*   Updated: 2024/06/11 17:09:00 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static int	init_env_list(t_minishell *minishell, char **envp)
{
	char	*env_var;

	minishell->env_list = ft_list(0);
	if (minishell->env_list == NULL)
		return (-1);
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp(*envp, "OLDPWD", 6) == 0)
		{
			envp++;
			continue ;
		}
		env_var = ft_strdup(*envp);
		if (env_var == NULL)
			return (-1);
		if (ft_list_push(minishell->env_list, env_var) < 0)
		{
			free(env_var);
			return (-1);
		}
		envp++;
	}
	return (0);
}

int	init_minishell(t_minishell *minishell, char **envp)
{
	char	*temp;

	if (init_env_list(minishell, envp) < 0)
	{
		delete_minishell(minishell);
		return (-1);
	}
	minishell->export_list = clone_env_list(minishell->env_list);
	if (minishell->export_list == NULL)
		return (delete_minishell(minishell), -1);
	temp = ft_strdup("OLDPWD");
	if (temp == NULL)
		return (delete_minishell(minishell), -1);
	if (ft_list_push(minishell->export_list, ft_strdup("OLDPWD")) < 0)
	{
		free(temp);
		delete_minishell(minishell);
		return (-1);
	}
	set_exit_status(0, minishell);
	return (0);
}
