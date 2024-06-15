/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 23:10:16 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/15 21:18:55 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"
#include "constants.h"
#include "utils.h"
#include "io.h"

static int	get_heredoc_des(t_list *io_list, t_minishell *minishell)
{
	t_node	*node;
	t_io	*io;
	int		descriptor;

	descriptor = INT_MIN;
	node = io_list->head;
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

static void	set_io_des(t_io	*io, int heredoc_des, int *fd_in, int *fd_out)
{
	int	temp_in;
	int	temp_out;

	temp_in = INT_MIN;
	temp_out = INT_MIN;
	if (io->redi_type == REDIR_INPUT)
		temp_in = open(io->token, O_RDONLY);
	else if (io->redi_type == REDIR_HEREDOC)
		temp_in = heredoc_des;
	else if (io->redi_type == REDIR_OUTPUT)
		temp_out = open(io->token, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (io->redi_type == REDIR_APPEND)
		temp_out = open(io->token, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (temp_in != INT_MIN)
	{
		if (*fd_in >= 0)
			close(*fd_in);
		*fd_in = temp_in;
	}
	if (temp_out != INT_MIN)
	{
		if (*fd_out >= 0)
			close(*fd_out);
		*fd_out = temp_out;
	}
}

static int	redirect_pipe(int fd_in, int fd_out, int pipe_r, int pipe_w)
{
	if (fd_in >= 0)
	{
		if (dup2_close(fd_in, STDIN_FILENO) < 0)
			return (-1);
	}
	else if (pipe_r >= 0)
	{
		if (dup2(pipe_r, STDIN_FILENO) < 0)
			return (-1);
	}
	if (fd_out >= 0)
	{
		if (dup2_close(fd_out, STDOUT_FILENO) < 0)
			return (-1);
	}
	else if (pipe_w >= 0)
	{
		if (dup2(pipe_w, STDOUT_FILENO) < 0)
			return (-1);
	}
	return (0);
}

static int	redirect_stdio(
	t_list *io_list,
	int heredoc_des,
	int pipe_r,
	int pipe_w
)
{
	t_node	*node;
	int		fd_in;
	int		fd_out;
	t_io	*io;

	node = io_list->head;
	fd_in = INT_MIN;
	fd_out = INT_MIN;
	while (node != NULL)
	{
		io = (t_io *)node->data;
		set_io_des(io, heredoc_des, &fd_in, &fd_out);
		if (fd_in == -1 || fd_out == -1)
		{
			if (errno != EINTR)
				ft_fprintf(2, "minishell: %s: %s\n",
					io->token, strerror(errno));
			return (-1);
		}
		node = node->next;
	}
	if (redirect_pipe(fd_in, fd_out, pipe_r, pipe_w) < 0)
		return (-1);
	return (0);
}

int	redirect(t_list *io_list, int pipe_r, int pipe_w, t_minishell *minishell)
{
	int	status;
	int	heredoc_des;

	status = 0;
	heredoc_des = get_heredoc_des(io_list, minishell);
	if (heredoc_des == -1)
		status = -1;
	if (status == 0)
		status = redirect_stdio(io_list, heredoc_des, pipe_r, pipe_w);
	if (pipe_r >= 0)
	{
		if (close(pipe_r) < 0)
			status = -1;
	}
	if (pipe_w >= 0)
	{
		if (close(pipe_w) < 0)
			status = -1;
	}
	return (status);
}
