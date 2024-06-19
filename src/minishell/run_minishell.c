/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:23 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/17 23:00:23 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "minishell_signal.h"
#include "validation.h"

static int	install_signal_handlers(void)
{
	if (
		set_signal_handler(SIGINT, sigint_handler) < 0
		|| set_signal_handler(SIGQUIT, SIG_IGN) < 0
	)
		return (-1);
	return (0);
}

int	run_minishell(t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		if (install_signal_handlers() < 0)
			return (-1);
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (validate_input(line) != 0)
		{
			free(line);
			set_exit_status(2, minishell);
			continue ;
		}
		expand(&line, minishell);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		set_exit_status(execute(line, minishell), minishell);
		free(line);
	}
	rl_clear_history();
	return (0);
}
