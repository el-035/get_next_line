#include "get_next_line.h"
#include <stdio.h> 

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*res;

	res = s;
	while (n-- > 0)
		*res++ = '\0';
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s || !s[i])
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

char    *ft_strjoin(char *s1, char *s2)
{
	char    *join;
	int     len1;
	int     len2;
	int		i;
	char 	*ptr;

	len1 = 0;
	len2 = 0;
	i = 0;
	ptr = s1;
	while (ptr != NULL && ptr[len1])
		len1++;
	while (s2[len2])
	    len2++;
	join = (char *)malloc((len1 + len2 + 1) * sizeof (char));
	if (!join)
		return ( free (s1), NULL);
	while (ptr && len1-- > 0)
		join[i++] = *ptr++;
	while (len2-- > 0)
		join[i++] = *s2++;
	join[i] = '\0';
	return (free(s1), join);
}

char	*ft_strdup(char *s)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	len = 0;
	while (s[len])
		len++;
	str = (char *) malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (len + 1));
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = s[i];
	return (str);
} 

// int main (void)
// {
// 	//char *beg = NULL;
// 	char *end = "Nel mezzo del cammin di nostra vita \nmi ritrovai";

// 	printf ("%s", current_line(end));

// } */