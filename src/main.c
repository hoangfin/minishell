/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:31:20 by mito              #+#    #+#             */
/*   Updated: 2024/05/28 23:41:36 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "minishell_signal.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_sigint(int signum)
{
	(void)signum;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	if (
		add_signal_handler(SIGINT, handle_sigint) < 0
		|| add_signal_handler(SIGQUIT, SIG_IGN) < 0
	)
		return (perror("error"), EXIT_FAILURE);
	if (init_minishell(&minishell, envp) < 0)
		return (EXIT_FAILURE);
	start_minishell(&minishell);
	delete_minishell(&minishell);
	return (EXIT_SUCCESS);
}
