/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:31:20 by mito              #+#    #+#             */
/*   Updated: 2024/05/20 00:26:26 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"
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
	char		*line;

	(void)argc;
	(void)argv;
	if (
		add_signal_handler(SIGINT, handle_sigint) < 0
		|| add_signal_handler(SIGQUIT, SIG_IGN) < 0
	)
		return (perror("error"), EXIT_FAILURE);
	if (init_minishell(&minishell, envp) < 0)
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line != '\0')
			add_history(line);
		minishell.exit_status = exe_cmd(line, &minishell);
		free(line);
	}
	rl_clear_history();
	clean_up(&minishell);
	return (EXIT_SUCCESS);
}
