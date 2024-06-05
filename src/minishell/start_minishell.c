/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:23 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/05 15:26:06 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

static void	handle_sigint(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static int	install_signal_handlers(void)
{
	struct sigaction	sigint_sa;
	struct sigaction	sigquit_sa;

	sigemptyset(&sigint_sa.sa_mask);
	sigint_sa.sa_handler = handle_sigint;
	sigint_sa.sa_flags = 0;
	sigemptyset(&sigquit_sa.sa_mask);
	sigquit_sa.sa_handler = SIG_IGN;
	sigquit_sa.sa_flags = 0;
	if (
		sigaction(SIGINT, &sigint_sa, NULL) < 0
		|| sigaction(SIGQUIT, &sigquit_sa, NULL) < 0
	)
	{
		perror("minishell: sigaction");
		return (-1);
	}
	return (0);
}

void	start_minishell(t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		if (install_signal_handlers() < 0)
			break ;
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line == '\0')
			continue ;
		add_history(line);
		if (validate_input(line) != 0)
		{
			free(line);
			set_exit_status(2, minishell);
			continue ;
		}
		expand(&line, minishell);
		set_exit_status(execute(line, minishell), minishell);
		free(line);
	}
	rl_clear_history();
}
