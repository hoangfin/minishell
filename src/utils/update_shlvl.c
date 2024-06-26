/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:47:03 by mito              #+#    #+#             */
/*   Updated: 2024/06/26 14:27:06 by mito             ###   ########.fr       */
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

int	update_shlvl(t_list *list)
{
	t_node	*node;
	char	*shlvl;
	int		shlvl_number;
	char	buf[sizeof(int) * 8 + 1];

	node = ft_list_find(list, "SHLVL", is_key_exist_v2);
	if (node == NULL)
	{
		shlvl = ft_strdup("SHLVL=1");
		if (shlvl == NULL)
			return (-1);
		if (ft_list_push(list, shlvl) < 0)
			return (-1);
		return (0);
	}
	shlvl = ft_strchr((char *)node->data, '=');
	shlvl_number = ft_atoi(shlvl + 1, NULL);
	ft_itoa(shlvl_number + 1, buf, 10);
	shlvl = ft_join_strings(2, "SHLVL=", buf);
	if (shlvl == NULL)
		return (-1);
	free(node->data);
	node->data = shlvl;
	return (0);
}
