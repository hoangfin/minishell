/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:30:23 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/25 17:36:10 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include <readline/readline.h>
#include <readline/history.h>

void	start_minishell(t_minishell *minishell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (*line == '\0')
			continue ;
		add_history(line);
		expand(&line, minishell);
		minishell->exit_status = execute(line, minishell);
		free(line);
	}
	rl_clear_history();
}
