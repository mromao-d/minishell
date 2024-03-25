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

// DUP2 LEARNING
// prints the stdout in the file!!!!
// int main(int argc, char **argv)
// { 
// 	// int file_desc = open("fake.txt",O_WRONLY | O_APPEND);
// 	int file_desc = open("fake.txt",O_RDONLY);

// 	(void) argc;
// 	(void) argv;
// 	// here the newfd is the file descriptor of stdout (i.e. 1) 
// 	dup2(file_desc, STDIN_FILENO);

// 	// All the printf statements will be written in the file 
// 	// "tricky.txt" 
// 	printf("I will be printed in the file tricky.txt\n");
// 	// write(0, "Hello world\n", 12);

// 	close(file_desc);

// 	printf("Done\n");
// 	return 0; 
// } 



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


int main() {
    // Save the current stdin file descriptor
    int original_stdin = dup(STDIN_FILENO);

    // Open the file for reading
    int file = open("fake.txt", O_RDONLY);
    if (file == -1) {
        perror("Error opening fake.txt");
        return 1;
    }

    // Redirect stdin to read from the file
    if (dup2(file, STDIN_FILENO) == -1)
	{
        perror("Error redirecting stdin");
        return 1;
    }

    // Now stdin is redirected, and you can use readline or other input functions.

    char *input;
	while (1)
	{
		input = readline("Enter something: ");
		printf("You entered: %s\n", input);

		// Close the file and restore original stdin
		close(file);
		free(input);
		dup2(original_stdin, STDIN_FILENO);
	}

    return 0;
}
