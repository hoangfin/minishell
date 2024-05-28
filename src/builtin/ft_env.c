/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:06:36 by mito              #+#    #+#             */
/*   Updated: 2024/05/20 16:53:23 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_command *cmd, t_list *env_list)
{
	t_node	*node;

	if (cmd->argv[1] != NULL)
	{
		ft_fprintf(
			2, "%s: %s: %s\n", cmd->argv[0],
			cmd->argv[1], "No such file or directory"
		);
		return (127);
	}
	node = env_list->head;
	while (node != NULL)
	{
		if (printf("%s\n", (char *)node->data) < 0)
			return (1);
		node = node->next;
	}
	return (0);
}
