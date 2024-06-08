#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

char* list_files_and_directories(const char* path) {
    DIR *dir;
    struct dirent *entry;
    size_t size = 1024;
    char *result = malloc(size);
    if (!result) {
        perror("malloc");
        return NULL;
    }
    result[0] = '\0';  // Initialize the string

    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        free(result);
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        size_t len = strlen(entry->d_name) + 2;  // +2 for space and null terminator
        if (strlen(result) + len > size) {
            size *= 2;
            char *temp = realloc(result, size);
            if (!temp) {
                perror("realloc");
                free(result);
                closedir(dir);
                return NULL;
            }
            result = temp;
        }
        strcat(result, entry->d_name);
        strcat(result, " ");
    }
    closedir(dir);
    return result;
}

int main(void) {
    char *files = list_files_and_directories(".");
    if (files) {
        printf("Files and directories:\n%s\n", files);
        free(files);
    }
    return 0;
}
