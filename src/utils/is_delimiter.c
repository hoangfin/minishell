/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 21:08:45 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/13 21:09:11 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	is_delimiter(const char *str, const char *dollar)
{
	char	*start;
	char	*end;

	start = find_symbol(str, "<<");
	if (start == NULL)
		return (false);
	end = start;
	while (*end != '\0' && (*end == '<' || ft_isspace(*end)))
		end++;
	if (*end == '\0')
		return (false);
	while (*end != '\0' && !ft_isspace(*end))
		end++;
	if (dollar > start && dollar < end)
		return (true);
	return (is_delimiter(end, dollar));
}
