/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:33:35 by mito              #+#    #+#             */
/*   Updated: 2024/06/20 15:01:52 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static t_bool	handle_equal_sign(char *key, char *env_var)
{
	const char	*env_var_eq = ft_strchr(env_var, '=');
	const char	*key_eq = ft_strchr(key, '=');
	size_t		length;

	if (key_eq == NULL)
	{
		length = ft_strlen(key);
		if (
			((env_var_eq - env_var) == (int)length)
			&& ft_strncmp(env_var, key, length) == 0
		)
			return (true);
		return (false);
	}
	if (
		(env_var_eq - env_var) == (key_eq - key)
		&& ft_strncmp(env_var, key, (env_var_eq - env_var)) == 0
	)
		return (true);
	return (false);
}

static t_bool	is_key_exist_v2(t_node *node, void *data)
{
	const char	*env_var = (const char *)node->data;
	const char	*key = (const char *)data;

	if (
		ft_strchr(env_var, '=') == NULL
		&& ft_strchr(key, '=') == NULL
	)
	{
		if (ft_strcmp(env_var, key) == 0)
			return (true);
		return (false);
	}
	return (handle_equal_sign((char *)data, (char *)node->data));
}

int	update_env(const char *key, const char *value, t_list *list)
{
	t_node	*node;
	char	*new_env;

	node = ft_list_find(list, (void *)key, is_key_exist_v2);
	if (node == NULL)
		return (0);
	new_env = ft_join_strings(3, key, "=", value);
	if (new_env == NULL)
		return (-1);
	free(node->data);
	node->data = new_env;
	return (0);
}
