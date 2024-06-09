/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:49:03 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/09 17:56:54 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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

static int	read_inputs(int fd, const char *delimiter, t_bool should_expand, t_minishell *minishell)
{
	char	*line;
	size_t	length;

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		if (get_next_line(STDIN_FILENO, &line) < 0)
			return (-1);
		if (line == NULL)
			return (0);
		length = ft_strlen(line);
		if (
			(length - 1) == ft_strlen(delimiter)
			&& ft_strncmp(line, delimiter, length - 1) == 0
		)
		{
			free(line);
			return (0);
		}
		if (should_expand == true)
		{
			if (heredoc_expand(&line, minishell) < 0)
				return (free(line), -1);
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
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
	t_bool	should_expand;
	int		fd;

	should_expand = true;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
	{
		ft_remove_quote_pair(delimiter);
		should_expand = false;
	}
	if (
		set_signal_handler(SIGINT, newline_handler) < 0
		|| set_signal_handler(SIGQUIT, SIG_IGN) < 0
	)
		return (-1);
	fd = open(HERE_DOC_TEMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (read_inputs(fd, delimiter, should_expand, minishell) < 0)
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
