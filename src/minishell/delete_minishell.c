/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:51:21 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/27 22:55:16 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"

void	delete_minishell(void *minishell)
{
	t_minishell	*mnshell;

	mnshell = (t_minishell *)minishell;
	ft_list_clear(&mnshell->env_list, free);
	ft_list_clear(&mnshell->cmd_list, delete_cmd);
}
