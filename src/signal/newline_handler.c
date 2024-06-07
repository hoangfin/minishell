/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newline_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:33:34 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/07 13:34:42 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	newline_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}
