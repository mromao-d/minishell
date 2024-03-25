#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


// joins 2 strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
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

static void	ft_freeup(char *strs)
{
	int	i;

	i = 0;
	while (strs[i] != '\0')
	{
		free(strs);
		i++;
	}
	free(strs);
}

static int	ft_wordcount(char *str, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			word++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (word);
		}
		i++;
	}
	return (word);
}

static void	ft_strcpy(char *word, char *str, char c, int j)
{
	int	i;

	i = 0;
	while (str[j] != '\0' && str[j] == c)
		j++;
	while (str[j + i] != c && str[j + i] != '\0')
	{
		word[i] = str[j + i];
		i++;
	}
	word[i] = '\0';
}

static char	*ft_stralloc(char *str, char c, int *k)
{
	char	*word;
	int		j;

	j = *k;
	word = NULL;
	while (str[*k] != '\0')
	{
		if (str[*k] != c)
		{
			while (str[*k] != '\0' && str[*k] != c)
				*k += 1;
			word = (char *)malloc(sizeof(char) * (*k + 1));
			if (word == NULL)
				return (NULL);
			break ;
		}
		*k += 1;
	}
	ft_strcpy(word, str, c, j);
	return (word);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		pos;

	if (str == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	j = ft_wordcount((char *)str, c);
	strs = (char **)malloc(sizeof(char *) * (j + 1));
	if (strs == NULL)
		return (NULL);
	strs[j] = NULL;
	while (i < j)
	{
		strs[i] = ft_stralloc(((char *)str), c, &pos);
		if (strs[i] == NULL)
		{
			ft_freeup(strs[i]);
		}
		i++;
	}
	return (strs);
}

typedef struct s_fds {
	int	fd_in;
	int	fd_out;
	int	nb_pipes;
	int	**pipe_fd;
	int	flag;
}	t_fds;

// format: ./pipex file1 cmd1 cmd2 file2

// Macro: int R_OK	->	Flag meaning test for read permission.
// Macro: int W_OK	->	Flag meaning test for write permission.
// Macro: int X_OK	->	Flag meaning test for execute/search permission.
// Macro: int F_OK	->	Flag meaning test for existence of the file.
// access return zero if access is permited and -1 otherwise

// when I run a process, I need to fork the process. The child process (pid == 0)

int	ft_validate_access(char *file1, char *file2)
{
	if (access(file1, F_OK | R_OK))
		perror("pipex: input\n");
}

// adds "/" at the end of each path (arr[i])
// might print it or not (comment the printf)
void	ft_print_arr(char **str)
{
	char	*temp;

	while (*str)
	{
		temp = *str;
		*str = ft_strjoin(*str, "/");
		// strcat(*str, "/");
		// printf("%s\n", *str);
		free(temp);
		str++;
	}
	return ;
}

// creates the necessary pipes
// pipes saves the file descriptor keys (read and write) of the process
int	ft_create_pipes(t_fds *fds, int argc)
{
	int	i;

	fds->nb_pipes = argc - 4;
	fds->pipe_fd = (int **)calloc(sizeof(int *), fds->nb_pipes + 1);
	i = -1;
	while (++i < fds->nb_pipes)
	{
		fds->pipe_fd[i] = (int *)calloc(sizeof(int), 2);
		if (!fds->pipe_fd[i])
		{
			perror ("malloc ing pipes error\n");
			exit (1);
		}
		if (pipe(fds->pipe_fd[i]) == -1)
		{
			perror ("pipping error\n");
			exit (2);
		}
		// printf("%d\n", fds->pipe_fd[i][0]);
		// printf("%d\n", fds->pipe_fd[i][1]);
	}
	fds->pipe_fd[i] = 0;
	return (0);
}

void	ft_free_pipes(t_fds *fds)
{
	int	i;

	i = -1;
	while (fds->pipe_fd[++i])
		free(fds->pipe_fd[i]);
	free(fds->pipe_fd);
}

// returns all paths from the environment
char	**ft_get_paths(char	**envp)
{
	char	**paths;

	while (*envp)
	{
		if (strncmp(*envp, "PATH", 4) == 0)
			// printf("%s\n", *envp);
			paths = ft_split(*envp + 5, ':');
		envp++;
	}
	ft_print_arr(paths);
	return (paths);
}

// returns the executable name, if it has accesses.
char	*ft_get_exec_name(char **paths, char *cmd)
{
	char	*s_path;
	char	*temp;

	while (*paths) {
		s_path = strdup(*paths);
		temp = s_path;
		s_path = ft_strjoin(s_path, cmd);
		if (!access(s_path, F_OK | R_OK)) {
			printf("path is: %s\n\n", s_path);
			free(s_path);
			free(temp);
			return ;
		}
		// printf("%s\n", s_path);
		free(s_path);
		free(temp);
		paths++;
	}
	return ;
}

// frees array of arrays
void	ft_free_arr(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

// sets the proper flag to send to the new process
void	ft_set_flag(int	i, int argc, t_fds *fds)
{
	if (i == 0)
		(*fds).flag = 0;
	else if (i + 2 == argc - 2)
		(*fds).flag = 2;
	else
		(*fds).flag = 1;
	// printf("flag is:	%d\n", (*fds).flag);
	return ;
}

// forks the actual process. 
// The chid will write the cmd (STDOUT) and the parent will read this value (STDIN)
void	ft_new_process(char *argv, char **paths, t_fds *fds)
{
	int	pid;
}

// main
// int	main(int argc, char **argv, char **envp)
// {
// 	t_fds	fds;
// 	char	**paths;
// 	int		i;

// 	if (argc != 5) {
// 		perror("Wrong number of args");
// 		return (1);
// 	}
// 	fds.fd_in = open(argv[1], O_RDONLY);
// 	fds.fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	ft_create_pipes(&fds, argc);
// 	paths = ft_get_paths(envp);
// 	ft_free_arr(paths);
// 	i = -1;
// 	while (++i < argc -3)	//	argv{0, 1, -1} are not cmds, so it has to be till argc - 3
// 	{
// 		ft_set_flag(i, argc, &fds);
// 		ft_new_process(argv[i + 2], paths, &fds);	// argv[2] is the 1st cmd
// 	}
// 	printf("\n\n %s\n\n", argv[0]);
// 	close(fds.fd_in);
// 	close(fds.fd_out);
// 	// ft_plug_pipes(&fds);
// 	ft_free_pipes(&fds);
// 	// paths = ;
// 	return (0);
// }

void	ft_exec_child(int *fd, int argc, char **argv, char **envp)
{
	;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	**paths;

	if (argc > 2)
	{
		// fd[1] = open(argv[argc - 1], O_WRONLY | O_CREATE | O_TRUNC, 0644);
		fd[0] = open(argv[1], O_RDONLY);
		paths = ft_get_paths(envp);
		ft_get_exec_name(paths, argv[2]);
		// ft_exec_child(fd, argc, argv, envp);
	}
	ft_free_arr(paths);
}
