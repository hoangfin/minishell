/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:24:04 by mito              #+#    #+#             */
/*   Updated: 2024/05/10 16:46:26 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(const char **str, t_bool flag)
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
