/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:06:36 by mito              #+#    #+#             */
/*   Updated: 2024/05/10 16:49:09 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print(t_node *node, size_t i)
{
	char	*env_var;
	
	env_var = (char *)node->data;
	(void)i;
	printf("%s\n", env_var);
}

void	ft_env(t_minishell *minishell)
{
	ft_list_foreach(minishell->env_list, print);
}
