/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ungroup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoatran <hoatran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:02:11 by hoatran           #+#    #+#             */
/*   Updated: 2024/06/13 00:34:33 by hoatran          ###   ########.fr       */
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
	char	quote;
	int		i;
	int		j;
	int		depth;

	quote = 0;
	init(&i, &j, &depth);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (quote == 0)
				quote = str[i];
			else if (quote == str[i])
				quote = 0;
		}
		if (str[i] == '(' && quote == 0)
		{
			if (depth != 0)
				str[j++] = str[i];
			depth++;
		}
		else if (str[i] == ')' && quote == 0)
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
