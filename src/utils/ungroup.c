/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ungroup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:02:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/07 15:11:35 by hoatran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	init(int *i, int *j, int *depth)
{
	*i = 0;
	*j = 0;
	*depth = 0;
}

void	ungroup(char *str)
{
	int	i;
	int	j;
	int	depth;

	init(&i, &j, &depth);
	while (str[i] != '\0')
	{
		if (str[i] == '(')
		{
			if (depth != 0)
				str[j++] = str[i];
			depth++;
		}
		else if (str[i] == ')')
		{
			depth--;
			if (depth != 0)
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}
