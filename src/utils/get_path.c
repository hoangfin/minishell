/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:30:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/02 22:23:05 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

const char	**get_path(t_list *env_list)
{
	const char	*path_env_value;

	path_env_value = find_env("PATH", env_list);
	if (path_env_value == NULL)
		return (NULL);
	return ((const char **)ft_split(path_env_value, ':'));
}
