/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_str_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:53:10 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/17 19:03:51 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	count_str_array(const char **str_array)
{
	int	i;

	if (str_array == NULL)
		return (0);
	i = 0;
	while (str_array[i])
		i++;
	return (i);
}
