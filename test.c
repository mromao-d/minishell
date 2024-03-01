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

// int main(int argc, char **argv)
// {
// 	char *a;
// 	char *b;
// 	char *args[] = {"/usr/local/bin/cat", NULL};
// 	char *cpy;

// 	a = malloc(sizeof(char) * 60);
// 	cpy = malloc(sizeof(char) * 20);
// 	strcpy(a, "asdsadM");
// 	b = malloc(sizeof(char) * 7);
// 	// a = "kjbsd";
// 	b = "123456";
// 	if (argc > 1)
// 		printf("%s\n", argv[0]);
// 	printf("STDIN_FILENO is: %d\n", STDIN_FILENO);
// 	printf("STDOUT_FILENO is: %d\n", STDOUT_FILENO);
// 	printf("STDERR_FILENO is: %d\n", STDERR_FILENO);
// 	a[strlen(a)] = '/';
// 	ft_strlcat(a, b, strlen(a) + strlen(b));
// 	a[strlen(a)] = '/';
// 	ft_strlcat(a, b, strlen(a) + strlen(b));
// 	printf("ft_strlcat is: %s\n", a);
// 	// args = (char **) 
// 	// execve("/usr/local/bin/cat", "Makefile", NULL);
// 	// execve("/usr/bin/cat", args, NULL);
// 	// execve("/usr/bin/cat", (char *[]){"/usr/bin/cat", "Makefile", NULL}, NULL);
// 	printf("strcpy is: %s\n", strcpy(cpy, "asdasdasd"));
// 	// a = strncpy(a, b, 2);
// 	// printf("asfdasds\n");
// 	return (0);
// }

int	main(void)
{
	printf("Here from test!\n");
	return (0);
}

// int	main(void)
// {
// 	execve("/mnt/c/Users/42/minishell",
//               (char *[]){"/mnt/c/Users/42/minishell", "/mnt/c/Users/42/minishell/test", NULL},
//               NULL);
// 	return (0);
// }
