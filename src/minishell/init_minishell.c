/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:36:12 by mito              #+#    #+#             */
/*   Updated: 2024/05/13 01:23:25 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_env_list(t_minishell *minishell, char **envp)
{
	char	*env_var;
	t_node	*node;

	minishell->env_list = ft_list(0);
	if (minishell->env_list == NULL)
		return (-1);
	while (envp != NULL && *envp != NULL)
	{
		env_var = ft_strdup(*envp);
		if (env_var == NULL)
			return (-1);
		node = ft_list_node(env_var);
		if (node == NULL)
			return (free(env_var), -1);
		ft_list_push(minishell->env_list, node);
		envp++;
	}
	return (0);
}

int	init_minishell(t_minishell *minishell, char **envp)
{
	if (init_env_list(minishell, envp) < 0)
	{
		clean_up(minishell);
		return (-1);
	}
	minishell->exit_status = 0;
	return (0);
}
