/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_param_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:45:46 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/25 14:46:37 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	is_delimiter(const char *str, const char *dollar)
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

const char	*find_param_exp(const char *str)
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
