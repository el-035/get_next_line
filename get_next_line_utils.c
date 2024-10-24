# include "get_next_line.h"

#include "get_next_line.h"
#include <fcntl.h> //
#include <stdio.h> //
#include <stdlib.h>
#include <unistd.h>

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;
	size_t	len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	str = (char *) malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = s[i];
	return (str);
}

size_t	ft_linelen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == (unsigned char) c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	mem;
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*join;

	i = 0;
	len1 = ft_linelen(s1);
	len2 = ft_linelen(s2);
	mem = len1 + len2 + 2; // if s2 doesnt have a nl then it should be 1?
	join = (char *) malloc(mem * sizeof(char));
	if (join == NULL)
		return (NULL);
	while (len1-- > 0)
		join[i++] = *s1++;
	while (len2-- > 0)
		join[i++] = *s2++;
	if (ft_strchr(s2, '\n'))
		join[i++] = '\n';
	join[i] = '\0';
	return (join);
}

char	*free_join(char *s1, char *s2)
{
	char	*res;
	int		f;

	f = 0;
	if (s1)
		f = 1;
	res = ft_strjoin(s1, s2);
	if (f == 1)
		free (s1);
	return (res);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*mem;
	size_t	temp;
	size_t	i;

	i = 0;
	temp = (nmemb * size);
	if (nmemb != 0 && temp / nmemb != size)
		return (NULL);
	mem = malloc(nmemb * size);
	if (mem == NULL)
		return (NULL);
	while (i < temp)
		mem[i++] = '\0';
	return ((void *)mem);
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*res;

	res = s;
	while (n-- > 0)
		*res++ = '\0';
}
/* int main (void)
{
	char *line = NULL;
	char *str = "Nel mezzo del cammin di nostra vita\n";
	
	
	line = ft_strdup(str);
	printf("%zu", ft_linelen("Nel mezzo del cammin di nostra vita\njsfkhudh"));
	printf("%s", ft_strjoin(line, "how are you?"));
}  */


/* char	*ft_temp(char *temp)
{
	char	*line;

	line = NULL;
	if (ft_strchr(temp, '\n'))
	{
		line = ft_strjoin(line, temp);
		if (!line)
				return (free(line), NULL);
		temp = saveline(temp);
		if (!temp)
				return (free(temp), NULL);
		return (line);
	}
	else
		return ()
} */

