/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 22:36:57 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/23 23:06:10 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_delimiter(const char *str, const char *dollar)
{
	char	*heredoc;
	size_t	length;

	length = ft_strlen(str);
	heredoc = ft_strnstr(str, "<<", length);
	if (heredoc == NULL || heredoc > dollar)
		return (false);
	while (*heredoc == '<' || ft_isspace(*heredoc))
		heredoc++;
	while (*heredoc != '\0' && !ft_isspace(*heredoc))
		heredoc++;
	if (heredoc > dollar)
		return (true);
	return (is_delimiter(heredoc, dollar));
}

static const char	*find_dollar_sign(const char *str)
{
	const char	*current = str;
	char		quote;

	quote = 0;
	while (*current != '\0')
	{
		if (*current == '\'' || *current == '"')
		{
			if (quote == 0)
				quote = *current;
			else if (quote == *current)
				quote = 0;
		}
		if (*current == '$' && !is_delimiter(str, current))
		{
			if (quote == 0 || quote == '"')
				return (current);
		}
		current++;
	}
	return (NULL);
}

static int	reduce(char **result, const char *str, t_minishell *minishell)
{
	const char	*dollar;
	const char	*value;
	int			i;

	dollar = find_dollar_sign(str);
	if (dollar == NULL)
	{
		if (ft_concat(result, str) < 0)
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
		if (ft_concat(result, value) < 0)
			return (-1);
	}
	return (reduce(result, &dollar[i], minishell));
}

int	expand(char **str, t_minishell *minishell)
{
	const char	*dollar;
	char		*result;

	dollar = find_dollar_sign(*str);
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
