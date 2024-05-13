/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:24:04 by mito              #+#    #+#             */
/*   Updated: 2024/05/13 14:20:38 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_echo(t_command cmd)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_putstr_fd(str[i], 1) < 0)
			return (-1);
		if (str[i + 1] != NULL)
			if (ft_putchar_fd(' ', 1) < 0)
				return (-1);
		i++;
	}
	if (flag == false)
	{
		if (ft_putchar_fd('\n', 1) < 0)
			return (-1);
	}
	return (0);
}
