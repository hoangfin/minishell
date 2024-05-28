/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_logical_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:28:06 by hoatran           #+#    #+#             */
/*   Updated: 2024/05/25 14:49:49 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

const char	*find_logical_op(const char *str)
{
	int	depth;

	depth = 0;
	while (*str != '\0')
	{
		if (*str == '(')
			depth++;
		if (*str == ')')
			depth--;
		if (*str == '&' && *(str + 1) == '&' && depth == 0)
			return (str);
		if (*str == '|' && *(str + 1) == '|' && depth == 0)
			return (str);
		str++;
	}
	return (NULL);
}
