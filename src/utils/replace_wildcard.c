/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:55:01 by mito              #+#    #+#             */
/*   Updated: 2024/06/08 16:20:59 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include "utils.h"

static t_bool	is_match(const char *glob_pattern, const char *filename)
{
	char	*next;
	char	*match;

	while (*glob_pattern != '\0' && *glob_pattern == '*')
		glob_pattern++;
	if (*glob_pattern == '\0')
		return (true);
	next = ft_strchr(glob_pattern, '*');
	if (next == NULL)
	{
		match = ft_strnstr(filename, glob_pattern, ft_strlen(glob_pattern));
		if (match == NULL)
			return (false);
		if (ft_strlen(match) == ft_strlen(glob_pattern))
			return (true);
		return (false);
	}
	match = ft_strnstr(filename, glob_pattern, next - glob_pattern);
	if (match == NULL)
		return (false);
	return (is_match(next + 1, match + (next - glob_pattern)));
}

static int concat(char **result, const char *str)
{
	if (*result == NULL)
	{
		if (ft_concat(result, 1, str) < 0)
			return (perror("minishell: malloc"), -1);
	}
	else
	{
		if (ft_concat(result, 2, " ", str) < 0)
		{
			perror("minishell: malloc");
			free(*result);
			*result = NULL;
			return (-1);
		}
	}
	return (0);
}

/**
 * If an error occurs, NULL is returned and errno is set to indicate the
 * error. To distinguish end of stream from an error, set errno to zero before
 * calling readdir() and then check the value of errno if NULL is returned.
*/
static int	fill(char **result, DIR *dir, const char *glob_pattern)
{
	struct dirent	*entry;

	errno = 0;
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (is_match(glob_pattern, entry->d_name))
		{
			if (concat(result, entry->d_name) < 0)
				return (-1);
		}
	}
	if (errno)
	{
		perror("minishell: readdir");
		free(*result);
		*result = NULL;
		return (-1);
	}
	return (0);
}

static int	get_match(char **result, const char *glob_pattern)
{
	char	buffer[1024];
	DIR		*dir;

	*result = NULL;
	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (perror("minishell: getcwd"), -1);
	dir = opendir(buffer);
	if (dir == NULL)
		return (perror("minishell: opendir"), -1);
	if (fill(result, dir, glob_pattern) < 0)
		return (-1);
	if (closedir(dir) < 0)
	{
		perror("minishell: closedir");
		free(*result);
		*result = NULL;
		return (-1);
	}
	return (0);
}

/**
 * Check if a given string has wildcard and replace string with new one that
 * satisfies wildcard pattern.
 *
 * If no match content is found, this function does not update the given string.
 *
*/
int	replace_wildcard(char **str)
{
	char	*result;

	if (ft_strchr(*str, '*') == NULL)
		return (0);
	if (get_match(&result, *str) < 0)
		return (-1);
	if (result == NULL)
		return (0);
	free(*str);
	*str = result;
	return (0);
}
