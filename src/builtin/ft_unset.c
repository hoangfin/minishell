/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 10:48:28 by mito              #+#    #+#             */
/*   Updated: 2024/05/16 16:29:52 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static size_t	count_arguments(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		i++;
	//printf("count_arguments():: i = %d\n", i);
	return (i);
}
// error -> 1
// success -> 0

// no error message for no arg on Bash but zsh has a message

// ft_cmpnode == pred and because I called pred(node, data) inside

// t_bool ft_cmpnode(t_node *node, void *data) // data = cmd->argv[i], node is element of env_list
// {
// 	const char	*ev_node = (const char *)node->data;
// 	const char	*en_data = (char *)data;

// 	char *equal_sign_ptr;
// 	equal_sign_ptr = ft_strchr(ev_node, '=');
// 	if (ft_strncmp(ev_node, en_data, (equal_sign_ptr - ev_node)) == 0)
// 		return (true);
// 	else
// 		return (false);
// }

static t_bool ft_cmpnode(t_node *node, void *data) // data = cmd->argv[i], node is element of env_list
{
	const char	*ev_node = (const char *)node->data;
	const char	*en_data = (const char *)data;

	char *env_node_eq_ptr;
	int i;
	//char *en_data_eq_ptr;
	printf("key=%s\n", ev_node);
	env_node_eq_ptr = ft_strchr(ev_node, '=');
	//printf("env_node_eq_ptr is %s\n", env_node_eq_ptr);
	i = ft_strlen(en_data);

	//printf("env_node_eq_ptr - ev_node is %ld\n", env_node_eq_ptr - ev_node);
	if (
		((env_node_eq_ptr - ev_node) == i)
		&& ft_strncmp(ev_node, en_data, i) == 0
	)
		return (true);
	else
		return (false);
}

int		ft_unset(t_command *cmd, t_list *env_list)
{
	int i;
	int argc;

	i = 1;
	argc = count_arguments(cmd);
	if (argc == 1)
	{
		return (0); // if it is only exit, then do nothing and 0
	}
	while (i < argc)
	{
		//printf("cmd->argv[i] = %s\n", cmd->argv[i]); // delete it
		printf("argv=%s\n", cmd->argv[i]);
		ft_list_remove(env_list, cmd->argv[i], ft_cmpnode, free);
		i++;
	}
	return (1);
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
// 	cmd.argv[0] = "unset";
// 	cmd.argv[1] = "VSCODE_INJECTIONN";
// 	cmd.argv[2] = NULL;
// 	ft_unset(&cmd, env_list);
// 	printf("\nAfter ft_unset\n");
// 	ft_list_foreach(env_list, print);
// 	free(cmd.argv);
// }
