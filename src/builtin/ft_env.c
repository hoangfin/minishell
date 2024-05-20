/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:06:36 by mito              #+#    #+#             */
/*   Updated: 2024/05/19 23:49:44 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print(t_node *node, size_t i)
{
	char	*env_var;

	env_var = (char *)node->data;
	(void)i;
	printf("%s\n", env_var);
}

void	ft_env(t_command *cmd, t_list *env_list)
{
	ft_list_foreach(env_list, print);
}
