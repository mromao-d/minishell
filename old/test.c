#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <fcntl.h> 

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

// int	main(void)
// {
// 	printf("Here from test!\n");
// 	return (0);
// }

// int	main(void)
// {
// 	char *prompt;

// 	while (1)
// 	{
// 		prompt = readline("test: ");
// 		if (strcmp(prompt, "ls") == 0)
// 		{
// 			printf("Yes\n");
// 			// execve("/usr/bin/cat", (char *[]){"/usr/bin/cat", "tes.txt", NULL}, NULL);
// 			execve("/usr/bin/ls", (char *[]){"ls", NULL}, NULL);
// 		}
// 	}
// 	return (0);
// }




// DUP2 LEARNING
// prints the stdout in the file!!!!
int main() 
{ 
    int file_desc = open("fake.txt",O_WRONLY | O_APPEND); 
      
    // here the newfd is the file descriptor of stdout (i.e. 1) 
    dup2(file_desc, 1) ;  

    // All the printf statements will be written in the file 
    // "tricky.txt" 
    printf("I will be printed in the file tricky.txt\n"); 
      
	return 0; 
} 



// DUP LEARNING
// int main() 
// { 
//     // open() returns a file descriptor file_desc to a  
//     // the file "dup.txt" here" 
  
//     int file_desc = open("fake.txt", O_WRONLY | O_APPEND); 
      
//     if(file_desc < 0) 
//         printf("Error opening the file\n"); 
      
//     // dup() will create the copy of file_desc as the copy_desc 
//     // then both can be used interchangeably. 
  
//     int copy_desc = dup(file_desc); 
          
//     // write() will write the given string into the file 
//     // referred by the file descriptors 
  
//     write(copy_desc,"This will be output to the file named dup.txt\n", 46); 
          
//     write(file_desc,"This will also be output to the file named dup.txt\n", 51); 
      
//     return 0; 
// } 

