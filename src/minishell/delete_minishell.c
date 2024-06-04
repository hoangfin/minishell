/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:51:21 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/31 23:29:11 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"

void	delete_minishell(void *minishell_ptr)
{
	t_minishell	*minishell = (t_minishell *)minishell_ptr;
	
	if (minishell == NULL)
		return ;
	if (minishell->env_list != NULL)
		ft_list_clear(&minishell->env_list, free);
	if (minishell->export_list != NULL)
		ft_list_clear(&minishell->export_list, free);
	if (minishell->executor != NULL)
		delete_executor(minishell->executor);
}
