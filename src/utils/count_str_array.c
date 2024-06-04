/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_str_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:53:10 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/02 22:59:25 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	count_str_array(const char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
		i++;
	return (i);
}