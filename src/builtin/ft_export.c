/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:40:25 by mito              #+#    #+#             */
/*   Updated: 2024/05/16 16:30:00 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// if it already exists, it overwrite
// variable name can contain _
// if it contains other char: not a valid identifier

t_bool is_key_exist(t_node *node, void *data) // data = cmd->argv[i], node is element of env_list
{
	const char	*ev_node = (const char *)node->data;
	const char	*en_data = (char *)data;

	char *env_node_eq_ptr;
	char *en_data_eq_ptr;
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

static int	add_node(t_list *env_list, const char *str)
{
	char	*cmd_dup;
	t_node	*node;

	cmd_dup = ft_strdup(str);
	if (cmd_dup == NULL)
		return (-1);
	node = ft_list_node(cmd_dup);
	if (node == NULL)
	{
		free(cmd_dup);
		return (-1);
	}
	ft_list_push(env_list, node);
	return (0);
}

int		ft_export(t_command *cmd, t_list *env_list)
{
	int		i;
	t_node	*node;
	char	*cmd_dup;

	i = 1;
	while (cmd->argv[i] != NULL)
	{
		node = ft_list_find(env_list, cmd->argv[i], is_key_exist);
		if (node == NULL)
			add_node(env_list, cmd->argv[i]);
		else
		{
			free(node->data);
			node->data = ft_strdup(cmd->argv[i]);
		}
		i++;
	}
	return (0);
}

static void	print(t_node *node, size_t index)
{
	(void)index;
	printf("%s\n", (char *)node->data);
}
// int main(void) {
// 	t_list *env_list = ft_list(0);
// 	ft_list_push(env_list, ft_list_node(ft_strdup("ABC=hello")));
// 	ft_list_push(env_list, ft_list_node(ft_strdup("VSCODE_NONCE=46b9be33-9a93-4467-b759-f67dae90c639")));
// 	ft_list_push(env_list, ft_list_node(ft_strdup("VSCODE_INJECTION=1")));
// 	ft_list_push(env_list, ft_list_node(ft_strdup("LANG=en_US.UTF-8")));
// 	ft_list_push(env_list, ft_list_node(ft_strdup("COLORTERM=truecolor")));
// 	ft_list_push(env_list, ft_list_node(ft_strdup("HIVE=42")));

// 	ft_list_foreach(env_list, print);
// 	t_command cmd;
// 	cmd.argv = malloc(sizeof(char *) * 3);
// 	cmd.argv[0] = "export";
// 	cmd.argv[1] = "HIVEE=hi";
// 	cmd.argv[2] = NULL;
// 	ft_export(&cmd, env_list);
// 	printf("\nAfter ft_export\n");
// 	ft_list_foreach(env_list, print);
// 	free(cmd.argv);
// }
