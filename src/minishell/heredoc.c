/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:49:03 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/25 16:04:32 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "minishell.h"
#include "utils.h"
#include "constants.h"
#include "minishell_signal.h"

static int	reduce(char **result, const char *str, t_minishell *minishell)
{
	const char	*dollar;
	const char	*value;
	int			i;

	dollar = ft_strchr(str, '$');
	if (dollar == NULL)
	{
		if (ft_concat(result, 1, str) < 0)
			return (-1);
		return (0);
	}
	i = 1;
	while (
		dollar[i] != '\0' && !ft_isspace(dollar[i])
		&& dollar[i] != '"' && dollar[i] != '\''
	)
		i++;
	value = resolve_env(&dollar[1], i - 1, minishell);
	if (value != NULL)
	{
		if (ft_concat(result, 1, value) < 0)
			return (-1);
	}
	return (reduce(result, &dollar[i], minishell));
}

static int	heredoc_expand(char **str, t_minishell *minishell)
{
	const char	*dollar;
	char		*result;

	dollar = ft_strchr(*str, '$');
	if (dollar == NULL)
		return (0);
	result = ft_substr(*str, 0, dollar - (*str));
	if (result == NULL)
		return (-1);
	if (reduce(&result, dollar, minishell) < 0)
	{
		free(result);
		return (-1);
	}
	if (result != NULL)
	{
		free(*str);
		*str = result;
	}
	return (0);
}

static int	get_input(
	int fd,
	const char *delimiter,
	t_minishell *minishell,
	t_bool should_expand_dollar
)
{
	char	*line;

	while (1)
	{
		line = ft_readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line), 0);
		if (should_expand_dollar == true)
		{
			if (heredoc_expand(&line, minishell) < 0)
				return (free(line), -1);
		}
		ft_fprintf(fd, "%s\n", line);
		free(line);
	}
	if (errno)
		return (-1);
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
 * Set signal handlers for `SIGINT` and `SIGQUIT`, then read inputs from
 * `STDIN_FILENO`.
 *
 * @returns On success, the read-only file descriptor (a nonnegative integer)
 * 			of `HERE_DOC_TEMP_FILE` is returned. On error, -1 is returned and
 * 			errno is set to indicate the error.
*/
int	heredoc(char *delimiter, t_minishell *minishell)
{
	t_bool	should_expand_dollar;
	int		fd;

	if (set_signal_handler(SIGINT, sigint_handler_heredoc) < 0
		|| set_signal_handler(SIGQUIT, SIG_IGN) < 0)
		return (-1);
	should_expand_dollar = true;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		should_expand_dollar = false;
	ft_remove_quote_pair(delimiter);
	fd = open(HERE_DOC_TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (get_input(fd, delimiter, minishell, should_expand_dollar) < 0)
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
