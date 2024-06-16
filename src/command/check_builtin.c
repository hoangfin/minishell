/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:37:52 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/16 13:37:19 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_bool	check_builtin(const char *cmd)
{
	int			i;
	const char	*cmds[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL
	};

	i = 0;
	while (cmds[i] != NULL)
	{
		if (ft_strcmp(cmd, cmds[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
