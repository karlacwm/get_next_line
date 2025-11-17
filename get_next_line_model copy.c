#include "get_next_line.h"

// This function is unchanged
static char *extract_line(char *remaining)
{
    int     i;
    char    *line;

    i = 0;
    if (!remaining || !remaining[i]) // Protects against NULL or ""
        return (NULL);
    while (remaining[i] && remaining[i] != '\n')
        i++;
    if (remaining[i] == '\n')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 1));
    if (!line)
        return (NULL);
    ft_memcpy(line, remaining, i);
    line[i] = '\0';
    return (line);
}

// This function is unchanged, it looks correct.
static char *update_remaining(char *remaining)
{
    int     i;
    char    *updated;

    if (!remaining)
        return (NULL);
    i = 0;
    while (remaining[i] && remaining[i] != '\n')
        i++;
    // If no '\n' was found (remaining[i] is '\0')
    // OR if the '\n' is the very last char (remaining[i+1] is '\0')
    // Then there is no remainder.
    if (!remaining[i] || !remaining[i + 1])
    {
        free(remaining);
        return (NULL);
    }
    // Otherwise, copy from the char *after* the '\n'
    updated = ft_strdup(&remaining[i + 1]);
    free(remaining);
    return (updated);
}

/*
** NEW HELPER FUNCTION to fix norminette
** This function reads from the file descriptor and joins the buffer to
** the 'remaining' string until a newline is found or EOF is reached.
*/
static char *read_and_join(int fd, char *remaining)
{
    char    *read_buffer;
    int     bytes_read;

    read_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!read_buffer)
    {
        free(remaining); // Free remaining if malloc fails
        return (NULL);
    }
    bytes_read = 1;
    while (bytes_read > 0 && !ft_strchr(remaining, '\n'))
    {
        bytes_read = read(fd, read_buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(read_buffer);
            free(remaining); // Free remaining on read error
            return (NULL);
        }
        read_buffer[bytes_read] = '\0';
        remaining = ft_strjoin(remaining, read_buffer); // Assumes ft_strjoin frees old 'remaining'
        if (!remaining)
        {
            free(read_buffer);
            return (NULL);
        }
    }
    free(read_buffer);
    return (remaining); // Return the (potentially) new 'remaining'
}

/*
** REFACTORED main function (now < 25 lines)
*/
char    *get_next_line(int fd)
{
    static char *remaining = NULL;
    char        *return_line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    // Call the helper to read and update 'remaining'
    remaining = read_and_join(fd, remaining);

    // If read_and_join failed or returned NULL:
    if (!remaining)
        return (NULL);

    // This check is now safer.
    // If 'remaining' is just an empty string "", extract_line
    // will correctly handle it (returning NULL or "" depending on your impl.)
    // But if it's empty, we should stop.
    if (remaining[0] == '\0')
    {
        free(remaining);
        remaining = NULL;
        return (NULL);
    }

    // Extract the line from 'remaining'
    return_line = extract_line(remaining);

    // If extract_line failed (e.g., malloc error), free 'remaining'
    if (!return_line)
    {
        free(remaining);
        remaining = NULL;
        return (NULL);
    }

    // Update 'remaining' to hold only the part *after* the extracted line
    remaining = update_remaining(remaining);

    return (return_line);
}
