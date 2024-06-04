/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 21:54:00 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/01 22:28:14 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "utils.h"

t_bool	is_directory(const char *pathname)
{
	struct stat statbuff;

	if (stat(pathname, &statbuff) == -1)
		return (false);
	return (S_ISDIR(statbuff.st_mode));
}
