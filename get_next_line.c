#include "get_next_line.h"
#include <fcntl.h> //
#include <stdio.h> //
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static char	*saveline(char *buffer)
{
	char	*temp;
	size_t	len;
	char	*nl;

	len = 0;
	if (!buffer)
		return (NULL);
	nl = ft_strchr(buffer, '\n') + 1;
	while (nl[len])
		len++;
	temp = (char *) malloc((len + 1) * sizeof(char));
	if (!temp)
		return (free(temp), NULL);
	temp[len] = '\0';
	while (len-- > 0)
		temp[len] = nl[len];
	return (temp);
}

char	*found_nl_temp(char **temp, char **line, char *buffer)
{
	char *temp_free;

	temp_free = NULL; 
	temp_free = saveline (*temp); //here I changed
	if (!temp_free)
		return (free (buffer), free (line), NULL);
	*line = free_join(*line, *temp);
	if (!*line)
		return (free(buffer), NULL);
	free (*temp);
	*temp = ft_strdup(temp_free);
	free (temp_free);
	if (!*temp)
		return (free(*line), free (buffer), NULL);
	return (free (buffer), *line);
}

char	*helper(char **temp, char **line, char *buffer, int bytes)
{
	if (bytes == 0)
	{
		*line = free_join(*line, *temp);
		if (!*line)
				return (free(*line), NULL); //free buffer to
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
		ft_bzero((void *)buffer, BUFFER_SIZE);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free (buffer), NULL);
		if (bytes == 0)
			break ;
		temp = free_join(temp, buffer);
		if (!temp)
			return (NULL);
	}
	if (ft_strchr(buffer, '\n') || (bytes == 0 && temp))
		return (helper(&temp, &line, buffer, bytes));
	return (free (temp), temp = NULL, free (buffer), line);
}

/*int main()
{
    char    *line = "";
    int fd;

    fd = open("alternate_line_nl_no_nl.txt", O_RDONLY);
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
}*/
