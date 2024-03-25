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

// frees array of arrays
void	ft_free_arr(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
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
// access returns zero if all is ok
char	*ft_get_exec_name(char **paths, char *cmd)
{
	char	*s_path;
	char	*temp;
	char	**fst_cmd;

	fst_cmd = ft_split(cmd, ' ');
	while (*paths) {
		s_path = strdup(*paths);
		temp = s_path;
		s_path = ft_strjoin(s_path, fst_cmd[0]);
		if (!access(s_path, F_OK | R_OK)) {
			free(temp);
			ft_free_arr(fst_cmd);
			return (s_path);
		}
		free(s_path);
		free(temp);
		paths++;
	}
	ft_free_arr(fst_cmd);
	return NULL;
}

void	ft_redirect_input()
{
	return ;
}

// 
// int	ft_exec_grand_child(int fd_in, char **paths, char **argv, int argc)
// {
// 	int		pid;
// 	int		child_fd[2];
// 	char	**path;
// 	char	*cmd;

// 	if (pipe(child_fd) == -1) {
// 		perror ("pid on exec_grand_child");
// 		exit (1);
// 	}
// 	pid = fork();
// 	if (pid == -1) {
// 		perror ("fork error on grand child");
// 		exit (2);
// 	}
// 	if (pid == 0) {
// 		close(child_fd[0]);
// 		dup2(fd_in, STDIN_FILENO);
// 		dup2(child_fd[1], STDOUT_FILENO);
// 		path = ft_get_exec_name(paths, argv[argc + 2]);
// 		cmd = ft_split(argv[2], ' ');
// 		execve(path, cmd, NULL);
// 	}
// 	else {
// 		waitpid(pid, NULL, 0);
// 		close(fd_int);
// 		close(child_fd[0]);
// 		close(child_fd[1]);
// 	}
// 	return (child_fd[0]);
// }

void	ft_exec_child(char **argv, int *fd, char **paths, int argc)
{
	int		pid;
	int		child_fd[2];
	char	*path;
	char	**cmd;
	static int	i;

	if (pipe(child_fd) == -1) {
		perror ("pipe error on exec_child");
		exit (-1);
	}
	pid = fork();
	if (pid < 0) {
		perror ("fork error on exec_child");
		exit(-2);
	}
	if (pid == 0) {
		close(fd[1]);
		close(child_fd[0]);
		dup2(fd[0], STDIN_FILENO);
		dup2(child_fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(child_fd[1]);
		path = ft_get_exec_name(paths, argv[2]);
		cmd = ft_split(argv[2], ' ');
		ft_print_arr(cmd);
		execve(path, cmd, NULL);
	}
	else {
		path = ft_get_exec_name(paths, argv[argc - 2]);
		cmd = ft_split(argv[argc - 2], ' ');
		waitpid(pid, NULL, 0);
		// while (++i < argc - 4) {
		// 	child_fd[0] = ft_exec_grand_child();
		// }
		int	fdd = open("aux_", O_CREAT | O_RDWR, 0777);
		close(child_fd[1]);
		close(fd[0]);
		dup2(child_fd[0], STDIN_FILENO);
		close(child_fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(path, cmd, NULL);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	char	**paths;

	if (argc > 4)
	{
		fd[0] = open(argv[1], O_RDONLY);
		fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		paths = ft_get_paths(envp);
		ft_exec_child(argv, fd, paths, argc);
	}
	ft_free_arr (paths);
	return (0);
}
