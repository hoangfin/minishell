/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirect_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:37:37 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/15 17:34:05 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*get_operator(const char *str)
{
	char	quote;

	quote = 0;
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
		{
			if (quote == 0)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		if ((*str == '<' || *str == '>') && quote == 0)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

/**
 * Return redirection operator `<` or `>` in the given string, skipping all
 * operators that are inside `'` or `"`.
*/
void	find_redirect_op(const char *str, char **start, char **end)
{
	*start = NULL;
	*end = NULL;
	*start = get_operator(str);
	if (*start == NULL)
		return ;
	*end = *start;
	while (**end != '\0' && (**end == **start || ft_isspace(**end)))
		(*end)++;
	if (**end == '\0')
		return ;
	while (**end != '\0' && !ft_isspace(**end))
	{
		if (**end == '\'' || **end == '"')
		{
			*end = ft_strchr(*end + 1, **end);
			if (*end == NULL)
				return ;
		}
		(*end)++;
	}
}
