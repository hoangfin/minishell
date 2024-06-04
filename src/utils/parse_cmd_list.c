/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 13:34:48 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/31 16:53:58 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static int	init_list(t_list *list, char **splits)
{
	int			i;
	t_command	*cmd;

	i = 0;
	while (splits[i] != NULL)
	{
		cmd = new_cmd(splits[i]);
		if (cmd == NULL)
			return (-1);
		if (ft_list_push(list, cmd) < 0)
		{
			delete_cmd(cmd);
			return (-1);
		}
		i++;
	}
	return (0);
}

t_list	*parse_cmd_list(const char *str)
{
	char	**splits;
	t_list	*list;

	splits = ft_split(str, '|');
	if (splits == NULL)
		return (NULL);
	list = ft_list(0);
	if (list == NULL)
	{
		ft_del_str_arr(&splits);
		return (NULL);
	}
	if (init_list(list, splits) < 0)
	{
		ft_del_str_arr(&splits);
		ft_list_clear(&list, delete_cmd);
		return (NULL);
	}
	ft_del_str_arr(&splits);
	return (list);
}
