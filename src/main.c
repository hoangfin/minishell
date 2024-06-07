/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:31:20 by mito              #+#    #+#             */
/*   Updated: 2024/06/07 14:52:57 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include "minishell.h"

static int	disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) < 0)
	{
		perror("minishell: tcgetattr");
		return (-1);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
	{
		perror("minishell: tcsetattr");
		return (-1);
	}
	return (0);
}

static int	enable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) < 0)
	{
		perror("minishell: tcgetattr");
		return (-1);
	}
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) < 0)
	{
		perror("minishell: tcsetattr");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	if (disable_echoctl() < 0)
		return (EXIT_FAILURE);
	if (init_minishell(&minishell, envp) < 0)
		return (enable_echoctl(), EXIT_FAILURE);
	if (run_minishell(&minishell) < 0)
	{
		delete_minishell(&minishell);
		enable_echoctl();
		return (EXIT_FAILURE);
	}
	delete_minishell(&minishell);
	if (enable_echoctl() < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
