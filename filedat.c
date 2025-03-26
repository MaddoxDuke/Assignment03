#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void execute_command(char *command, char *filename) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execlp(command, command, filename, NULL);
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else {
        int status;
        wait(&status);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *filename = argv[1];
    int choice;
    
    while (1) {
        printf("File: %s\n", filename);
        printf("Menu:\n");
        printf("1. List contents of file (cat)\n");
        printf("2. Print newline, word, and character count (wc)\n");
        printf("3. Print directory details (ls -l)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Exiting.\n");
            exit(EXIT_FAILURE);
        }

        while (getchar() != '\n');  // Clear input buffer

        switch (choice) {
            case 1:
                execute_command("cat", filename);
                break;
            case 2:
                execute_command("wc", filename);
                break;
            case 3:
                execute_command("ls", "-l");
                execute_command("ls", filename);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
