/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:17:05 by mito              #+#    #+#             */
/*   Updated: 2024/05/20 16:08:12 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(t_command *cmd)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (1);
	if (printf("%s\n", buffer) < 0)
		return (1);
	return (0);
}
