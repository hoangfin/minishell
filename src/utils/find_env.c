/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 16:19:26 by mito              #+#    #+#             */
/*   Updated: 2024/05/24 16:36:42 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

const char	*find_env(const char *key, t_list *env_list)
{
	t_node	*node;
	char	*ptr;
	size_t	key_length;

	key_length = ft_strlen(key);
	node = env_list->head;
	while (node != NULL)
	{
		ptr = ft_strchr(node->data, '=');
		if (
			key_length == (size_t)(ptr - (char *)node->data)
			&& ft_strncmp(key, node->data, key_length) == 0
		)
			return (ptr + 1);
		node = node->next;
	}
	return (NULL);
}
