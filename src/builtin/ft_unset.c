/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:28 by mito              #+#    #+#             */
/*   Updated: 2024/05/27 18:19:28 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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

int		ft_unset(t_command *cmd, t_list *env_list, t_list *export_list)
{
	int i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (cmd->argv[i] != NULL)
	{
		if (!is_valid_env_key(cmd->argv[i]))
		{
			ft_fprintf(
				2,
				"minishell: unset: `%s': not a valid identifier\n",
				cmd->argv[i]
			);
			exit_status = 1;
		}
		else
		{
			ft_list_remove(env_list, cmd->argv[i], is_key_exist, free);
			ft_list_remove(export_list, cmd->argv[i], is_key_exist, free);
		}
		i++;
	}
	return (exit_status);
}
