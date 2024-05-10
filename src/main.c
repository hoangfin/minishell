/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:31:20 by mito              #+#    #+#             */
/*   Updated: 2024/05/09 01:06:30 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	char		*line;

	(void)argc;
	(void)argv;
	if (init_minishell(&minishell, envp) < 0)
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		// if (bytes_read <= 0)
		// {
		// 	printf("bytes_read <= 0\n");
		// 	break ;
		// }
		// if (ft_strncmp(buf, "sleep", 5) == 0)
		// 	sleep(5);
		// if (buf[bytes_read - 1] != '\n')
		// 	write(1, "\n", 1);
		// printf("bytes_read = %ld\n", bytes_read);
		// write(1, buf, bytes_read);
	}
	clean_up(&minishell);
	return (EXIT_SUCCESS);
}