/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:17:05 by mito              #+#    #+#             */
/*   Updated: 2024/06/17 00:05:14 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "builtin.h"

int	ft_pwd(void)
{
	static char	cwd[1024] = {'\0'};
	char		buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		if (cwd[0] == '\0')
			return (1);
		else
		{
			if (printf("%s\n", cwd) < 0)
				return (1);
			return (0);
		}
	}
	ft_memcpy(cwd, buffer, 1024);
	if (printf("%s\n", cwd) < 0)
		return (1);
	return (0);
}
