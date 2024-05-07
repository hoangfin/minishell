#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <dirent.h>
# include <termios.h>
# include <signal.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>

typedef struct s_minishell
{
	char	**envp;
	char	**path;
}	t_minishell;

// when flag is false, echo() print with newline.
void	ft_echo(const char *str, t_bool flag);
// ◦ cd with only a relative or absolute path
void	ft_pwd(void); //??? opendir, readdir, closedir
void	ft_export(const char *env_var);
void	ft_unset(const char *env_var_key);
void	ft_env(void);
void	ft_exit(void);

#endif