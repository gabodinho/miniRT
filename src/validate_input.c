#include <fcntl.h>  // For open
#include <unistd.h> // For close
#include <string.h> // For strcmp
#include <stdio.h>  // For perror

// Function to check if the file exists and is of correct format
int validate_input_file(char *filename)
{
    int fd;
    size_t len = strlen(filename);

    // Check if the filename ends with ".rt"
    if (len < 3 || strcmp(filename + len - 3, ".rt") != 0)
    {
        printf("Error: Invalid file extension. Expected .rt file.\n");
        return 1;
    }

    // Try to open the file
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 2;
    }

    // If the file opens correctly, close it
    close(fd);

    // If everything is correct, return 0 (success)
    return 0;
}

