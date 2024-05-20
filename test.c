#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>

sig_atomic_t is_heredoc = 0;


void handle_sigint(int sig) {
    is_heredoc = 0;
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0; // No special flags
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    char buf[100];
	char *line;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
		if (strncmp(line, "heredoc", 7) == 0)
		{
			is_heredoc = 1;
			while (is_heredoc) {
				write(1, "heredoc> ", 9);
				ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
				if (n == -1) {
					if (errno == EINTR && !is_heredoc) {
						// Interrupted by signal
						printf("\n");
						break ;
					}
					perror("read()");
					exit(EXIT_FAILURE);
				} else if (n > 0) {
					buf[n] = '\0';
					printf("Read: %s\n", buf);
				}
			}
		}
		free(line);
	}
    return 0;
}
