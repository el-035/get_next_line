#include "get_next_line.h"
#include <fcntl.h> //
#include <stdio.h> //
#include <stdlib.h>
#include <unistd.h>

static char	*saveline(char *buffer)
{
	char	*temp;
	size_t	len;

	len = 0;
	if (*buffer == 0)
		return (NULL);
	buffer = ft_strchr(buffer, '\n') + 1;
	while (buffer[len])
		len++;
	temp = (char *) malloc((len + 1) * sizeof(char));
	if (!temp)
		return (free(temp), NULL);
	temp[len] = '\0';
	while (len-- > 0)
		temp[len] = buffer[len];
	return (temp);
}
char	*found_nl_temp(char **temp, char **line, char *buffer)
{
	char *temp_free;

	temp_free = NULL; //here I changed
	temp_free = saveline (*temp);
	if (!temp_free)
		return (free (buffer), free (line), NULL);
	*line = free_join(*line, *temp);
	if (!*line)
		return (free(buffer), NULL);
	*temp = free_join(*temp, temp_free);
	free (temp_free);
	if (!*temp)
		return (free(*line), free (buffer), NULL);
	return (free (buffer), *line);
}

char	*found_nl_buf(char **temp, char **line, char *buffer, int bytes)
{
	if (bytes == 0)
	{
		*line = free_join(*line, *temp);
		if (!*line)
				return (free(*line), NULL); //free buffer too
		return (free (*temp), *temp = NULL, free (buffer), *line);
	}
	else
	{
		*line = free_join(*line, *temp);
		if (!*line)
			return (free(*temp), free(buffer), NULL);
		free (*temp);
		*temp = saveline(buffer);
		if (!*temp)
			return (free(*line), free (buffer), NULL);
		return (free (buffer), *line);
	}
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			bytes;
	static char	*temp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	line = NULL;
	bytes = 1;
	if (ft_strchr(temp, '\n'))
		return (found_nl_temp(&temp, &line, buffer));
	while (bytes != 0 && (!ft_strchr(buffer, '\n')))
	{	
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free (buffer), NULL);
		if (bytes == 0)
			break ;
		temp = free_join(temp, buffer);
		if (!temp)
			return (free(buffer), NULL);
	}
	if (ft_strchr(buffer, '\n') || (bytes == 0 && temp))
		return (found_nl_buf(&temp, &line, buffer, bytes));
	return (free (temp), temp = NULL, free (buffer), line);
}

int main()
{
    char    *line = "";
    int fd;

    fd = open("nl.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
    while (line)
    {
        free(line);
		line = get_next_line(fd);
		printf("%s", line);
    }
    close(fd);
    return 0;
}