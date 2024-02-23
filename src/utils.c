#include "../includes/minishel.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t	i)
{
	size_t	j;

	if (i == 0)
		return (0);
	j = 0;
	while (*s1 && *s1 == *s2 && j < i - 1)
	{
		s1++;
		s2++;
		j++;
	}
	return ((int)*s1 - (int)*s2);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i] != 0)
		;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char *)malloc(sizeof(*s) * (len + 1));
	if (str == 0)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (s);
	return (0);
}
