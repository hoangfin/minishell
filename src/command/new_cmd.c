/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:44:03 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/15 17:37:40 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "io.h"
#include "utils.h"

static int	init_io_list(t_list *list, char *str)
{
	char	*start;
	char	*end;
	t_io	*io;

	find_redirect_op(str, &start, &end);
	if (start == NULL || end == NULL)
		return (0);
	io = new_io(start, *start);
	if (io == NULL)
		return (-1);
	if (ft_list_push(list, io) < 0)
		return (delete_io(io), -1);
	ft_memset(start, ' ', end - start);
	return (init_io_list(list, str));
}

static int	init_cmd(t_command *cmd, const char *str)
{
	char	*str_dup;

	str_dup = ft_strdup(str);
	if (str_dup == NULL)
		return (-1);
	if (init_io_list(cmd->io_list, str_dup) < 0)
	{
		free(str_dup);
		return (-1);
	}
	cmd->argv = ft_parse_cmd(str_dup);
	if (cmd->argv == NULL)
	{
		free(str_dup);
		return (-1);
	}
	free(str_dup);
	return (0);
}

static t_bool	is_builtin_cmd(const char *str)
{
	int			i;
	const char	*builtin_cmds[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};

	i = 0;
	while (i < 7)
	{
		if (
			ft_strcmp(str, builtin_cmds[i]) == 0
			&& ft_strlen(str) == ft_strlen(builtin_cmds[i])
		)
			return (true);
		i++;
	}
	return (false);
}

t_command	*new_cmd(const char *str)
{
	t_command	*cmd;

	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->io_list = ft_list(0);
	if (cmd->io_list == NULL || init_cmd(cmd, str) < 0)
	{
		delete_cmd(cmd);
		return (NULL);
	}
	cmd->is_builtin = is_builtin_cmd(cmd->argv[0]);
	return (cmd);
}
