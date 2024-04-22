#include "pipex.h"

int     ft_strlen(char *str)
{
    int     i;

    i = 0;
    while (str[i])
        i++;
    return(i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*str;

	i = 0;
	l = ft_strlen(s) - start;
	if (len == 0 || start >= ft_strlen(s))
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	if (len < l)
		l = len;
	str = malloc(sizeof(char) * (l + 1));
	if (str == NULL)
		return (NULL);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_wordcount(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count ++;
		i++;
	}
	return (count);
}

size_t	ft_wordlen(char *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s)
	{
		len++;
		s++;
	}
	return (len);
}

char	**ft_split(char *s, char c)
{
        char     **tab;
	int		i;
	int		wc;

	if (!s)
		return (NULL);
	wc = ft_wordcount(s, c);
	tab = (char **)malloc(sizeof(char *) * (wc + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		while (*s == c)
			s++;
		tab[i] = ft_substr(s, 0, ft_wordlen(s, c));
		if (!tab[i])
			return (NULL);
		s += ft_wordlen(s, c);
		i++;
	}
	tab[i] = (NULL);
	return (tab);
}