#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

void list_open_fds(pid_t pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/fd/", pid);
    
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            printf("FD: %s\n", entry->d_name);
        }
    }
    
    closedir(dir);
}

int main() {
    pid_t pid = getpid(); // Get the current process ID
    printf("Current process ID: %d\n", pid);
    printf("Open file descriptors:\n");
    list_open_fds(pid);
    return 0;
}