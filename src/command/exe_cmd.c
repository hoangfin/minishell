/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 23:21:35 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/13 01:30:39 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

int	exe_cmd(t_command cmd)
{
	char	*temp;

	temp = cmd_line;
	while (*temp != '\0' && *temp != '&' && *temp != '|')
		temp++;
	exe_cmd(temp, minishell);
}