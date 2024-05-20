/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:05:46 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/19 23:17:28 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	is_builtin_cmd(const char *str)
{
	int			i;
	const char	*builtin_cmds[] = {
		"cd", "echo", "env", "exit", "export", "pwd", "unset"
	};

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(str, builtin_cmds[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
