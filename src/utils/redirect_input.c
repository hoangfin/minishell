/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:10:05 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/30 22:01:42 by hoatran          ###   ########.fr       */
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

static int	prompt_heredoc(int fd, const char *delimiter)
{
	char	buf[1024];
	ssize_t	bytes_read;

	while (1)
	{
		write(STDOUT_FILENO, HERE_DOC_PROMPT, 9);
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
		return (handle_error("read", strerror(errno)));
	// {
	// 	if (errno != EINTR)
	// 		ft_fprintf(2, "minishell: read: %s\n", strerror(errno));
	// 	return (-1);
	// }
	return (0);
}

// static int	install_signal_handlers(void)
// {
// 	struct sigaction	sigint_sa;
// 	struct sigaction	sigquit_sa;

// 	sigemptyset(&sigint_sa.sa_mask);
// 	sigint_sa.sa_handler = SIG_DFL;
// 	sigint_sa.sa_flags = 0;
// 	sigemptyset(&sigquit_sa.sa_mask);
// 	sigquit_sa.sa_handler = SIG_DFL;
// 	sigquit_sa.sa_flags = 0;
// 	if (
// 		sigaction(SIGINT, &sigint_sa, NULL) < 0
// 		|| sigaction(SIGQUIT, &sigquit_sa, NULL) < 0
// 	)
// 	{
// 		ft_fprintf(2, "minishell: sigaction: %s\n", strerror(errno));
// 		return (-1);
// 	}
// 	return (0);
// }

static int	heredoc(const char *delimiter)
{
	int	fd;

	// if (install_signal_handlers() < 0)
	// 	return (handle_error("sigaction", strerror(errno)));
	fd = open(HERE_DOC_TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (handle_error("open", strerror(errno)));
	if (prompt_heredoc(fd, delimiter) < 0)
	{
		close(fd);
		unlink(HERE_DOC_TEMP_FILE);
		return (-1);
	}
	if (close(fd) < 0)
		return (handle_error("close", strerror(errno)));
	fd = open(HERE_DOC_TEMP_FILE, O_RDONLY);
	if (fd < 0)
		return (handle_error("open", strerror(errno)));
	return (fd);
}

int	redirect_input(t_list *input_list)
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
			return (handle_error(io->token, strerror(errno)));
		if (dup2(fd, STDIN_FILENO) < 0)
			return (handle_error("dup2", strerror(errno)));
		if (close(fd) < 0)
			return (handle_error("close", strerror(errno)));
		node = node->next;
	}
	return (0);
}
