/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:12 by mito              #+#    #+#             */
/*   Updated: 2024/05/28 23:39:36 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin.h"
#include "utils.h"

static int print_export_list(t_list *export_list)
{
	char	*eq_sign;
	t_node	*node;

	node = export_list->head;
	while (node != NULL)
	{
		if (write(1, "declare -x ", 11) < 0)
			return (1);
		eq_sign = ft_strchr((const char *)node->data, '=');
		if (eq_sign == NULL)
			printf("%s\n", (const char *)node->data);
		else
		{
			if (write(1, node->data, eq_sign - (char *)node->data + 1) < 0)
				return (1);
			if (printf("\"%s\"\n", eq_sign + 1) < 0)
				return (1);
		}
		node = node->next;
	}
	return (0);
}

static int	handle_key_validation(const char *str)
{
	char	*eq_ptr;
	char	*export_key;

	eq_ptr = ft_strchr(str, '=');
	if (eq_ptr == NULL)
	{
		if (!is_valid_env_key(str))
		{
			ft_fprintf(2,
				"minishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
	}
	export_key = ft_substr(str, 0, eq_ptr - str);
	if (export_key == NULL)
		return (perror("minishell: ft_substr()\n"), 1);
	if (!is_valid_env_key(export_key))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", str);
		free(export_key);
		return (1);
	}
	free(export_key);
	return (0);
}

static t_bool	is_key_exist(t_node *node, void *data)
{
	const char	*ev_node = (const char *)node->data;
	const char	*en_data = (char *)data;
	char		*env_node_eq_ptr;
	char		*en_data_eq_ptr;

	env_node_eq_ptr = ft_strchr(ev_node, '=');
	en_data_eq_ptr = ft_strchr(en_data, '=');
	if (
		(env_node_eq_ptr - ev_node) == (en_data_eq_ptr - en_data)
		&& ft_strncmp(ev_node, en_data, (env_node_eq_ptr - ev_node)) == 0
	)
		return (true);
	else
		return (false);
}

static int	add_node(t_list *env_list, t_list *export_list, const char *str)
{
	char	*cmd_dup;

	cmd_dup = ft_strdup(str); // create address 0x100 with value of str
	if (cmd_dup == NULL)
		return (-1);
	if (ft_list_push(export_list, cmd_dup) < 0)
	{
		free(cmd_dup);
		return (-1);
	}
	if (ft_strchr(str, '=') != NULL)
	{
		cmd_dup = ft_strdup(str); // create address 0x200 with value of str and cmd_dup --> 0x200 now but export_list->tail->data still --> 0x100
		if (cmd_dup == NULL)
			return (-1);
		if (ft_list_push(env_list, cmd_dup) < 0)
		{
			free(cmd_dup);
			return (-1);
		}
	}
	return (0);
}

// int	ft_export(t_command *cmd, t_list *env_list)
// {
// 	int		i;
// 	t_node	*node;
// 	int		exit_status;

// 	i = 1;
// 	exit_status = 0;
// 	while (cmd->argv[i] != NULL)
// 	{
// 		if (handle_key_validation(cmd->argv[i]) == 1)
// 		{
// 			exit_status = 1;
// 			i++;
// 			continue ;
// 		}
// 		node = ft_list_find(env_list, cmd->argv[i], is_key_exist);
// 		if (node == NULL)
// 			add_node(env_list, cmd->argv[i]);
// 		else
// 		{
// 			free(node->data);
// 			node->data = ft_strdup(cmd->argv[i]);
// 		}
// 		i++;
// 	}
// 	return (exit_status);
// }


// to implement export

//declare -x TERM_PROGRAM="iTerm.app"
//TERM_PROGRAM=
//iTerm.app



int	ft_export(t_command *cmd, t_list *env_list, t_list *export_list)
{
	int		i;
	t_node	*node;
	int		exit_status;

	i = 1;
	exit_status = 0;

	if (cmd->argv[1] == NULL) // when the input was only "export"
		return (print_export_list(export_list));
	while (cmd->argv[i] != NULL)
	{
		if (handle_key_validation(cmd->argv[i]) == 1)
		{
			exit_status = 1;
			i++;
			continue ;
		}
		node = ft_list_find(env_list, cmd->argv[i], is_key_exist);
		if (node == NULL)
			add_node(env_list, export_list, cmd->argv[i]);
		else
		{
			free(node->data);
			node->data = ft_strdup(cmd->argv[i]);
		}
		i++;
	}
	return (exit_status);
}
