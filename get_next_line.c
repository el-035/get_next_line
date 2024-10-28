#include "get_next_line.h"

#include <stdio.h> //to be deleted
#include <fcntl.h> //to be deleted
#include <string.h>

//step 1
char	*read_content(int fd, char *temp)
{
	char		*buffer;
	int			bytes;

	bytes = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(temp), NULL);
	ft_bzero(buffer, (BUFFER_SIZE + 1));
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), /* free(temp), */ NULL);
		buffer[bytes] = '\0';
		if (bytes == 0)
			break;
		temp = ft_strjoin(temp, buffer);
		if (!temp)
			return (free(buffer), NULL);
	}
	if(!temp || (temp && !*temp))
		return(free(buffer), free(temp), NULL);
	return (free(buffer), temp);
}

//step 2
char	*current_line(char *temp)
{
	int		i;
	char	*line;
	int		len;

	line = NULL;
	i = -1;
	len = 0;
	while (temp[len] && temp[len] != '\n')
		len++;
	if (temp[len] == '\n')
		len++;
	line = (char *) malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_bzero(line, (len + 1));
	while (++i < len)
		line[i] = temp[i];
	return (line);
}

//step 3
char	*saveline(char *str)
{
	char	*temp;
	size_t	len;
	char	*nl;

	len = 0;
	nl = ft_strchr(str, '\n');
	if (!nl)
		return (free(str), ft_strdup(""));
	nl++;
	while (nl[len])
		len++;
	temp = (char *) malloc((len + 1) * sizeof(char));
	if (!temp)
		return (free(str), NULL);
	temp[len] = '\0';
	while (len-- > 0)
		temp[len] = nl[len];
	free (str);
	return (temp);
}

char	*get_next_line(int fd) 
{
	static char	*temp = NULL;
	char		*line;

	line = NULL;
	if(fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	//step 1 read from file until a new line is found and return everything
	temp = read_content(fd, temp);
	if(!temp)
		return NULL;
	
	//step 2 save everything until nl included
	line = current_line(temp);
	if(!line)
		return (free(temp), NULL);
	
	//step 3 save what was after the newline
	temp = saveline(temp);
	if(!temp)
		return (free(line), NULL);

	//final step return the current line
	return (line);
}

/* int main()
{
    char    *line;
    int fd;

    fd = open("test.txt", O_RDONLY);
    while (1)
    {
		line = get_next_line(fd);
		printf("%s", line);
		if (!line)
			return (close(fd), 0);
		free(line);
    }
    close(fd);
    return 0;
}  */
