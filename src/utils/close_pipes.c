/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 16:50:02 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/02 22:49:45 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	close_pipes(int **pipes)
{
	int	status;

	status = 0;
	while (pipes != NULL && *pipes != NULL)
	{
		if ((*pipes)[0] != -1)
		{
			if (close((*pipes)[0]) < 0)
			{
				perror("minishell: close");
				status = -1;
			}
		}
		if ((*pipes)[1] != -1)
		{
			if (close((*pipes)[1]) < 0)
			{
				perror("minishell: close");
				status = -1;
			}
		}
		pipes++;
	}
	return (status);
}
