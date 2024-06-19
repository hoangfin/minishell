#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

// Signal handler for SIGINT
void handle_sigint(int sig) {
    // Just print a message and return; readline() will handle the rest
    printf("\nCaught SIGINT (Ctrl+C), type 'exit' to quit.\n");
}

int main() {
    char *line;

    // Set up the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    while (1) {
        line = readline("> ");

        // Check if readline() returned NULL
        if (line == NULL) {
            // If readline() returns NULL, it could be due to EOF or SIGINT
            printf("\nreadline returned NULL, exiting.\n");
            break;
        }

        // If the input line is not empty, add it to the history
        if (*line) {
            add_history(line);
        }

        // Process the input line
        printf("You entered: %s\n", line);

        // Free the allocated line buffer
        free(line);
    }

    return 0;
}
