/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_ampersand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:13:02 by mito              #+#    #+#             */
/*   Updated: 2024/06/14 13:21:09 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "constants.h"
#include "libft.h"
#include "utils.h"

static const char	*get_next(const char *str)
{
	if (*(str + 1) != *str)
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "&"), NULL);
	str = str + 2;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '\0')
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "&&"), NULL);
	if (*str == '&')
		return (ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "&&"), NULL);
	while (*str != '\0' && !ft_isspace(*str))
		str++;
	return (str);
}

// int	has_valid_ampersand(const char *str)
// {
// 	const char	*next;

// 	while (*str != '\0' && *str != '&')
// 		str++;
// 	if (*str == '\0')
// 		return (0);
// 	next = get_next(str);
// 	if (next == NULL)
// 		return (2);
// 	return (has_valid_arrow(next));
// }

int	has_valid_ampersand(const char *str)
{
	const char	*symbol;
	const char	*next;

	symbol = find_symbol(str, "&");
	if (symbol == NULL)
		return (0);
	next = get_next(symbol);
	if (next == NULL)
		return (2);
	return (has_valid_arrow(next));
}
