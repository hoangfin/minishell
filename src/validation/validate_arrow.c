/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 21:40:35 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/05 14:57:27 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include "constants.h"
#include "libft.h"

static const char	*get_next(const char *str)
{
	if (*(str + 1) == *str)
		str++;
	str++;
	while (*str != '\0' && ft_isspace(*str))
		str++;
	if (*str == '\0')
	{
		ft_fprintf(2, "%s `%s'\n", ERROR_SYNTAX, "newline");
		return (NULL);
	}
	if (*str == '>' || *str == '<')
	{
		ft_fprintf(2, "%s ", ERROR_SYNTAX);
		if (*(str + 1) == *str)
			ft_fprintf(2, "`%c%c'\n", *str, *str);
		else
			ft_fprintf(2, "`%c'\n", *str);
		return (NULL);
	}
	while (*str != '\0' && !ft_isspace(*str))
		str++;
	return (str);
}

int	has_valid_arrow(const char *str)
{
	const char	*next;

	while (*str != '\0' && *str != '>' && *str != '<')
		str++;
	if (*str == '\0')
		return (0);
	next = get_next(str);
	if (next == NULL)
		return (2);
	return (has_valid_arrow(next));
}
