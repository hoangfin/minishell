/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:31:20 by mito              #+#    #+#             */
/*   Updated: 2024/05/29 22:48:06 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	if (init_minishell(&minishell, envp) < 0)
		return (EXIT_FAILURE);
	start_minishell(&minishell);
	delete_minishell(&minishell);
	return (EXIT_SUCCESS);
}
