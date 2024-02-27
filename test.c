#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
	return (i + strlen(src));
}

int main(int argc, char **argv)
{
	char *a;
	char *b;

	a = malloc(sizeof(char) * 60);
	strcpy(a, "asdsadM");
	b = malloc(sizeof(char) * 7);
	// a = "kjbsd";
	b = "123456";
	if (argc > 1)
		printf("%s\n", argv[0]);
	printf("STDIN_FILENO is: %d\n", STDIN_FILENO);
	printf("STDOUT_FILENO is: %d\n", STDOUT_FILENO);
	printf("STDERR_FILENO is: %d\n", STDERR_FILENO);
	a[strlen(a)] = '/';
	ft_strlcat(a, b, strlen(a) + strlen(b));
	a[strlen(a)] = '/';
	ft_strlcat(a, b, strlen(a) + strlen(b));
	printf("ft_strlcat is: %s\n", a);
	// printf("env is: %d\n", execv(getenv("PATH"), "cat", NULL));
	// a = strncpy(a, b, 2);
	// printf("asfdasds\n");
	return (0);
}