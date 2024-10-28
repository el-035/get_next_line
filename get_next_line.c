#include "get_next_line.h"

#include <stdio.h> //to be deleted
#include <fcntl.h> //to be deleted

char	*saveline(char *str)
{
	char	*temp;
	size_t	len;
	char	*nl;

	len = 0;
	if (!str)
		return (NULL);
	nl = ft_strchr(str, '\n') + 1;
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

char	*nl_temp(char *buffer, char **temp)
{
	char *free_temp;

	free_temp = NULL;
	buffer = ft_linedup(*temp); //until nl
	if (!buffer)
		return (NULL);
	free_temp = saveline(*temp);//previous temp needs to be freed before reallocation
	if (!free_temp)
		return (NULL);
	free(*temp);
	*temp = ft_strdup(free_temp);
	if (!*temp)
		return (NULL);
	return (free(free_temp), buffer); 
	
}
char	*nl_buf(char *buffer, char **temp)
{
	char *free_temp;

	free_temp = NULL;
	free(*temp);
	*temp = saveline(buffer);
	if (!*temp)
		return (NULL);
	free_temp = ft_strdup (buffer);
	free (buffer);
	buffer = ft_linedup(free_temp);
	if (!buffer)
		return (NULL);
	return (free (*temp), buffer);
}

char *eof(char **temp)
{
	char *buffer;

	buffer = ft_strdup(*temp);
	free(*temp);
	*temp = NULL;
	return (buffer);
}
char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE +1];
	static char *temp = NULL;
	int			bytes;

	bytes = 1;
	ft_bzero(buffer, (BUFFER_SIZE + 1));
	while (bytes != 0 && !ft_strchr(buffer, '\n') && !ft_strchr(temp, '\n'))
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0 && temp != NULL)
			return(eof(&temp));
		temp = ft_strjoin(temp, buffer);
		if (!temp)
			return (NULL);
	}
	if (ft_strchr(temp, '\n'))
		return (nl_temp(buffer, &temp));
	if (ft_strchr(buffer, '\n'))
		return (nl_buf(buffer, &temp));
	return (free(temp), temp = NULL, NULL);
}

int main()
{
    char    *line = "";
    int fd;

    fd = open("divina_commedia.txt", O_RDONLY);
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