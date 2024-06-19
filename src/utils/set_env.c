/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 23:20:32 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/20 00:03:26 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool	is_equal(t_node *node, void *key)
{
	const char	*env_key = (char *)node->data;
	char		*eq_sign;

	eq_sign = ft_strchr(env_key, '=');
	if (eq_sign == NULL)
	{
		if (ft_strcmp(env_key, key) == 0)
			return (true);
		return (false);
	}
	if (
		eq_sign - env_key == (int)ft_strlen(key)
		&& ft_strncmp(env_key, key, eq_sign - env_key) == 0
	)
		return (true);
	return (false);
}

static int	create_new_env(t_list *list, const char *key, const char *value)
{
	char	*env;

	if (value == NULL)
	{
		if (ft_list_push(list, (char *)key) < 0)
			return (-1);
		return (0);
	}
	env = ft_join_strings(3, key, "=", value);
	if (env == NULL || ft_list_push(list, env) < 0)
		return (free(env), -1);
	return (0);
}

static int	update_env_var(t_node *node, const char *key, const char *value)
{
	char	*env;

	if (value == NULL)
		return (0);
	env = ft_join_strings(3, key, "=", value);
	if (env == NULL)
		return (-1);
	free(node->data);
	node->data = env;
	return (0);
}

int	set_env(t_list *list, const char *key, const char *value)
{
	t_node	*node;

	node = ft_list_find(list, (char *)key, is_equal);
	if (node == NULL)
		return (create_new_env(list, key, value));
	return (update_env_var(node, key, value));
}
