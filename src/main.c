/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:31:20 by mito              #+#    #+#             */
/*   Updated: 2024/05/07 17:47:40 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	buf[1024];
	ssize_t	bytes_read;

	write(STDOUT_FILENO, "minishell > ", 12);
	bytes_read = read(STDIN_FILENO, buf, 1024);
	printf("Just behind first read\n");
	while (bytes_read > 0)
	{
		//Do something here
		write(STDOUT_FILENO, "minishell > ", 12);
		bytes_read = read(STDIN_FILENO, buf, 1024);
		printf("Just behind read in while loop\n");
	}
	return (EXIT_SUCCESS);
}