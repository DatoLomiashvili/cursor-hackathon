#include <unistd.h>
#include <stdlib.h>
#include <string.h>

static char *ft_strchr_gnl(const char *s, int c)
{
    if (!s)
        return NULL;
    while (*s)
    {
        if (*s == c)
            return (char *)s;
        s++;
    }
    if (c == '\0')
        return (char *)s;
    return NULL;
}

static char *ft_strjoin_gnl(char *s1, char *s2)
{
    char *result;
    int i, j;

    if (!s1 && !s2)
        return NULL;
    if (!s1)
        s1 = strdup("");
    if (!s2)
        s2 = strdup("");
    
    result = malloc(strlen(s1) + strlen(s2) + 1);
    if (!result)
        return NULL;
    
    i = 0;
    while (s1[i])
    {
        result[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
        result[i++] = s2[j++];
    result[i] = '\0';
    
    free(s1);
    return result;
}

int get_next_line(int fd, char **line)
{
    static char *buffer = NULL;
    char temp[1024];
    char *newline_pos;
    char *temp_line;
    int bytes_read;

    if (fd < 0 || !line)
        return -1;

    if (!buffer)
        buffer = strdup("");

    while (1)
    {
        newline_pos = ft_strchr_gnl(buffer, '\n');
        if (newline_pos)
        {
            *newline_pos = '\0';
            *line = strdup(buffer);
            temp_line = strdup(newline_pos + 1);
            free(buffer);
            buffer = temp_line;
            return 1;
        }

        bytes_read = read(fd, temp, 1023);
        if (bytes_read <= 0)
        {
            if (strlen(buffer) > 0)
            {
                *line = strdup(buffer);
                free(buffer);
                buffer = NULL;
                return 1;
            }
            free(buffer);
            buffer = NULL;
            return bytes_read;
        }

        temp[bytes_read] = '\0';
        buffer = ft_strjoin_gnl(buffer, temp);
    }
}

