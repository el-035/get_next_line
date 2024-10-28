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

	len1 = 0;
	len2 = 0;
	i = 0;
	while (s1 != NULL && s1[len1])
		len1++;
	while (s2[len2])
	    len2++;
	join = (char *) malloc ((len1 + len2 + 1) * sizeof (char));
	if (!join)
		return (NULL);
	while (s1 && len1-- > 0)
		join[i++] = *s1++;
	while (len2-- > 0)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

char	*ft_linedup(char *s) //rename linedup
{
	int		i;
	char	*str;
	int		len;

	i = -1;
	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	str = (char *) malloc((len + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (len + 2));
	while (i++ < len)
		str[i] = s[i];
	return (str);
}

char	*ft_strdup(char *s) //rename linedup
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



/* int main (void)
{
	//char *beg = NULL;
	char *end = "Nel mezzo del cammin di nostra vita \nmi ritrovai";

	printf ("%s", ft_linedup(end));

	beg = end;
	end = "ezzo";

	printf ("%s", ft_linedup(beg));
} */