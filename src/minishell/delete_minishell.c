/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:51:21 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/30 18:36:48 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"

void	delete_minishell(void *minishell)
{
	t_minishell	*mnshell;

	mnshell = (t_minishell *)minishell;
	ft_list_clear(&mnshell->env_list, free);
	if (mnshell->cmd_list != NULL)
		ft_list_clear(&mnshell->cmd_list, delete_cmd);
}
