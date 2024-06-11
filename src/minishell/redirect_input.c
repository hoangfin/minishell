/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:10:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/11 15:33:45 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "constants.h"
#include "utils.h"
#include "io.h"

static int	get_heredoc_descriptor(t_list *input_list, t_minishell *minishell)
{
	t_node	*node;
	t_io	*io;
	int		descriptor;

	descriptor = INT_MIN;
	node = input_list->head;
	while (node != NULL)
	{
		io = (t_io *)node->data;
		if (io->redi_type == REDIR_HEREDOC)
			descriptor = heredoc(io->token, minishell);
		if (descriptor == -1)
			return (-1);
		node = node->next;
	}
	return (descriptor);
}

static int	get_input_descriptor(t_list *input_list, int heredoc_des)
{
	t_node	*node;
	t_io	*io;
	int		fd;

	node = input_list->head;
	while (node != NULL)
	{
		io = (t_io *)node->data;
		if (io->redi_type == REDIR_INPUT)
			fd = open(io->token, O_RDONLY);
		else if (io->redi_type == REDIR_HEREDOC)
			fd = heredoc_des;
		if (fd == -1)
		{
			ft_fprintf(2, "minishell: %s: %s\n", io->token, strerror(errno));
			return (-1);
		}
		node = node->next;
	}
	return (fd);
}

static int	redirect_stdin(t_list *input_list, t_minishell *minishell)
{
	int		fd;
	int		heredoc_des;

	fd = INT_MIN;
	heredoc_des = get_heredoc_descriptor(input_list, minishell);
	if (heredoc_des == -1)
		return (-1);
	fd = get_input_descriptor(input_list, heredoc_des);
	if (fd == -1)
		return (-1);
	if (fd != INT_MIN)
	{
		if (dup2_close(fd, STDIN_FILENO) < 0)
			return (-1);
	}
	return (0);
}

/**
 * Redirect STDIN_FILENO to the last file descriptor in the provided
 * linked list.
 *
 * @param input_list The pointer to a linked list in which each
 * 					 list node data is a `t_io *` pointer.
 *
 * @returns	On success, `0` is returned. On error, -1 is returned, and
 * 			`errno` is set to indicate the error.
 *
*/
int	redirect_input(t_list *input_list, int pipedes, t_minishell *minishell)
{
	if (input_list->length == 0)
	{
		if (pipedes < 0)
			return (0);
		if (dup2_close(pipedes, STDIN_FILENO) < 0)
			return (-1);
		return (0);
	}
	if (pipedes >= 0)
	{
		if (close(pipedes) < 0)
			return (-1);
	}
	if (redirect_stdin(input_list, minishell) < 0)
		return (-1);
	return (0);
}
