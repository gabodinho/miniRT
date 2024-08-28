#include "../libft/libft/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>  // For free()

int read_scene_file(char *filename)
{
    int fd;
    char *line;

    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return 2;
    }

    // Read the file line by line using get_next_line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Read line: %s\n", line);
        free(line);  // Free the memory allocated by get_next_line
    }

    // Close the file descriptor
    close(fd);
    return 0;
}

