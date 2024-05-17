/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mito <mito@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:02:39 by mito              #+#    #+#             */
/*   Updated: 2024/05/13 16:14:35 by mito             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// We don't handle these cases: ~ -> it goes to Home, - -> one back
// no arg  -> it goes to Home
// .. -> one back
// otherwise go to the path that is given

static char	*ft_getenv(const char *key, char **envp) // this is from Hoang's libft
{
	size_t	length;
	char	*temp;

	length = ft_strlen(key);
	while (envp != NULL && *envp != NULL)
	{
		if (ft_strncmp(*envp, key, length) == 0)
		{
			temp = ft_strchr(*envp, '=');
			if (temp == NULL)
				return (NULL);
			return (ft_strdup(temp + 1));
		}
		envp++;
	}
	return (NULL);
}

static int go_to_home(t_minishell *minishell)
{
	char *env_path;

	env_path = ft_getenv("HOME", minishell->path);
	if (chdir(env_path) == -1) //go to HOME
			return (-1);
	return (0);
}
int ft_cd(t_command *cmd, t_list *env_list)
{
	if (count_arguments(cmd) > 2) // if there are more than 2 then it's invalid
	{
		ft_fprintf(STDERR_FILENO, "%s%s\n", cmd->argv[0], ": too many arguments");
		return (1);
	}
    if (!cmd->argv[1]) // if there is no argment it means it is just "cd".
	{
        if (go_to_home(env_list) < 0) //go to HOME
		{
			ft_fprintf(STDERR_FILENO, "%s%s\n", cmd->argv[0], ": HOME not set");
			// if we unset HOME. Are there any other reason it fails?
			return (1);
		}
	}
    else
    {
        if (chdir(cmd->argv[1]) == -1) //argv[1] is a path
            return (1);
    }
    return (0);
}

