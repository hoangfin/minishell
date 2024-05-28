/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:33:35 by mito              #+#    #+#             */
/*   Updated: 2024/05/24 18:22:19 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool is_key_exist(t_node *node, void *data)
{
	const char	*ev_node = (const char *)node->data;
	const char	*en_data = (const char *)data;
	char		*env_node_eq_ptr;
	int			i;

	env_node_eq_ptr = ft_strchr(ev_node, '=');
	i = ft_strlen(en_data);
	if (
		((env_node_eq_ptr - ev_node) == i)
		&& ft_strncmp(ev_node, en_data, i) == 0
	)
		return (true);
	else
		return (false);
}

int	update_env(const char *key, const char *value, t_list *env_list)
{
	t_node	*node;
	char	*new_env;

	node = ft_list_find(env_list, key, is_key_exist);
	if (node == NULL)
		return (0);
	new_env = ft_join_strings(3, key, "=", value);
	if (new_env == NULL)
		return (-1);
	free(node->data);
	node->data = new_env;
	return (0);
}
