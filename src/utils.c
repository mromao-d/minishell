#include "../includes/minishel.h"

// compares 2 strings
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

// compares 2 strings until i
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

// returns len of string
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i] != 0)
		;
	return (i);
}

// returns a substring os string s
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

// advances on the string till it finds char c.
// returns the string from there onwards
char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c || *s == 0)
		return ((char *) s);
	return (0);
}

// counts words on an array
int	ft_count_words_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

// joins 2 strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

// copies a string into another string
char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = ft_strlen(s);
	str = (char *)malloc(sizeof(*str) * (j + 1));
	while (i < j)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < size)
		i++;
	while (src[j] && (i + j + 1) < size)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
