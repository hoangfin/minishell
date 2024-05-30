/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:10:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/30 18:13:18 by hoatran          ###   ########.fr       */
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

int	redirect_output(t_list *output_list)
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
		else if (io->redi_type == REDIR_PIPE)
			fd = io->pipedes;
		if (fd < 0)
			return (handle_error(io->token, strerror(errno)));
		if (dup2(fd, STDOUT_FILENO) < 0)
			return (handle_error("dup2", strerror(errno)));
		if (close(fd) < 0)
			return (handle_error("close", strerror(errno)));
		node = node->next;
	}
	return (0);
}
