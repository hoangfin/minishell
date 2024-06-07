/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:10:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/07 14:40:35 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "constants.h"
#include "utils.h"
#include "io.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell_signal.h"

static int	prompt_heredoc(int fd, const char *delimiter)
{
	char	buf[1024];
	ssize_t	bytes_read;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, buf, 1023);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		if (
			(size_t)bytes_read - 1 == ft_strlen(delimiter)
			&& ft_strncmp(buf, delimiter, (size_t)bytes_read - 1) == 0
		)
			break ;
		write(fd, buf, ft_strlen(buf));
	}
	if (bytes_read < 0)
		return (-1);
	return (0);
}

static int	heredoc(const char *delimiter)
{
	int	fd;

	if (
		set_signal_handler(SIGINT, newline_handler) < 0
		|| set_signal_handler(SIGQUIT, SIG_IGN) < 0
	)
		return (-1);
	fd = open(HERE_DOC_TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (prompt_heredoc(fd, delimiter) < 0)
	{
		close(fd);
		unlink(HERE_DOC_TEMP_FILE);
		return (-1);
	}
	if (close(fd) < 0)
		return (-1);
	fd = open(HERE_DOC_TEMP_FILE, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

static int	redirect_stdin(t_list *input_list)
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
			fd = heredoc(io->token);
		if (fd < 0)
		{
			if (errno != EINTR)
				ft_fprintf(
					2, "minishell: %s: %s\n", io->token, strerror(errno) \
				);
			return (-1);
		}
		if (dup2_close(fd, STDIN_FILENO) < 0)
			return (-1);
		node = node->next;
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
int	redirect_input(t_list *input_list, int pipedes)
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
	if (redirect_stdin(input_list) < 0)
		return (-1);
	return (0);
}
