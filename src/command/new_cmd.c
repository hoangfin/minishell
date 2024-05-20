/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 23:44:03 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/19 14:52:47 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static int	extract(char *str, int c, char **result)
{
	char	*c_ptr;

	*result = NULL;
	while (*str != '\0' && *str != c)
		str++;
	if (*str == '\0')
		return (0);
	c_ptr = str;
	while (*str != '\0' && (*str == c || ft_isspace(*str)))
		str++;
	if (*str == '\0')
		return (0);
	while (*str != '\0' && !ft_isspace(*str))
	{
		if (*str == '\'' || *str == '"')
			str = ft_strchr(str + 1, *str);
		if (str == NULL)
			return (0);
		str++;
	}
	*result = ft_substr(c_ptr, 0, str - c_ptr);
	if (*result == NULL)
		return (-1);
	ft_memset(c_ptr, ' ', str - c_ptr);
	return (0);
}

static int	init_list(t_list *list, char *str, int c)
{
	char	*result;
	t_io	*io;

	while (1)
	{
		if (extract(str, c, &result) < 0)
			return (-1);
		if (result == NULL)
			return (0);
		io = new_io(result, c);
		if (io == NULL)
		{
			free(result);
			return (-1);
		}
		if (ft_list_push(list, io) < 0)
		{
			free(result);
			delete_io(io);
			return (-1);
		}
		free(result);
	}
	return (0);
}

static int	init_cmd(t_command *cmd, const char *str)
{
	char	*str_dup;

	str_dup = ft_strdup(str);
	if (str_dup == NULL)
		return (-1);
	if (
		init_list(cmd->input_list, str_dup, '<') < 0
		|| init_list(cmd->output_list, str_dup, '>') < 0
	)
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

t_command	*new_cmd(const char *str)
{
	t_command	*cmd;

	cmd = (t_command *)ft_calloc(1, sizeof(t_command));
	if (cmd == NULL)
		return (NULL);
	cmd->input_list = ft_list(0);
	cmd->output_list = ft_list(0);
	if (
		cmd->input_list == NULL
		|| cmd->output_list == NULL
		|| init_cmd(cmd, str) < 0
	)
	{
		delete_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
