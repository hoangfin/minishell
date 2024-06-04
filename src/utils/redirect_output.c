/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:10:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/03 18:04:55 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "utils.h"
#include "io.h"

static int	handle_error(const char *err_src, const char *err_msg)
{
	ft_fprintf(\
		STDERR_FILENO, \
		"minishell: %s: %s\n", \
		err_src, \
		err_msg \
	);
	return (-1);
}

/**
 * Redirect STDOUT_FILENO to the last file descriptor in the provided
 * linked list.
 *
 * @param output_list The pointer to a linked list in which each
 * 					  list node data is a `t_io *` pointer.
 *
 * @returns	On success, `0` is returned. On error, -1 is returned, and
 * 			`errno` is set to indicate the error.
 *
*/
int	redirect_output(t_list *output_list, int pipedes)
{
	t_node	*node;
	t_io	*io;
	int		fd;

	node = output_list->head;
	while (node != NULL)
	{
		io = (t_io *)node->data;
		if (io->redi_type == REDIR_OUTPUT)
			fd = open(io->token, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (io->redi_type == REDIR_APPEND)
			fd = open(io->token, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (handle_error(io->token, strerror(errno)));
		if (dup2_close(fd, STDOUT_FILENO) < 0)
			return (-1);
		node = node->next;
	}
	if (pipedes >= 0)
	{
		if (dup2_close(pipedes, STDOUT_FILENO) < 0)
			return (-1);
	}
	return (0);
}
