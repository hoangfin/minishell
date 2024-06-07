/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:36:12 by mito              #+#    #+#             */
/*   Updated: 2024/06/07 14:59:45 by hoatran          ###   ########.fr       */
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
	if (init_env_list(minishell, envp) < 0)
	{
		delete_minishell(minishell);
		return (-1);
	}
	minishell->export_list = clone_env_list(minishell->env_list);
	if (minishell->export_list == NULL)
		return (delete_minishell(minishell), -1);
	set_exit_status(0, minishell);
	return (0);
}
